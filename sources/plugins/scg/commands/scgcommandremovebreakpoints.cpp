/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
