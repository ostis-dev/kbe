/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandobjectmove.h"

SCgCommandObjectMove::SCgCommandObjectMove( SCgScene *scene,
                                            SCgObject* obj,
                                            const QPointF& oldPos,
                                            const QPointF& newPos,
                                            QUndoCommand *parent)
        : SCgBaseCommand(scene, obj, parent)
        , mOldPosition(oldPos)
        , mNewPosition(newPos)
{
    setText(QObject::tr("Move item"));
}

SCgCommandObjectMove::~SCgCommandObjectMove()
{

}

void SCgCommandObjectMove::redo()
{
    SCgBaseCommand::redo();
    mObject->setPos(mNewPosition);
}

void SCgCommandObjectMove::undo()
{
    SCgBaseCommand::undo();
    mObject->setPos(mOldPosition);
}

