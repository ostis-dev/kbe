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

#include "SCgInsertModeEventHandler.h"
#include "../scgcontour.h"

SCgInsertModeEventHandler::SCgInsertModeEventHandler(SCgScene* parent):
                                                            SCgEventHandler(parent)
{
}

SCgInsertModeEventHandler::~SCgInsertModeEventHandler()
{
    clean();
}

void SCgInsertModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mousePress(event);
    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;
    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);
    mScene->pasteCommand(parent);
}

void SCgInsertModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mouseMove(event);
    if(mScene->mInsertedObjectGroup)
        mScene->mInsertedObjectGroup->setPos(event->scenePos());
}

void SCgInsertModeEventHandler::keyPress(QKeyEvent *event)
{
    SCgEventHandler::keyPress(event);
    if(event->key() == Qt::Key_Escape)
    {
        clean();
        mScene->setEditMode(mScene->mPreviousEditMode);
        event->accept();
    }
}

void SCgInsertModeEventHandler::clean()
{
    SCgEventHandler::clean();
    if (mScene->mInsertedObjectGroup)
    {
        delete(mScene->mInsertedObjectGroup);
        mScene->mInsertedObjectGroup = 0;
    }
}

