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


#include "scgcommandchangeincedentobject.h"

#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgcontour.h"
#include "../scgbus.h"
#include "../scgscene.h"

SCgCommandChangeIncedentObject::SCgCommandChangeIncedentObject(SCgScene* scene,
                                                                SCgPointObject* obj,
                                                                SCgPointObject::IncidentRole role,
                                                                SCgObject* newObj,
                                                                const QPointF& newPoint,
                                                                QUndoCommand* parent):
                                            SCgBaseCommand(scene, obj, parent),
                                            mRole(role),
                                            mOldObject(obj->objectWithRole(role)),
                                            mNewObject(newObj),
                                            mNewPoint(newPoint)
{
    setText(QObject::tr("Change incident object"));
    int i = role == SCgPointObject::IncidentBegin ? 1 : obj->points().size() - 1;
    if(mOldObject)
        mOldPoint = obj->mapFromScene(mOldObject->cross(obj->mapToScene(obj->pointAt(i)), obj->dotAtRole(role)));
    else
        mOldPoint = obj->pointAt(0);
}

SCgCommandChangeIncedentObject::~SCgCommandChangeIncedentObject()
{

}

void SCgCommandChangeIncedentObject::redo()
{
    ((SCgPointObject*)mObject)->changeIncidentObject(mNewObject, mNewPoint, mRole);
    SCgBaseCommand::redo();
}

void SCgCommandChangeIncedentObject::undo()
{
    SCgBaseCommand::undo();
    ((SCgPointObject*)mObject)->changeIncidentObject(mOldObject, mOldPoint, mRole);
}

