/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandminimizecontour.h"

#include "scgcontour.h"

SCgCommandMinimizeContour::SCgCommandMinimizeContour(SCgScene *scene,
                                                     SCgContour *contour,
                                                     QUndoCommand *parent)
    : SCgBaseCommand(scene, contour, parent)
    , mOldPoints(contour->scenePoints())
    , mNewPoints(contour->minimizedPoints())
{
    setText(QObject::tr("Minimize contour's size"));
}

SCgCommandMinimizeContour::~SCgCommandMinimizeContour()
{
}

void SCgCommandMinimizeContour::redo()
{
    SCgBaseCommand::redo();

    static_cast<SCgContour *>(mObject)->setPoints(mNewPoints);
}

void SCgCommandMinimizeContour::undo()
{
    static_cast<SCgContour *>(mObject)->setPoints(mOldPoints);

    SCgBaseCommand::undo();
}
