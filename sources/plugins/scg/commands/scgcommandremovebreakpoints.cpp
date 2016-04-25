/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgpair.h"
#include "scgcontour.h"

#include "scgcommandremovebreakpoints.h"

SCgCommandRemoveBreakPoints::SCgCommandRemoveBreakPoints(SCgScene *scene, SCgPair *pair, QUndoCommand *parent)
    : SCgBaseCommand(scene, pair, parent)
    , mOldBeginDot(pair->beginDot())
    , mOldEndDot(pair->endDot())
    , mOldPoints(pair->scenePoints())
{
    setText(QObject::tr("Remove pair's break points"));
}

SCgCommandRemoveBreakPoints::~SCgCommandRemoveBreakPoints()
{
}

void SCgCommandRemoveBreakPoints::redo()
{
    SCgBaseCommand::redo();

    SCgPair *pair = static_cast<SCgPair *>(mObject);
    QVector<QPointF> newPoints;
    newPoints << pair->scenePoints().first()
              << pair->scenePoints().last();
    static_cast<SCgPair *>(mObject)->setPoints(newPoints);
}

void SCgCommandRemoveBreakPoints::undo()
{
    static_cast<SCgPair *>(mObject)->setPoints(mOldPoints);

    static_cast<SCgPair*>(mObject)->setBeginDot(mOldBeginDot);
    static_cast<SCgPair*>(mObject)->setEndDot(mOldEndDot);

    SCgBaseCommand::undo();
}
