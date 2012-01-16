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
                mUndoInfo[item] = qMakePair(p,p);
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
        while(it != mUndoInfo.end())
        {
            it.value().second = it.key()->pos();
            ++it;
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



