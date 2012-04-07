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

#ifndef SCGCOMMANDCREATEPAIR_H
#define SCGCOMMANDCREATEPAIR_H

#include "scgbasecommand.h"

/*! sc.g-pair creation command
  */
class SCgCommandCreatePair : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    points  Vector of line points (exluding incident points)
      @param    beginObject Pointer to begin object
      @param    endObject   Pointer to end object
      @param    parenContour    Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreatePair(SCgScene *scene,
                                  const QVector<QPointF> &points,
                                  SCgObject *beginObject,
                                  SCgObject *endObject,
                                  SCgContour *parentContour,
                                  QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreatePair();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Line point (excluding incedent points)
    QVector<QPointF> mPoints;
    //! Pointer to begin object
    SCgObject *mBeginObject;
    //! Pointer to end object
    SCgObject *mEndObject;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void pairDestroyed();
};

#endif // SCGCOMMANDCREATEPAIR_H
