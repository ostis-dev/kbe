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


#ifndef SCGCOMMANDCREATEBUS_H
#define SCGCOMMANDCREATEBUS_H

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

/*! SCg-pair creation command
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

#endif // SCGCOMMANDCREATEBUS_H
