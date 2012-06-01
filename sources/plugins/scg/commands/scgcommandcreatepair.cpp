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

#include "scgcommandcreatepair.h"
#include "scgpair.h"
#include "scgcontour.h"

SCgCommandCreatePair::SCgCommandCreatePair(SCgScene *scene,
                                           const QVector<QPointF> &points,
                                           SCgObject *beginObject,
                                           SCgObject *endObject,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoints(points),
    mBeginObject(beginObject),
    mEndObject(endObject),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgPair(mBeginObject, mEndObject, mPoints);

    connect(mObject, SIGNAL(destroyed()), this, SLOT(pairDestroyed()));
    setText(QObject::tr("Create pair"));
}

SCgCommandCreatePair::~SCgCommandCreatePair()
{
    if(mObject)
        delete mObject;
}

void SCgCommandCreatePair::pairDestroyed()
{
    mObject = 0;
}

void SCgCommandCreatePair::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::redo()",
               "Pair doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setDead(false);

    if(mParentContour)
        mObject->setParentItem(mParentContour);

    mObject->positionChanged();

}

void SCgCommandCreatePair::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::undo()",
               "Pair doesn't exists");

    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
