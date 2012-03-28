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


#ifndef SCGCOMMANDOBJECTDELETE_H
#define SCGCOMMANDOBJECTDELETE_H

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

/*! Object deletion command
  */
class SCgCommandObjectDelete : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to deleting object
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectDelete(SCgScene *scene,
                                    SCgObject *object,
                                    QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectDelete();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();
    //! List of deleted objects (object that was linked to deleting object)
    QList<SCgObject*> mDelList;
    //! Map of parent objects
    QMap<SCgObject*, QGraphicsItem*> mParents;
};

#endif // SCGCOMMANDOBJECTDELETE_H
