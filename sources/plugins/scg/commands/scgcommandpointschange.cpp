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

#include "scgcommandpointschange.h"

#include "scgpair.h"

SCgCommandPointsChange::SCgCommandPointsChange(SCgScene* scene,
                                                SCgPointObject* obj,
                                                const QVector<QPointF>& newPoints,
                                                QUndoCommand* parent):
            SCgBaseCommand(scene, obj, parent),
            mOldPoints(obj->scenePoints()),
            mNewPoints(newPoints)
{
    setText(QObject::tr("Change object's points"));
    if(obj->type() == SCgPair::Type)
    {
        mIsPair = true;
        mOldBeginDot = static_cast<SCgPair*>(obj)->beginDot();
        mOldEndDot = static_cast<SCgPair*>(obj)->endDot();
    }
    else
        mIsPair = false;
}

SCgCommandPointsChange::~SCgCommandPointsChange()
{

}

void SCgCommandPointsChange::redo()
{
    SCgBaseCommand::redo();
    static_cast<SCgPointObject*>(mObject)->setPoints(mNewPoints);
}

void SCgCommandPointsChange::undo()
{
    static_cast<SCgPointObject*>(mObject)->setPoints(mOldPoints);
    if(mIsPair)
    {
        static_cast<SCgPair*>(mObject)->setBeginDot(mOldBeginDot);
        static_cast<SCgPair*>(mObject)->setEndDot(mOldEndDot);
    }
    SCgBaseCommand::undo();
}
