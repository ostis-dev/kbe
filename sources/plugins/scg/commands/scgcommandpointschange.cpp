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

#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgcontour.h"
#include "../scgbus.h"
#include "../scgscene.h"

SCgCommandPointsChange::SCgCommandPointsChange(SCgScene* scene,
                                                SCgPointObject* obj,
                                                const QVector<QPointF>& newPoints,
                                                QUndoCommand* parent):
            SCgBaseCommand(scene, obj, parent),
            mOldPoints(obj->points()),
            mNewPoints(newPoints)
{
    setText(QObject::tr("Change object's points"));
    if(obj->type() == SCgPair::Type)
    {
        mIsPair = true;
        mOldBeginDot = ((SCgPair*)obj)->getBeginDot();
        mOldEndDot = ((SCgPair*)obj)->getEndDot();
    }else
        mIsPair = false;
}

SCgCommandPointsChange::~SCgCommandPointsChange()
{

}

void SCgCommandPointsChange::redo()
{
    SCgBaseCommand::redo();
    ((SCgPointObject*)mObject)->setPoints(mNewPoints);
}

void SCgCommandPointsChange::undo()
{
    ((SCgPointObject*)mObject)->setPoints(mOldPoints);
    if(mIsPair)
    {
        ((SCgPair*)mObject)->setBeginDot(mOldBeginDot);
        ((SCgPair*)mObject)->setEndDot(mOldEndDot);
    }
    SCgBaseCommand::undo();
}
