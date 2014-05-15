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

#ifndef SCGCOMMANDCONTENTCHANGE_H
#define SCGCOMMANDCONTENTCHANGE_H

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


#endif // SCGCOMMANDCONTENTCHANGE_H
