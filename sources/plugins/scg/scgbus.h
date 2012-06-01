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

#ifndef SCGBUS_H
#define SCGBUS_H

#include "scgpointobject.h"

class SCgNode;


class SCgBus : public SCgPointObject
{
public:
    enum { Type = UserType + 4 };

    explicit SCgBus();
    virtual ~SCgBus();

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    SCgPointGraphicsItem* createPointItem(int pointIndex);

public:
    /*! @see SCgObject::del(QList<SCgObject*> &delList)
      */
    void del(QList<SCgObject*> &delList);

    /*! @see SCgObject::undel(SCgScene *scene)
      */
    void undel(SCgScene *scene);

    void positionChanged();
    //! @see SCgPointObject::updateShape;
    void updateShape();
    //! @see SCgObject::objectDelete;
    void objectDelete(SCgObject *object);

    /*! Get bus width
      */
    float getWidth() const;

    /*! Set new bus owner.
        \param owner    Pointer to new owner object.
        @see SCgBus::owner
      */
    void setOwner(SCgNode *owner);

    /*! Get bus owner.
        \return Pointer to bus owner object.
        @see SCgBus::setOwner
      */
    SCgNode* owner() const;


    QPointF cross(const QPointF &from, float dot) const;
    float dotPos(const QPointF &point) const;
    int type() const { return Type; }

    //! Returns true, if @p obj is acceptable for specified role.
    //! Acceptable object mustn't be parent for this pair and pair mustn't be a loop.
    bool isAcceptable(SCgObject* obj, IncidentRole role = IncidentBegin) const;

    //! Changes incident object for specified role.
    void changeIncidentObject(SCgObject* obj, const QPointF& point, IncidentRole role = IncidentBegin);

    //! @see SCgPointObject::changePointPosition(int pointIndex, const QPointF& newPos)
    void changePointPosition(int pointIndex, const QPointF& newPos);

    SCgObject* objectWithRole(IncidentRole role) const;

private:
    //! Path that represents shape
    QPainterPath mShape;
    //! Width of bus
    float mWidth;
    //! Owner
    SCgNode *mOwner;
    //! Position for moving offset counting
    QPointF mOwnerPos;

};

#endif // SCGBUS_H
