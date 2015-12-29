/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpoperatorpin.h"
#include "scpgraphicalstyle.h"

#include <QPainter>

SCpOperatorPin::SCpOperatorPin(QString const & displayName, QGraphicsItem * parent)
    : QGraphicsItem(parent)
    , mDisplayName(displayName)
    , mPinType(Input)
    , mIsHovered(false)
{
    setAcceptHoverEvents(true);
}

SCpOperatorPin::~SCpOperatorPin()
{
}

void SCpOperatorPin::setPinType(SCpOperatorPin::ePinType pinType)
{
    mPinType = pinType;
    updateBounds();
}

SCpOperatorPin::ePinType SCpOperatorPin::pinType() const
{
    return mPinType;
}

void SCpOperatorPin::setDisplayName(QString const & displayName)
{
    mDisplayName = displayName;
    updateBounds();
}

QString const & SCpOperatorPin::displayName() const
{
    return mDisplayName;
}


QRectF SCpOperatorPin::boundingRect() const
{
    return mBoundRect;
}

void SCpOperatorPin::paint(QPainter * painter, QStyleOptionGraphicsItem const * option, QWidget * widget)
{
    SCpGraphicalStyle * style = SCpGraphicalStyle::instance();

    float const pinSize = style->operatorPinSize();

    painter->setPen(mIsHovered ? style->operatorPinPenHovered() : style->operatorPinPen());

    QRectF nameRect;
    QPainterPath pinPath;
    if (mPinType == Input)
    {
        pinPath.moveTo(mBoundRect.left() + pinSize, mBoundRect.center().y());
        pinPath.lineTo(mBoundRect.left(), mBoundRect.top());
        pinPath.lineTo(mBoundRect.left(), mBoundRect.bottom());

        nameRect = mBoundRect.adjusted(pinSize + 5.f, 0, 0, 0);
    }
    else
    {
        pinPath.moveTo(mBoundRect.right() - pinSize, mBoundRect.top());
        pinPath.lineTo(mBoundRect.right(), mBoundRect.center().y());
        pinPath.lineTo(mBoundRect.right() - pinSize, mBoundRect.bottom());

        nameRect = mBoundRect.adjusted(0, 0, -pinSize - 5.f, 0);
    }
    pinPath.closeSubpath();
    painter->drawPath(pinPath);

    // draw text
    painter->setBrush(Qt::NoBrush);
    painter->setFont(style->operatorPinFont());
    painter->drawText(nameRect, Qt::AlignVCenter | (mPinType == Input ? Qt::AlignLeft : Qt::AlignRight), mDisplayName);
}

void SCpOperatorPin::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    mIsHovered = true;
}

void SCpOperatorPin::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
    mIsHovered = false;
}

void SCpOperatorPin::updateBounds()
{
    SCpGraphicalStyle const * style = SCpGraphicalStyle::instance();
    qreal const s = style->operatorPinSize();

    qreal nameWidth = 0.f;
    if (!mDisplayName.isEmpty())
    {
        QFontMetricsF metrics(style->operatorPinFont());
        nameWidth = metrics.width(mDisplayName);
    }

    if (mPinType == Input)
    {
        mBoundRect.setCoords(0.f, 0.f, s + nameWidth + 10.f, s);
    }
    else
    {
        mBoundRect.setCoords(-s - nameWidth - 10.f, 0.f, 0.f, s);
    }
}
