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

#include "scgcommandcreatebus.h"
#include "scgnode.h"
#include "scgcontour.h"
#include "scgbus.h"

SCgCommandCreateBus::SCgCommandCreateBus(SCgScene *scene,
                                           SCgNode *owner,
                                           const QVector<QPointF> &points,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mOwner(owner),
    mPoints(points),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgBus(mPoints, mOwner);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(busDestroyed()));
    setText(QObject::tr("Create bus"));
}

SCgCommandCreateBus::~SCgCommandCreateBus()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateBus::busDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateBus::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::redo()",
               "Bus doesn't exists");
    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setParentItem(mParentContour);
    mObject->setDead(false);

    static_cast<SCgBus*>(mObject)->setOwner(mOwner);
}

void SCgCommandCreateBus::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::undo()",
               "Bus doesn't exists");

    static_cast<SCgBus*>(mObject)->setOwner(0);
    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
