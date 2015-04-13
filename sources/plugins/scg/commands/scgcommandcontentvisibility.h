/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

class SCgCommandContentVisibility : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    node    Pointer to sc.g-node for content show/hide
      @param    visibility    Visibility flag
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandContentVisibility(SCgScene *scene,
                                         SCgNode *node,
                                         bool visibility,
                                         QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandContentVisibility();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to sc.g-node for content show/hide
    SCgNode *mNode;
    //! Visibility flag
    bool mVisibility;
};

class SCgCommandAllContentVisibility : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    visibility    Visibility flag
      @param    parent  Pointer to parent command
    */
    explicit SCgCommandAllContentVisibility(SCgScene *scene, bool visibility, QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandAllContentVisibility();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

private:
    //! Visibility flag
    bool mVisibility;
    QList<SCgNode*> mUnchangedNodeList;
};


