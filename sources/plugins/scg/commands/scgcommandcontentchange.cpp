/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandcontentchange.h"

#include "scgnode.h"

SCgCommandContentChange::SCgCommandContentChange(SCgScene *scene,
                                                 SCgNode *node,
                                                 const SCgContent::ContInfo &contInfo,
                                                 QUndoCommand *parent)
    : SCgBaseCommand(scene, mNode, parent)
    , mNode(node)
    , mContentInfo(contInfo)
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

