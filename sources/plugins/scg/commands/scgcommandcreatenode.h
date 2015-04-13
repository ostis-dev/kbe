/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once
#include <QObject>
#include "scgbasecommand.h"

/*! sc.g-node creation command
  */
class SCgCommandCreateNode : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    point   Position in scene
      @param    parentContour   Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateNode(SCgScene *scene,
                                  const QPointF &point,
                                  SCgContour *parentContour,
                                  QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateNode();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Node position in scene
    QPointF mPoint;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void nodeDestroyed();
};


