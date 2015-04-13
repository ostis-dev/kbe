/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/*! Change content command
  */
class SCgCommandContentChange : public SCgBaseCommand
{
public:
    /*! Constructor
      */
    explicit SCgCommandContentChange(SCgScene *scene,
                                     SCgNode *node,
                                     const SCgContent::ContInfo &contInfo,
                                     QUndoCommand *parent = 0);
    virtual ~SCgCommandContentChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to sc.g-node for content changing
    SCgNode *mNode;
    //! Content information
    SCgContent::ContInfo mContentInfo;
    //! Old content information
    SCgContent::ContInfo mOldContentInfo;
    //! If content was visible before changing, holds true
    bool mContentVisibility;
};

