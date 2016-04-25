/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandpointschange.h"

#include "scgpair.h"

SCgCommandPointsChange::SCgCommandPointsChange(SCgScene* scene,
                                                SCgPointObject* obj,
                                                const QVector<QPointF>& newPoints,
                                                QUndoCommand* parent)
            : SCgBaseCommand(scene, obj, parent)
            , mOldPoints(obj->scenePoints())
            , mNewPoints(newPoints)
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
