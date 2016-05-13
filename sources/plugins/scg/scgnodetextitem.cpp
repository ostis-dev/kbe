/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QCursor>
#include "scgnodetextitem.h"

// Used as width of horizontal borders of identifier bounding rectangle
const int adjust = 10;

SCgNodeTextItem::SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::IdentifierPosition idtfPos)
    : SCgTextItem(str,(QGraphicsItem*)parent)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
    setAcceptHoverEvents(true);
}


SCgNodeTextItem::SCgNodeTextItem(SCgNode *parent, SCgNode::IdentifierPosition idtfPos)
    : SCgTextItem((QGraphicsItem*)parent)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
    setAcceptHoverEvents(true);
}


SCgNodeTextItem::~SCgNodeTextItem()
{

}

void SCgNodeTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void SCgNodeTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if ( (nodeTextPos() == SCgNode::TopLeft || nodeTextPos() == SCgNode::BottomLeft) &&
            (event->pos().x() < boundingRect().left() + adjust) )
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if ( (nodeTextPos() == SCgNode::TopRight || nodeTextPos() == SCgNode::BottomRight) &&
             (event->pos().x() > boundingRect().right() - adjust) )
    {
        setCursor(Qt::SizeHorCursor);
    }
    else setCursor(Qt::OpenHandCursor);
}

void SCgNodeTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        setCursor(Qt::OpenHandCursor);
}

void SCgNodeTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        setCursor(Qt::ClosedHandCursor);

    double dx = event->pos().x() - event->lastPos().x();
    if ( (nodeTextPos() == SCgNode::TopLeft || nodeTextPos() == SCgNode::BottomLeft) &&
            (event->pos().x() < boundingRect().left() + adjust) )
    {
        setCursor(Qt::SizeHorCursor);
        changeIdtfWidth(-dx);
    }
    else if ( (nodeTextPos() == SCgNode::TopRight || nodeTextPos() == SCgNode::BottomRight) &&
             (event->pos().x() > boundingRect().right() - adjust) )
    {
        setCursor(Qt::SizeHorCursor);
        changeIdtfWidth(dx);
    }
    {
        if ((flags() & QGraphicsItem::ItemIsMovable) != 0)
            setNodeTextPos(posToIdtfPos(mapToParent(event->pos())));
    }
}


void SCgNodeTextItem::setNodeTextPos(SCgNode::IdentifierPosition pos)
{
    if (mTextPos != pos)
    {
        mTextPos = pos;
        updateTextPos(mTextPos);
    }
}

SCgNode::IdentifierPosition SCgNodeTextItem::posToIdtfPos(const QPointF &point) const
{
    SCgNode::IdentifierPosition idtfPos = SCgNode::BottomRight;

    qreal x = point.x();
    qreal y = point.y();

    if (qFuzzyIsNull(x))
        x += 1;
    if (qFuzzyIsNull(y))
        y += 1;

    if (x > 0)
    {
        if (y > 0)
            idtfPos = SCgNode::BottomRight;
        else
            idtfPos = SCgNode::TopRight;
    }
    else
    {
        if (y > 0)
            idtfPos = SCgNode::BottomLeft;
        else
            idtfPos = SCgNode::TopLeft;
    }

    return idtfPos;
}


void SCgNodeTextItem::updateTextPos(SCgNode::IdentifierPosition pos)
{
    QRectF rect = boundingRect();
    QRectF parentRect =  mParentItem->boundingRect();

    QPointF newPos;

    if (pos == SCgNode::BottomLeft || pos == SCgNode::TopLeft)
        newPos.setX(parentRect.left() - rect.width() + 8);
    else
        newPos.setX(parentRect.right() - 8);

    if (pos == SCgNode::TopLeft || pos == SCgNode::TopRight)
        newPos.setY(parentRect.top() - rect.height() + 8);
    else
        newPos.setY(parentRect.bottom() - 8);

    setPos(newPos);
    mParentItem->setSelected(true);
    setSelected(false);
}

SCgNode::IdentifierPosition SCgNodeTextItem::nodeTextPos() const
{
    return mTextPos;
}

void SCgNodeTextItem::setTextPos(const QPointF &pos)
{
    setNodeTextPos(posToIdtfPos(pos));
}

void SCgNodeTextItem::setPlainText(const QString &text)
{
    SCgTextItem::setPlainText(text);
    updateTextPos(mTextPos);
}

void SCgNodeTextItem::changeIdtfWidth(double dx)
{
    QRectF prevRect = boundingRect();
    QPointF prevPos = pos();

    SCgNode::IdentifierPosition idtfPos = nodeTextPos();
    this->setTextWidth(this->textWidth() + dx);

    QRectF newRect = boundingRect();
    QPointF newPos;
    QPointF diff;

    switch(idtfPos)
    {
        case SCgNode::TopLeft :
            diff = prevRect.bottomRight() - newRect.bottomRight();
            break;
        case SCgNode::TopRight :
            diff = prevRect.bottomLeft() - newRect.bottomLeft();
            break;
        case SCgNode::BottomRight :
            diff = prevRect.topLeft() - newRect.topLeft();
            break;
        case SCgNode::BottomLeft :
            diff = prevRect.topRight() - newRect.topRight();
            break;
        default:
            throw std::exception("Unknown enum member.");
    }

    newPos = prevPos + diff;
    setPos(newPos);
}
