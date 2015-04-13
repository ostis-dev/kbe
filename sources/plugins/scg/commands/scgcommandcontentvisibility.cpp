/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandcontentvisibility.h"
#include "scgnode.h"

SCgCommandContentVisibility::SCgCommandContentVisibility(SCgScene *scene,
                                                         SCgNode *node,
                                                         bool visibility,
                                                         QUndoCommand *parent)
    : SCgBaseCommand(scene, node, parent)
    , mNode(node)
    , mVisibility(visibility)
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

SCgCommandAllContentVisibility::SCgCommandAllContentVisibility(SCgScene *scene, bool visibility, QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mVisibility(visibility)
{
    if(visibility)
        setText(QObject::tr("Show all content"));
    else
        setText(QObject::tr("Hide all content"));
}

SCgCommandAllContentVisibility::~SCgCommandAllContentVisibility()
{

}

void SCgCommandAllContentVisibility::redo()
{
    QList<QGraphicsItem*> items = mScene->items();
    SCgNode *node = 0;
    for(int i = 0; i < items.size(); ++i)
    {
        node = qgraphicsitem_cast<SCgNode*>(items.at(i));
        if (!node || !node->isContentData())
            continue;
        bool isVisible = node->isContentVisible();
        if(mVisibility)
        {
            if (!isVisible)
                node->showContent();
            else
                mUnchangedNodeList.append(node);
        }
        else
        {
            if (isVisible)
                node->hideContent();
            else
                mUnchangedNodeList.append(node);
        }
    }

    SCgBaseCommand::redo();
}

void SCgCommandAllContentVisibility::undo()
{
    QList<QGraphicsItem*> items = mScene->items();
    SCgNode *node = 0;
    for(int i = 0; i < items.size(); ++i)
    {
        node = qgraphicsitem_cast<SCgNode*>(items.at(i));
        if (!node || !node->isContentData())
            continue;
        if (mUnchangedNodeList.contains(node))
            continue;
        if (node && !mVisibility)
            node->showContent();
        else if(node && mVisibility)
            node->hideContent();
    }
    mUnchangedNodeList.clear();
    SCgBaseCommand::undo();
}
