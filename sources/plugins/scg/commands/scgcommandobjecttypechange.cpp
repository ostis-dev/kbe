/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandobjecttypechange.h"

SCgCommandObjectTypeChange::SCgCommandObjectTypeChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newType,
                                                       QUndoCommand *parent)
        : SCgBaseCommand(scene, object, parent)
        , mNewType(newType)
{
    setText(QObject::tr("Change object's type"));
    mOldType = mObject->typeAlias();
}

SCgCommandObjectTypeChange::~SCgCommandObjectTypeChange()
{

}

void SCgCommandObjectTypeChange::redo()
{
    mObject->setTypeAlias(mNewType);
    SCgBaseCommand::redo();
}

void SCgCommandObjectTypeChange::undo()
{
    mObject->setTypeAlias(mOldType);
    SCgBaseCommand::undo();
}
