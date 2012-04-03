/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#include "scgcommandcontentvisibility.h"
#include "scgnode.h"

SCgCommandContentVisibility::SCgCommandContentVisibility(SCgScene *scene,
                                                         SCgNode *node,
                                                         bool visibility,
                                                         QUndoCommand *parent) :
    SCgBaseCommand(scene, node, parent),
    mNode(node),
    mVisibility(visibility)
{
    Q_ASSERT_X(mNode != 0,
               "SCgCommandContentVisibility::SCgCommandContentVisibility(SCgScene *scene,"
               "SCgNode *node, bool visibility, QUndoCommand *parent)",
               "Pointer to node is null");

    setText(QObject::tr("Change content visibility"));
}

SCgCommandContentVisibility::~SCgCommandContentVisibility()
{

}

void SCgCommandContentVisibility::redo()
{
    if (mVisibility)
        mNode->showContent();
    else
        mNode->hideContent();

    SCgBaseCommand::redo();
}

void SCgCommandContentVisibility::undo()
{
    SCgBaseCommand::undo();

    if (!mVisibility)
        mNode->showContent();
    else
        mNode->hideContent();
}

