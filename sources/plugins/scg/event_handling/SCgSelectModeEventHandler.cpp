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
#include "../gwf/gwffilewriter.h"
#include "../gwf/gwfobjectinforeader.h"
#include "../scgtemplateobjectbuilder.h"
#include "../scgview.h"
#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgbus.h"
#include "../scgcontour.h"
#include "../pointgraphicsitem.h"
#include "../ballontypetoolbar.h"

#include <QDomDocument>
#include <QToolBar>

SCgSelectModeEventHandler::SCgSelectModeEventHandler(SCgScene* parent):SCgEventHandler(parent),
    mIsItemsMoved(false),
    mCurrentPointObject(0)
{
    mEditBar = new BallonTypeToolBar;
}

SCgSelectModeEventHandler::~SCgSelectModeEventHandler()
{
    delete mEditBar;
    //    clean();
}

void SCgSelectModeEventHandler::activate()
{
    QList<QToolBar*> barsList = mEditBar->toolBarsList();
    SCgView *view = static_cast<SCgView*>(mScene->views().at(0));
    foreach (QToolBar *bar, barsList)
    {
        connect(bar, SIGNAL(actionTriggered(QAction*)), view, SLOT(changeType(QAction*)));
    }
}

void SCgSelectModeEventHandler::deactivate()
{
    QList<QToolBar*> barsList = mEditBar->toolBarsList();
    SCgView *view = static_cast<SCgView*>(mScene->views().at(0));
    foreach (QToolBar *bar, barsList)
    {
        disconnect(bar, SIGNAL(actionTriggered(QAction*)), view, SLOT(changeType(QAction*)));
    }

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
        }
        else
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

    if (event->modifiers() == Qt::ShiftModifier && mScene->selectedItems().contains(mScene->objectAt(event->scenePos())))
        mScene->setEditMode(SCgScene::Mode_Clone);

    if (event->modifiers() == Qt::NoModifier &&
            event->button() == Qt::LeftButton &&
            mScene->selectedItems().size() == 1)
    {
        QGraphicsItem *selItem = mScene->itemAt(event->scenePos());
        // add edit bar to the scene in case if it hasn't been added earlier; if we have one
        // selected item and item has corresponding type
        if (selItem && selItem->isSelected() &&
                (selItem->type() == SCgNode::Type || selItem->type() == SCgPair::Type) &&
                !mEditBar->scene())
        {
            mEditBar->setParentItem(selItem);
            mEditBar->setToolBarForType(selItem->type());
            mScene->addItem(mEditBar);
            mEditBar->editToolBarsStateChanged();
            QPointF editBarPos;
            if (selItem->type() == SCgNode::Type)
                editBarPos = QPointF(selItem->boundingRect().width() + 10,
                                     -(mEditBar->rect().height() + 10));
            if (selItem->type() == SCgPair::Type)
            {
                SCgPair *pair = static_cast<SCgPair*>(selItem);
                QPointF itemPos = (pair->endObject()->scenePos() + pair->beginObject()->scenePos()) / 2.f;
                editBarPos = itemPos + QPointF(10, -(mEditBar->rect().height() + 10));
            }
            mEditBar->setPos(editBarPos);
            connect(static_cast<SCgObject*>(selItem),
                    SIGNAL(typeChanged()),
                    mEditBar,
                    SLOT(editToolBarsStateChanged()));
        }
        else if (mEditBar->scene() == mScene &&
                 !mEditBar->sceneBoundingRect().contains(event->scenePos()))
        {
            disconnect(static_cast<SCgObject*>(mEditBar->parentItem()),
                       SIGNAL(typeChanged()),
                       mEditBar,
                       SLOT(editToolBarsStateChanged()));
            mEditBar->setParentItem(0);
            mScene->removeItem(mEditBar);
            mEditBar->editToolBarsStateChanged();
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
        for(; it != mUndoInfo.end(); ++it)
        {
            QGraphicsItem *item = it.key();
            SCgContour *newParent = 0;
            switch(item->type())
            {
            case PointGraphicsItem::Type :
            case IncidencePointGraphicsItem::Type :
            case SCgTextItem::Type :
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

void SCgSelectModeEventHandler::clean()
{
    SCgEventHandler::clean();
    mIsItemsMoved = false;
    mUndoInfo.clear();
    if (mCurrentPointObject)
        mCurrentPointObject->destroyPointObjects();
    mCurrentPointObject = 0;
}

SCgContour* SCgSelectModeEventHandler::findNearestParentContour(QGraphicsItem *item)
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
