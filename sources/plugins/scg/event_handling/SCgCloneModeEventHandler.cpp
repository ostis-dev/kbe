/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2012 OSTIS

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

#include "SCgCloneModeEventHandler.h"
#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgbus.h"
#include "../scgcontour.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsView>

SCgCloneModeEventHandler::SCgCloneModeEventHandler(SCgScene *scene) :
    SCgEventHandler(scene),
    mNoKey(0)
{
    //! TODO: value needs to be checked in another platforms
#if defined( __WIN32__ ) || defined( _WIN32 )
    mNoKey = 0x01000020;
#elif defined( __APPLE_CC__)
    mNoKey = 0x01000020;
#else
    mNoKey = 0x01000020;
#endif
}

SCgCloneModeEventHandler::~SCgCloneModeEventHandler() {}

void SCgCloneModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event) {
    SCgEventHandler::mouseMove(event);
    if(mScene->mInsertedObjectGroup)
        mScene->mInsertedObjectGroup->setPos(event->scenePos());

}

void SCgCloneModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event) {
    SCgEventHandler::mousePress(event);
    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;
    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);
    mScene->cloneCommand(parent);
    mList.clear();
    event->accept();
}

void SCgCloneModeEventHandler::keyPress(QKeyEvent *event) {
    if (event->modifiers() == Qt::ShiftModifier && event->key() == mNoKey) {
        mList.clear();
        QGraphicsView *view = mScene->views().first();
        QPointF point = view->mapToScene(view->mapFromGlobal(QCursor::pos()));
        QGraphicsItem *item = mScene->itemAt(point);
        if (item)
            switch (item->type()) {
            case QGraphicsProxyWidget::Type : item = item->parentItem();
            case SCgNode::Type : {
                qgraphicsitem_cast<SCgNode*>(item)->clone(mList);
                break;
            }
            case SCgPair::Type : {
                qgraphicsitem_cast<SCgPair*>(item)->clone(mList);
                break;
            }
            case SCgBus::Type : {
                qgraphicsitem_cast<SCgBus*>(item)->clone(mList);
                break;
            }
            case SCgContour::Type : {
                qgraphicsitem_cast<SCgContour*>(item)->clone(mList);
                break;
            }
            }
        QRectF bounds;
        foreach(SCgObject* obj, mList)
            bounds = bounds.united(obj->sceneBoundingRect());
        foreach(SCgObject* obj, mList)
        {
            if(! obj->parentItem())
                    obj->setPos(obj->pos() - bounds.topLeft());
        }
        mScene->cloneTemplate(mList);

        event->accept();
    }
}

void SCgCloneModeEventHandler::keyRelease(QKeyEvent *event) {
    if (event->modifiers() != Qt::ShiftModifier) {
        delete (mScene->mInsertedObjectGroup);
        mScene->mInsertedObjectGroup = 0;
        mList.clear();
        mScene->setEditMode(mScene->mPreviousEditMode);
    }
}
