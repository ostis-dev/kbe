/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <QGraphicsSceneMouseEvent>
#include "scgnodetextitem.h"


SCgNodeTextItem::SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::IdentifierPosition idtfPos)
    : SCgTextItem(str,(QGraphicsItem*)parent)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
}


SCgNodeTextItem::SCgNodeTextItem(SCgNode *parent, SCgNode::IdentifierPosition idtfPos)
    : SCgTextItem((QGraphicsItem*)parent)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
}


SCgNodeTextItem::~SCgNodeTextItem()
{

}
void SCgNodeTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if ((flags() & QGraphicsItem::ItemIsMovable) != 0)
        setNodeTextPos(posToIdtfPos(mapToParent(event->pos())));
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
        if (y > 8)
            idtfPos = SCgNode::BottomRight;
        if (y < -8)
            idtfPos = SCgNode::TopRight;
        if (y >= -8 && y <= 8)
            idtfPos = SCgNode::Right;
    }
    else
    {
        if (y > 8)
            idtfPos = SCgNode::BottomLeft;
        if (y < -8)
            idtfPos = SCgNode::TopLeft;
        if (y >= -8 && y <= 8)
            idtfPos = SCgNode::Left;
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
    if (pos == SCgNode::Right) {
        newPos.setX(parentRect.right() - 4);
        newPos.setY(parentRect.bottom() - 24);
    }
    if (pos == SCgNode::Left) {
        newPos.setX(parentRect.left() - rect.width() + 4);
        newPos.setY(parentRect.bottom() - 24);
    }

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
    setPos(pos);
}

void SCgNodeTextItem::setPlainText(const QString &text)
{
    SCgTextItem::setPlainText(text);
    updateTextPos(mTextPos);
}
