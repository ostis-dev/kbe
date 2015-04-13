/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


