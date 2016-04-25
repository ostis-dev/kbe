/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandswappairorient.h"
#include "scgpair.h"

SCgCommandSwapPairOrient::SCgCommandSwapPairOrient(SCgScene *scene, SCgPair *pair, QUndoCommand *parent)
    : SCgBaseCommand(scene, pair, parent)
{
    setText(QObject::tr("Swap pair"));
}

SCgCommandSwapPairOrient::~SCgCommandSwapPairOrient()
{
}

void SCgCommandSwapPairOrient::redo()
{
    Q_ASSERT(mObject != 0 && mObject->type() == SCgPair::Type);
    static_cast<SCgPair*>(mObject)->swap();

    SCgBaseCommand::redo();
}

void SCgCommandSwapPairOrient::undo()
{
    Q_ASSERT(mObject != 0 && mObject->type() == SCgPair::Type);
    static_cast<SCgPair*>(mObject)->swap();

    SCgBaseCommand::undo();
}
