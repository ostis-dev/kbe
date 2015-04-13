/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Command for moving points on SCgPointObject
class SCgCommandPointMove : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    pointIndex  Index of changed point
      @param    oldPos      Old point position
      @param    newPos      New point position
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandPointMove(   SCgScene* scene,
                                    SCgPointObject* obj,
                                    int pointIndex,
                                    const QPointF& oldPos,
                                    const QPointF& newPos,
                                    QUndoCommand* parent = 0);

    virtual ~SCgCommandPointMove();

protected:
    void redo();
    void undo();

private:
    int mPointIndex;
    QPointF mOldPos;
    QPointF mNewPos;
};


