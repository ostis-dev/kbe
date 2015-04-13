/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandidtfmove.h"
#include "scgtextitem.h"

SCgCommandIdtfMove::SCgCommandIdtfMove(SCgObject *obj,
                                       SCgScene *scene,
                                       const QPointF& oldPosition,
                                       const QPointF& newPosition,
                                       QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mObject(obj)
    , mOldPosition(oldPosition)
    , mNewPosition(newPosition)
{
    Q_ASSERT(obj);

    setText(QObject::tr("Move identifier"));
}

SCgCommandIdtfMove::~SCgCommandIdtfMove()
{
}

void SCgCommandIdtfMove::redo()
{
    if (mObject)
        mObject->setIdtfPos(mNewPosition);
    SCgBaseCommand::redo();
}

void SCgCommandIdtfMove::undo()
{
    if (mObject)
        mObject->setIdtfPos(mOldPosition);
    SCgBaseCommand::undo();
}
