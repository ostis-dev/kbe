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

#include "scgcommandcreatecontour.h"
#include "scgcontour.h"

SCgCommandCreateContour::SCgCommandCreateContour(SCgScene *scene,
                                                 const QList<QGraphicsItem *> &childs,
                                                 const QVector<QPointF> &points,
                                                 SCgContour *parentContour,
                                                 QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mPoints(points)
    , mChildObjects(childs)
    , mParentContour(parentContour)
{
    Q_ASSERT(mScene);
    mObject = mScene->createSCgContour(mPoints);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(contourDestroyed()));
    setText(QObject::tr("Create contour"));
}

SCgCommandCreateContour::~SCgCommandCreateContour()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateContour::contourDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateContour::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::redo()",
               "Contour doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setDead(false);

    QList<QGraphicsItem*>::iterator it = mChildObjects.begin();
    for (; it != mChildObjects.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        (*it)->setParentItem(mObject);
    }

    if(mParentContour)
        mObject->setParentItem(mParentContour);
}

void SCgCommandCreateContour::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::undo()",
               "Contour doesn't exists");

    QGraphicsItem *parent = mObject->parentItem();
    QList<QGraphicsItem*> childs = mObject->childItems();
    QList<QGraphicsItem*>::iterator it = childs.begin();
    for (; it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        item->setParentItem(parent);
    }

    mObject->setParentItem(0);
    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
