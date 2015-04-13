/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandclone.h"

SCgCommandClone::SCgCommandClone(SCgScene *scene,
                                 QList<SCgObject *> objList,
                                 SCgContour *parentContour,
                                 QUndoCommand *parent)
    : SCgCommandInsert(scene, objList, parentContour, parent)
{
    setText(QObject::tr("Clone"));
}

SCgCommandClone::~SCgCommandClone()
{
}

void SCgCommandClone::redo()
{
    SCgCommandInsert::redo();
}

void SCgCommandClone::undo()
{
    SCgCommandInsert::undo();
}
