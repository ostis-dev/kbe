/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandobjectidtfchange.h"

SCgCommandObjectIdtfChange::SCgCommandObjectIdtfChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newIdtf,
                                                       QUndoCommand *parent)
        : SCgBaseCommand(scene, object, parent)
        , mNewIdtf(newIdtf)
{
    setText(QObject::tr("Change object's identifier"));
    mOldIdtf = mObject->idtfValue();
}

SCgCommandObjectIdtfChange::~SCgCommandObjectIdtfChange()
{

}

void SCgCommandObjectIdtfChange::redo()
{
    mObject->setIdtfValue(mNewIdtf);

    SCgBaseCommand::redo();
}

void SCgCommandObjectIdtfChange::undo()
{
    mObject->setIdtfValue(mOldIdtf);

    SCgBaseCommand::undo();
}
