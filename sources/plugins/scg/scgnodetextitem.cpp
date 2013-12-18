/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see .
-----------------------------------------------------------------------------
*/

#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "scgnodetextitem.h"


SCgNodeTextItem::SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::IdentifierPosition idtfPos, QGraphicsScene* scene )
    : SCgTextItem(str,(QGraphicsItem*)parent,scene)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
}


SCgNodeTextItem::SCgNodeTextItem(SCgNode *parent, SCgNode::IdentifierPosition idtfPos, QGraphicsScene *scene)
    : SCgTextItem((QGraphicsItem*)parent, scene)
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
        setTextPos(posToIdtfPos(mapToParent(event->pos())));
}


void SCgNodeTextItem::setTextPos(SCgNode::IdentifierPosition pos)
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
        if (y > 0)
            idtfPos = SCgNode::BottomRight;
		else
            idtfPos = SCgNode::TopRight;
	else
        if (y > 0)
            idtfPos = SCgNode::BottomLeft;
		else
            idtfPos = SCgNode::TopLeft;

	return idtfPos;
}


void SCgNodeTextItem::updateTextPos(SCgNode::IdentifierPosition pos)
{
	QRectF rect = boundingRect();
	QRectF parentRect =  mParentItem->boundingRect();

	QPointF newPos = parentRect.bottomRight() - QPointF(rect.x(),rect.y());

    if (pos == SCgNode::BottomLeft || pos == SCgNode::TopLeft)
		newPos.rx() = parentRect.left() - rect.width() - rect.x();

    if (pos == SCgNode::TopLeft || pos == SCgNode::TopRight)
		newPos.ry() = parentRect.top() - rect.height() - rect.y();

	setPos(newPos);
    mParentItem->setSelected(true);
    setSelected(false);
}
