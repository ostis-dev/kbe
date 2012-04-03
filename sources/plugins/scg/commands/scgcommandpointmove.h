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

#ifndef SCGCOMMANDPOINTMOVE_H
#define SCGCOMMANDPOINTMOVE_H

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

#endif // SCGCOMMANDPOINTMOVE_H
