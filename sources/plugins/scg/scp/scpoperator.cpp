/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpoperator.h"
#include "scpgraphicalstyle.h"
#include "scpoperatorpin.h"

#include <QCursor>


SCpOperator::SCpOperator(QGraphicsItem * parent)
    : SCgObject(parent)
    , mOperatorName(tr("Base SCp operator"))
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setZValue(3);

    mShadowEffect = new QGraphicsDropShadowEffect(this);
    SCpGraphicalStyle::instance()->configureShadowEffect(mShadowEffect);
    setGraphicsEffect(mShadowEffect);

    /// test
    addInputPin(new SCpOperatorPin("do"));

    for (int i = 0; i < 10; ++i)
        addOutputPin(new SCpOperatorPin("then"));
    addOutputPin(new SCpOperatorPin("else"));
}

SCpOperator::~SCpOperator()
{
    delete mShadowEffect;
}

QPainterPath SCpOperator::shape() const
{
    float const radius = SCpGraphicalStyle::instance()->operatorBodyRadius();
    QPainterPath path;
    path.addRoundedRect(boundingRect(), radius, radius);
    return path;
}

QRectF SCpOperator::boundingRect() const
{
    return mBoundsRect;
}

void SCpOperator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF rect = boundingRect();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipPath(shape());
    painter->setClipping(true);

    /// TODO: move padding, header height and font to scp style
    SCpGraphicalStyle * style = SCpGraphicalStyle::instance();

    painter->drawPixmap(rect.toRect(), style->operatorBodyPixmap());

    float const headerHeight = style->operatorHeaderHeight();
    // header
    QRectF headerRect(rect.left(),
                      rect.top() ,
                      rect.width(),
                      headerHeight);
    {

        painter->drawPixmap(rect.left(), rect.top(), rect.width(), headerRect.height(), style->operatorHeaderPixmap());
        painter->setClipping(false);

        painter->setPen(Qt::white);
        painter->setFont(style->operatorIconFont());
        painter->drawText(rect.left(), rect.top(), headerHeight, headerHeight, Qt::AlignCenter, style->operatorIconText());
        painter->drawLine(headerRect.left(), headerRect.bottom(), headerRect.right(), headerRect.bottom());
        painter->setFont(style->operatorTitleFont());

        painter->drawText(headerRect.adjusted(headerHeight, 0, 0, 0), Qt::AlignCenter, mOperatorName);
    }

    // border
    if (isSelected())
    {
        qreal const radius = style->operatorBodyRadius();
        QColor color = mColor;
        color.setAlpha(200);

        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(color, 5.f));
        painter->drawRoundedRect(rect.adjusted(-3, -3, 3, 3), radius, radius);
    }
}

void SCpOperator::positionChanged()
{

}

QPointF SCpOperator::cross(QPointF const & from, float dot) const
{
    if (dot < 1.f && dot > -1.f)
    {
        QPointF p(mBoundsRect.center());
        QPolygonF polygon(mBoundsRect);
        QPointF p1 = polygon.last();
        QPointF p2, intersectPoint;
        QLineF line, pair(p, mapFromScene(from));
        bool haveIntersect = false;

        for (int i = 0; i < polygon.size(); i++)
        {
            p2 = polygon.at(i);
            line = QLineF(p1, p2);
            QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
            {
                haveIntersect = true;
                break;
            }

            p1 = p2;
        }
        p = haveIntersect ? intersectPoint : p;
        return mapToScene(p);
    }

    return pos();
}

float SCpOperator::dotPos(QPointF const & point) const
{
    return 0.f;
}

void SCpOperator::connectedObjectDelete(SCgObject * object)
{

}

void SCpOperator::updateBounds()
{
    SCpGraphicalStyle * style = SCpGraphicalStyle::instance();

    QFontMetricsF headerTextMetrics(style->operatorTitleFont());

    qreal const pinSpacer = style->operatorPinSpacer();
    qreal width = qMax((qreal)150.f, headerTextMetrics.width(mOperatorName)) + style->operatorHeaderHeight();
    qreal height = style->operatorHeaderHeight();

    QVector<SCpOperatorPin*>::iterator itInput, itOutput;
    itInput = mInputPins.begin();
    itOutput = mOutputPins.begin();

    while ((itInput != mInputPins.end()) || (itOutput != mOutputPins.end()))
    {
        QRectF inputRect;
        if (itInput != mInputPins.end())
        {
            inputRect = (*itInput)->boundingRect();
            ++itInput;
        }

        QRectF outputRect;
        if (itOutput != mOutputPins.end())
        {
            outputRect = (*itOutput)->boundingRect();
            ++itOutput;
        }

        width = qMax(width, inputRect.width() + outputRect.width() + 2 * pinSpacer);
        height += pinSpacer + qMax(inputRect.height(), outputRect.height());
    }

    mBoundsRect = QRectF(0, 0, width, height);
}

void SCpOperator::updatePinPositions()
{
    updateBounds();

    for (qint32 idx = 0; idx < mInputPins.size(); ++idx)
        mInputPins[idx]->setPos(calculatePinPosition(idx, true));

    for (qint32 idx = 0; idx < mOutputPins.size(); ++idx)
        mOutputPins[idx]->setPos(calculatePinPosition(idx, false));
}

QPointF SCpOperator::calculatePinPosition(int index, bool isInput) const
{
    SCpGraphicalStyle * style = SCpGraphicalStyle::instance();
    float const pinSize = style->operatorPinSize();
    float const pinSpacer = style->operatorPinSpacer();

    float const y = style->operatorHeaderHeight() + index * (pinSpacer + pinSize) + pinSize * 0.5f;
    float const x = isInput ? (mBoundsRect.left() + pinSpacer) : (mBoundsRect.right() - pinSpacer);

    return QPointF(x, y);
}

void SCpOperator::addInputPin(SCpOperatorPin * pin)
{
    pin->setPinType(SCpOperatorPin::Input);
    pin->setParentItem(this);
    mInputPins.append(pin);
    updatePinPositions();
}

void SCpOperator::addOutputPin(SCpOperatorPin * pin)
{
    pin->setPinType(SCpOperatorPin::Output);
    pin->setParentItem(this);
    mOutputPins.append(pin);
    updatePinPositions();
}
