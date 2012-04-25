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
#include "scgselectmode.h"
#include "scgcontour.h"
#include "gwf/gwffilewriter.h"
#include "gwf/gwfobjectinforeader.h"
#include "scgtemplateobjectbuilder.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgtextitem.h"
#include "scgpointgraphicsitem.h"

#include <QDebug>
#include <QDomDocument>

SCgSelectMode::SCgSelectMode(SCgScene* parent):SCgMode(parent),
    mIsItemsMoved(false),
    mCurrentPointObject(0)
{

}

SCgSelectMode::~SCgSelectMode()
{
    //    clean();
}

void SCgSelectMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    // left button
    if (event->button() == Qt::LeftButton)
    {
        QGraphicsItem *item = mScene->itemAt(mousePos);
        if(mCurrentPointObject)
        {
            QPainterPath p = mCurrentPointObject->lineShape();
            QPointF itemPoint = mCurrentPointObject->mapFromScene(mousePos);
            if(p.contains(itemPoint))
            {
                mScene->addPointCommand(mCurrentPointObject,itemPoint);
                event->accept();
                return;
            }
        }

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
    SCgMode::mouseDoubleClick(event);
}

void SCgSelectMode::mouseMove(QGraphicsSceneMouseEvent *event)
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

void SCgSelectMode::mousePress(QGraphicsSceneMouseEvent *event)
{

    QPointF current_position = event->scenePos();
    QGraphicsItem *item = mScene->itemAt( event->scenePos() );

        if ( item )     // if not empty place
        {
            if ( item != mCurrentPointObject && SCgObject::isSCgPointObjectType( item->type() ) )
            {
                if ( mCurrentPointObject )
                {
                    mCurrentPointObject->destroyPointObjects();
                    mCurrentPointObject = NULL;
                }
                mCurrentPointObject = static_cast<SCgPointObject*>( item );
                if( mCurrentPointObject->shape().contains( mCurrentPointObject->mapFromScene( current_position ) ) )
                {
                    mCurrentPointObject->createPointObjects();
                }

            }
        }
        else
        {
            if ( mCurrentPointObject )
            {
                mCurrentPointObject->destroyPointObjects();
                mCurrentPointObject = NULL;
            }
        }

        /*QPainterPath p = mCurrentPointObject->shape();
        if(!p.contains(mCurrentPointObject->mapFromScene(event->scenePos())))
        {
            mCurrentPointObject->destroyPointObjects();
            mCurrentPointObject = 0;
        }*/

    // start cloning
    if (event->modifiers() == Qt::ShiftModifier && mScene->selectedItems().contains(mScene->objectAt(event->scenePos())))
        mScene->setEditMode(SCgScene::Mode_Clone);
}

void SCgSelectMode::mouseRelease(QGraphicsSceneMouseEvent *event)
{
    if(mIsItemsMoved)
    {
        //______________________________________________________//
        //Store finish positions (after items moving)
        SCgScene::ItemUndoInfo::iterator it = mUndoInfo.begin();
        for(; it != mUndoInfo.end(); ++it)
        {
            QGraphicsItem *item = it.key();
            SCgContour *newParent = 0;
            switch(item->type())
            {
            case SCgPointGraphicsItem::Type :
            case SCgIncidentPointGraphicsItem::Type :
            case SCgTextItem::Type:
            {
                // exclude PointGraphicsItem's object, because it always has a parent item
                it.value().second.second = item->pos();
                continue;
            }
            case SCgNode::Type : case SCgContour::Type :
            {
                newParent = findNearestParentContour(item);
                break;
            }
            case SCgBus::Type : {
                SCgNode* node = qgraphicsitem_cast<SCgBus*>(item)->owner();
                newParent = findNearestParentContour(node);
            }
            default : break;
            }
            QGraphicsItem *oldParent = item->parentItem();
            if (newParent) {// mapped item coordinates to new parent item
                if (oldParent)
                    it.value().second.second = oldParent->mapToItem(newParent, item->pos());
                else
                    it.value().second.second = newParent->mapFromScene(item->pos());

                it.value().second.first = newParent;
                item->setParentItem(newParent);
            }
            else
            {
                // we need check if items under cursor contain old parent item
                if (mScene->itemAt(item->scenePos()) != oldParent)
                {
                    it.value().second.second = item->scenePos();
                    item->setParentItem(0);
                    it.value().second.first = 0;
                }
                else
                    it.value().second.second = item->pos();
            }
        }
        //______________________________________________________//
        mScene->moveSelectedCommand(mUndoInfo);
        mIsItemsMoved = false;
        mUndoInfo.clear();
    }
}

void SCgSelectMode::clean()
{
    SCgMode::clean();
    mIsItemsMoved = false;
    mUndoInfo.clear();
    if (mCurrentPointObject)
        mCurrentPointObject->destroyPointObjects();
    mCurrentPointObject = 0;
}

SCgContour* SCgSelectMode::findNearestParentContour(QGraphicsItem *item)
{
    // get list of items, which have the same position
    QList<QGraphicsItem*> itemList = mScene->items(item->scenePos(), Qt::ContainsItemShape, Qt::AscendingOrder);
    // if item is a SCgNode we will move it to the end of the list
    if (item->type() == SCgNode::Type)
    {
        itemList.removeOne(item);
        itemList.push_back(item);
    }
    int index = itemList.indexOf(item);
    SCgContour *newParent = 0;
    // find nearest SCgContour according to stack order
    do
    {
        if (index <= 0) break;
        QGraphicsItem *tmpItem = itemList.at(--index);
        if (!item->childItems().contains(tmpItem) && tmpItem->type() == SCgContour::Type)
            newParent = dynamic_cast<SCgContour*>(tmpItem);
    } while(!newParent && index != 0);
    return newParent;
}
