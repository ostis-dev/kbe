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
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/
#include "SCgSelectModeEventHandler.h"
#include "../scgcontour.h"
#include <QUndoStack>
#include "../scgnode.h"
#include "../pointgraphicsitem.h"

SCgSelectModeEventHandler::SCgSelectModeEventHandler(SCgScene* parent):SCgEventHandler(parent),
                                            mIsItemsMoved(false),
                                            mCurrentPointObject(0)
{

}

SCgSelectModeEventHandler::~SCgSelectModeEventHandler()
{
//    clean();
}

void SCgSelectModeEventHandler::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    // left button
    if (event->button() == Qt::LeftButton)
    {
        QGraphicsItem *item = mScene->itemAt(mousePos);
        if(mCurrentPointObject)
        {
            QPainterPath p = mCurrentPointObject->shapePoints();
            QPointF itemPoint = mCurrentPointObject->mapFromScene(mousePos);
            if(p.contains(itemPoint))
                mScene->addPointCommand(mCurrentPointObject,itemPoint);
            event->accept();
        }else
        // check if there are no any items under mouse and create scg-node
        if (item == 0 || item->type() == SCgContour::Type)
        {
            SCgContour *contour = 0;
            if (item != 0 && item->type() == SCgContour::Type)
                contour = static_cast<SCgContour*>(item);
            mScene->createNodeCommand(mousePos, contour);
            event->accept();
        }
    }
    SCgEventHandler::mouseDoubleClick(event);
}

void SCgSelectModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton && !mIsItemsMoved)
    {
        //We should use there current event position (not mStartPos) because of the delay between mousePress and mouseMove events.
        //______________________________________________________//
        //Store start positions(before items moving)
        QList<QGraphicsItem*> items = mScene->selectedItems();
        QList<QGraphicsItem*>::const_iterator it = items.begin();
        while(it != items.end())
        {
            QGraphicsItem* item = *it;
            // Item won't be moved if it is movable or its movable ancestor is selected.
            if( item->flags() & QGraphicsItem::ItemIsMovable && !movableAncestorIsSelected(item))
            {
                QPointF p = item->pos();
                QGraphicsItem *parent = item->parentItem();
                mUndoInfo[item] = qMakePair(qMakePair(parent, p), qMakePair(parent, p));
            }
            ++it;
        }
        //______________________________________________________//
        mIsItemsMoved = !mUndoInfo.empty();
    }
}

void SCgSelectModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    if(mCurrentPointObject)
    {
        QPainterPath p = mCurrentPointObject->shapePoints();
        if(!p.contains(mCurrentPointObject->mapFromScene(event->scenePos())))
        {
            mCurrentPointObject->destroyPointObjects();
            mCurrentPointObject = 0;
        }
    }
    if(!mCurrentPointObject)
    {
        QPointF cur_pos = event->scenePos();
        SCgObject* objAtMouse = mScene->objectAt(cur_pos);
        if(objAtMouse && SCgObject::isSCgPointObjectType(objAtMouse->type()))
        {
            mCurrentPointObject = static_cast<SCgPointObject*>(objAtMouse);
            if(mCurrentPointObject->shapePoints().contains(mCurrentPointObject->mapFromScene(cur_pos)))
                mCurrentPointObject->createPointObjects();
            else
                mCurrentPointObject = 0;
        }
    }
}

void SCgSelectModeEventHandler::mouseRelease(QGraphicsSceneMouseEvent *event)
{
    if(mIsItemsMoved)
    {
        //______________________________________________________//
        //Store finish positions (after items moving)
        SCgScene::ItemUndoInfo::iterator it = mUndoInfo.begin();
        for(; it != mUndoInfo.end(); ++it) {
            QGraphicsItem *item = it.key();
            // exclude PointGraphicsItem's object, because it always has a parent item
            if (item->type() == PointGraphicsItem::Type) {
                it.value().second.second = item->pos();
                continue;
            }
            // get list of items, which have the same position
            QList<QGraphicsItem*> itemList = mScene->items(item->scenePos(), Qt::ContainsItemShape, Qt::AscendingOrder);
            // if item is a SCgNode we will move it to the end of the list
            if (item->type() == SCgNode::Type) {
                itemList.removeOne(item);
                itemList.push_back(item);
            }
            int index = itemList.indexOf(item);
            SCgContour *newParent = 0;
            Q_ASSERT(index >= 0);
            // find nearest SCgContour according to stack order
            do {
                if (!index) break;
                QGraphicsItem *tmpItem = itemList.at(--index);
                // check
                if (!item->childItems().contains(tmpItem) && tmpItem->type() == SCgContour::Type)
                    newParent = dynamic_cast<SCgContour*>(tmpItem);
            } while(!newParent && index != 0);
            if (newParent) {// mapped item coordinates to new parent item
                QGraphicsItem *oldParent = item->parentItem();
                if (oldParent) it.value().second.second = oldParent->mapToItem(newParent, item->pos());
                else it.value().second.second = newParent->mapFromScene(item->pos());

                it.value().second.first = newParent;
                item->setParentItem(newParent);
            }
            else {
                // we need check if items under cursor contain old parent item
                QGraphicsItem *oldParent = item->parentItem();
                if (!itemList.contains(oldParent)){
                    it.value().second.second = item->scenePos();
                    item->setParentItem(0);
                    it.value().second.first = 0;
                }
                else it.value().second.second = item->pos();
            }
        }
        //______________________________________________________//
        mScene->moveSelectedCommand(mUndoInfo);
        mIsItemsMoved = false;
        mUndoInfo.clear();
    }
}

void SCgSelectModeEventHandler::clean()
{
    SCgEventHandler::clean();
    mIsItemsMoved = false;
    mUndoInfo.clear();
    if (mCurrentPointObject)
        mCurrentPointObject->destroyPointObjects();
    mCurrentPointObject = 0;
}



