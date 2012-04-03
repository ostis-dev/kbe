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

#ifndef SCGCOMMANDCONTENTVISIBILITY_H
#define SCGCOMMANDCONTENTVISIBILITY_H

#include "scgbasecommand.h"

class SCgCommandContentVisibility : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    node    Pointer to SCg-node for content show/hide
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

    //! Pointer to SCg-node for content show/hide
    SCgNode *mNode;
    //! Visibility flag
    bool mVisibility;
};

#endif // SCGCOMMANDCONTENTVISIBILITY_H
