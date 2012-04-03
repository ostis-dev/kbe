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

#include "scgcommandcontentchange.h"

#include "scgnode.h"

SCgCommandContentChange::SCgCommandContentChange(SCgScene *scene,
                                                 SCgNode *node,
                                                 const SCgContent::ContInfo &contInfo,
                                                 QUndoCommand *parent):
    SCgBaseCommand(scene, mNode, parent),
    mNode(node),
    mContentInfo(contInfo)
{
    setText(QObject::tr("Change content"));
    mContentVisibility = mNode->isContentVisible();
}

SCgCommandContentChange::~SCgCommandContentChange()
{

}

void SCgCommandContentChange::redo()
{
    mNode->contentInfo(mOldContentInfo);

    mNode->setContent(mContentInfo.mimeType,
                      mContentInfo.data,
                      mContentInfo.fileName,
                      mContentInfo.type);

    SCgBaseCommand::redo();
}

void SCgCommandContentChange::undo()
{
    SCgBaseCommand::undo();

    mNode->setContent(mOldContentInfo.mimeType,
                      mOldContentInfo.data,
                      mOldContentInfo.fileName,
                      mOldContentInfo.type);

    if(!mNode->isContentVisible() && mContentVisibility)
        mNode->showContent();
}

