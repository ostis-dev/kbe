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

#ifndef SCGCOMMANDDELETECONTOUR_H
#define SCGCOMMANDDELETECONTOUR_H

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

#endif // SCGCOMMANDDELETECONTOUR_H
