/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/*! Object deletion command
  */
class SCgCommandObjectDelete : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to deleting object
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectDelete(SCgScene *scene,
                                    SCgObject *object,
                                    QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectDelete();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();
    //! List of deleted objects (object that was linked to deleting object)
    QList<SCgObject*> mDelList;
    //! Map of parent objects
    QMap<SCgObject*, QGraphicsItem*> mParents;
};


