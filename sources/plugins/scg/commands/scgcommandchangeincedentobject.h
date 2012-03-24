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


#ifndef SCGCOMMANDCHANGEINCEDENTOBJECT_H
#define SCGCOMMANDCHANGEINCEDENTOBJECT_H

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

//! Command for changing begin and end objects of pair and owner of bus.
class SCgCommandChangeIncedentObject: public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    role        Role for changing incident point (begin or end).
      @param    newObj      New object for given role
      @param    newPoint    New point position (used for calculating new dotPos)
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandChangeIncedentObject(SCgScene* scene,
                                            SCgPointObject* obj,
                                            SCgPointObject::IncidentRole role,
                                            SCgObject* newObj,
                                            const QPointF& newPoint,
                                            QUndoCommand* parent = 0);

    virtual ~SCgCommandChangeIncedentObject();

protected:
    void redo();
    void undo();

private:
    SCgPointObject::IncidentRole mRole;
    SCgObject* mOldObject;
    SCgObject* mNewObject;
    QPointF mNewPoint;
    QPointF mOldPoint;
};

#endif // SCGCOMMANDCHANGEINCEDENTOBJECT_H
