/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/*! Contour deletion command
  */
class SCgCommandDeleteContour : public SCgBaseCommand
{
public:
    /*! Constructor
        @param  scene   Pointer to SCgScene that will be used for command working
        @param  contour Pointer to contour that need to be deleted
        @param  parent  Pointer to parent command
      */
    explicit SCgCommandDeleteContour(SCgScene *scene,
                                     SCgContour *contour,
                                     QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandDeleteContour();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to deleted contour
    SCgContour *mContour;
    //! List of child objects
    QList<QGraphicsItem*> mChilds;
};


