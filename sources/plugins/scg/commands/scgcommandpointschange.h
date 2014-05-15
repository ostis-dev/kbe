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

#ifndef SCGCOMMANDPOINTSCHANGE_H
#define SCGCOMMANDPOINTSCHANGE_H

#include "scgbasecommand.h"

//! Command for changing points on SCgPointObject
class SCgCommandPointsChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    newPoints   Points will be set;
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandPointsChange(   SCgScene* scene,
                                    SCgPointObject* obj,
                                    const QVector<QPointF>& newPoints,
                                    QUndoCommand* parent = 0);

    virtual ~SCgCommandPointsChange();

protected:
    void redo();
    void undo();

private:
    bool mIsPair;
    double mOldEndDot;
    double mOldBeginDot;
    QVector<QPointF> mOldPoints;
    QVector<QPointF> mNewPoints;
};

#endif // SCGCOMMANDPOINTSCHANGE_H
