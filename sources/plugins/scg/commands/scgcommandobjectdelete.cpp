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

#include "scgcommandobjectdelete.h"
#include "scgobject.h"

SCgCommandObjectDelete::SCgCommandObjectDelete(SCgScene *scene,
                                               SCgObject *object,
                                               QUndoCommand *parent) :
        SCgBaseCommand(scene, object, parent)
{
    setText(QObject::tr("Delete object"));
}

SCgCommandObjectDelete::~SCgCommandObjectDelete()
{

}

void SCgCommandObjectDelete::redo()
{
    mDelList.clear();
    mParents.clear();

    mObject->del(mDelList);

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        QGraphicsItem *parent = object->parentItem();

        mParents[object] = parent;

        if(object->scene() == mScene)
        {
            object->setParentItem(0);
            mScene->removeItem(object);
        }
    }

    SCgBaseCommand::redo();
}
//back
void SCgCommandObjectDelete::undo()
{
    SCgBaseCommand::undo();

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        if(!object->parentItem())
        {
            QGraphicsItem *parent = mParents[object];

            object->undel(mScene);

            object->setParentItem(parent);
            object->positionChanged();
        }
    }

}
