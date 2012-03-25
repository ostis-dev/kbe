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


#ifndef SCGCOMMANDCREATENODE_H
#define SCGCOMMANDCREATENODE_H

#include <QUndoCommand>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QPair>

#include "../scgcontent.h"
#include "../scgpointobject.h"
#include "../scgscene.h"


class SCgObject;
class SCgNode;
class SCgPair;
class SCgContour;
class SCgBus;

class QGraphicsScene;
class QGraphicsItem;

/*! SCg-node creation command
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

#endif // SCGCOMMANDCREATENODE_H
