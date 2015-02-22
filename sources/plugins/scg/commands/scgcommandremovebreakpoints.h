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

#include "scgbasecommand.h"

#ifndef SCGCOMMANDREMOVEBREAKPOINTS_H
#define SCGCOMMANDREMOVEBREAKPOINTS_H

//! Command for removing break points of pairs.
class SCgCommandRemoveBreakPoints : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    pair        Pair which will be removed break points
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandRemoveBreakPoints(SCgScene *scene,
                                         SCgPair *pair,
                                         QUndoCommand *parent = 0);
    virtual ~SCgCommandRemoveBreakPoints();

protected:
    void redo();
    void undo();

private:
    double mOldBeginDot;
    double mOldEndDot;
    QVector<QPointF> mOldPoints;
};

#endif // SCGCOMMANDREMOVEBREAKPOINTS_H
