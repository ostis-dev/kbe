/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandpointmove.h"
#include "scgpointobject.h"

SCgCommandPointMove::SCgCommandPointMove(SCgScene* scene,
                                        SCgPointObject* obj,
                                        int pointIndex,
                                        const QPointF& oldPos,
                                        const QPointF& newPos,
                                        QUndoCommand* parent)
    : SCgBaseCommand(scene, obj, parent)
    , mPointIndex(pointIndex)
    , mOldPos(oldPos)
    , mNewPos(newPos)
{
    setText(QObject::tr("Move object's point"));
}

SCgCommandPointMove::~SCgCommandPointMove()
{

}

void SCgCommandPointMove::redo()
{
    SCgBaseCommand::redo();
    static_cast<SCgPointObject*>(mObject)->changePointPosition(mPointIndex, mNewPos);
}
void SCgCommandPointMove::undo()
{
    static_cast<SCgPointObject*>(mObject)->changePointPosition(mPointIndex, mOldPos);
    SCgBaseCommand::undo();
}
