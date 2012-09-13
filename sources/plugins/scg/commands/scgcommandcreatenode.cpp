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

#include "scgcommandcreatenode.h"
#include "scgnode.h"
#include "scgcontour.h"

SCgCommandCreateNode::SCgCommandCreateNode(SCgScene *scene,
                                           const QPointF &point,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mPoint(point)
    , mParentContour(parentContour)
{
    mObject = mScene->createSCgNode(mPoint);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(nodeDestroyed()));

    setText(QObject::tr("Create node"));
}

SCgCommandCreateNode::~SCgCommandCreateNode()
{
    if(mObject)
        delete mObject;
}

void SCgCommandCreateNode::nodeDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateNode::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateNode::undo()",
               "Node doesn't exists");

    mObject->setParentItem(0);
    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}

void SCgCommandCreateNode::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateNode::redo()",
               "Node doesn't exists");

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setDead(false);

    if (mParentContour)
        mObject->setParentItem(mParentContour);

    SCgBaseCommand::redo();
}
