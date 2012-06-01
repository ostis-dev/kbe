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

#include "scgcommandinsert.h"
#include "scgobject.h"
#include "scgcontour.h"

SCgCommandInsert::SCgCommandInsert(SCgScene *scene,
                                   QList<SCgObject*> objList,
                                   SCgContour* parentContour,
                                   QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mList(objList),
    mParent(parentContour)
{
    foreach(SCgObject* obj, mList)
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(objectFromListDestroyed(QObject*)));

    setText(QObject::tr("Insert"));
}

SCgCommandInsert::~SCgCommandInsert()
{
    foreach(SCgObject* obj, mList)
        delete obj;
}

void SCgCommandInsert::objectFromListDestroyed(QObject* obj)
{
    mList.removeOne((SCgObject*)obj);
}

void SCgCommandInsert::redo()
{
    SCgBaseCommand::redo();

    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;

        object->setDead(false);
        if(object->scene() != mScene)
            mScene->addItem(object);

        object->setParentItem(mParent);
        object->positionChanged();
    }
}

void SCgCommandInsert::undo()
{
    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;
        object->setDead(true);
        object->setParentItem(0);
        mScene->removeItem(object);
    }

    SCgBaseCommand::undo();
}
