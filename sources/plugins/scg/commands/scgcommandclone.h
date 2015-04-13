/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgcommandinsert.h"

/*! Object cloning command
  */
class SCgCommandClone : public SCgCommandInsert
{
    Q_OBJECT
public:
    /*! Constructor
      @param scene          Pointer to SCgScene that will be used for command working
      @param objList        List of inserted objects
      @param parentContour  Pointer to parent contour (if 0 then parent is scene).
      @param parent         Pointer to parent command
      */
    explicit SCgCommandClone(SCgScene *scene,
                              QList<SCgObject*> objList,
                              SCgContour* parentContour,
                              QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandClone();

protected:
    //! @see    SCgCommandInsert::redo
    void redo();
    //! @see    SCgCommandInsert::undo
    void undo();
};
