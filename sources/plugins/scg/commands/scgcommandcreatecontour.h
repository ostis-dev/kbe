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

#ifndef SCGCOMMANDCREATECONTOUR_H
#define SCGCOMMANDCREATECONTOUR_H

#include <QObject>
#include "scgbasecommand.h"

/*! Contour creation command
  */
class SCgCommandCreateContour : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    childs  List of child objects (all child object will be added to contour)
      @param    points  Vector of contour points
      @param    parentContour   Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateContour(SCgScene *scene,
                                     const QList<QGraphicsItem*> &childs,
                                     const QVector<QPointF> &points,
                                     SCgContour *parentContour,
                                     QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateContour();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Contour points
    QVector<QPointF> mPoints;
    //! List of child object
    QList<QGraphicsItem*> mChildObjects;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void contourDestroyed();
};

#endif // SCGCOMMANDCREATECONTOUR_H
