/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"
#include "../scgpointobject.h"

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


