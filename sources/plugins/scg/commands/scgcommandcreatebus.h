/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include "scgbasecommand.h"

/*! sc.g-pair creation command
  */
class SCgCommandCreateBus : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    owner   SCgNode that is a bus owner
      @param    points  Vector of line points
      @param    owner   Pointer to owner object
      @param    parenContour    Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateBus(SCgScene *scene,
                                 SCgNode *owner,
                                 const QVector<QPointF> &points,
                                 SCgContour *parentContour,
                                 QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateBus();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Bus owner
    SCgNode *mOwner;
    //! Bus points
    QVector<QPointF> mPoints;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void busDestroyed();
};


