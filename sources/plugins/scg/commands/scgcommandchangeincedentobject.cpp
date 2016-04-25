/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandchangeincedentobject.h"

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
    static_cast<SCgPointObject*>(mObject)->changeIncidentObject(mNewObject, mNewPoint, mRole);
    SCgBaseCommand::redo();
}

void SCgCommandChangeIncedentObject::undo()
{
    SCgBaseCommand::undo();
    static_cast<SCgPointObject*>(mObject)->changeIncidentObject(mOldObject, mOldPoint, mRole);
}

