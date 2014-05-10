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

#include <QGraphicsSceneMouseEvent>
#include "scgnodetextitem.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <scgscene.h>
#include <QRectF>



SCgNodeTextItem::SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::eIdentifierPosition idtfPos, QGraphicsScene* scene )
    : SCgTextItem(str,(QGraphicsItem*)parent,scene)
    , mTextPos(idtfPos)
{
    Q_CHECK_PTR(parent);
    mParentItem = parent;
    updateTextPos(mTextPos);
}


SCgNodeTextItem::SCgNodeTextItem(SCgNode *parent, SCgNode::eIdentifierPosition idtfPos, QGraphicsScene *scene)
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


void SCgNodeTextItem::setTextPos(SCgNode::eIdentifierPosition pos)
{
    if (mTextPos != pos)
    {
        mTextPos = pos;
        updateTextPos(mTextPos);
    }
}

SCgNode::eIdentifierPosition SCgNodeTextItem::posToIdtfPos(const QPointF &point) const
{
    SCgNode::eIdentifierPosition idtfPos = SCgNode::BottomRight;

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


void SCgNodeTextItem::updateTextPos(SCgNode::eIdentifierPosition pos)
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

SCgNode::eIdentifierPosition SCgNodeTextItem::textPos() const
{
    return mTextPos;
}


void SCgNodeTextItem :: showPositions(SCgScene * scgScene, bool isShow)
{
    if(textItemPositions.empty())
    {
        createTextItemPostitions(scgScene);
    } else {
        // show or hide text item position
        foreach(QGraphicsRectItem * position,textItemPositions) {
            if(isShow) {
                position->show();
            } else {
                position->hide();
            }
        }
    }

}

void SCgNodeTextItem :: createTextItemPositions(SCgScene * scgScene) {

    QGraphicsScene * scene = static_cast<QGraphicsScene*>(scgScene);
    QGraphicsRectItem * textPositionItem;
    QRectF rect = boundingRect();
    QRectF parentRect =  mParentItem->boundingRect();

    qreal height = this->boundingRect().height();
    qreal widht = this->boundingRect().width();
    qreal x, y;

    //bottom left
    x = parentRect.left() - rect.width() + 8;
    y = parentRect.bottom() - 8;
    QRectF * textRect  = new QRectF(x,y,widht,height);
    textPositionItem = new QGraphicsRectItem(*textRect,mParentItem,scene);
    textPositionItem->hide();
    textItemPositions.push_back(textPositionItem);

    //top left
    y = parentRect.top() - rect.height() + 8;
    textRect  = new QRectF(x,y,widht,height);
    textPositionItem = new QGraphicsRectItem(*textRect,mParentItem,scene);
    textPositionItem->hide();
    textItemPositions.push_back(textPositionItem);

    //top rigth
    x = parentRect.right() - 8;
    textRect  = new QRectF(x,y,widht,height);
    textPositionItem = new QGraphicsRectItem(*textRect,mParentItem,scene);
    textPositionItem->hide();
    textItemPositions.push_back(textPositionItem);

    //bottom rigth
    y = parentRect.bottom() - 8;
    textRect  = new QRectF(x,y,widht,height);
    textPositionItem = new QGraphicsRectItem(*textRect,mParentItem,scene);
    textPositionItem->hide();
    textItemPositions.push_back(textPositionItem);

}





