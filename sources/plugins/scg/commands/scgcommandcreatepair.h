/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
