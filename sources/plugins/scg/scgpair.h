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

#ifndef SCGPAIR_H
#define SCGPAIR_H

#include "scgpointobject.h"
#include "scgalphabet.h"

#include <QPainterPath>


class SCgPair : public SCgPointObject
{
public:
    enum { Type = UserType + 3 };

    explicit SCgPair();
    virtual ~SCgPair();

    /* begin & end objects */
    void setBeginObject(SCgObject *object);
    SCgObject* getBeginObject() const;

    void setEndObject(SCgObject *object);
    SCgObject* getEndObject() const;

    /* dot positions */
    void setBeginDot(float pos);
    float getBeginDot() const;

    void setEndDot(float pos);
    float getEndDot() const;

    /*! Set points for a pair.
      @param points reference to vector that contains points for a pair.

      @see SCgPair::getPoints
      */
    void setPoints(const PointFVector &points);

    /*! Returns normal path, without pen width affected.
      */
    QPainterPath shapeNormal() const;

    //! @see SCgPointObject::updateShape;
    void updateShape();

    /*! Changes point position by specified index of this point.
     *
     * @param pointIndex index of changed point.
     * @param newPos New point position in THIS ITEM coordinates.
     * NOTE: The incidence objects for pair can be changed by calling this function
     */
    void changePointPosition(int pointIndex, const QPointF& newPos);

    //! Returns true, if @p obj is acceptable for specified role.
    //! Acceptable object mustn't be parent for this pair and pair mustn't be a loop.
    bool isAcceptable(SCgObject* obj, IncidentRole role = IncidentBegin) const;
    //! Changes incident object for specified role.
    void changeIncidentObject(SCgObject* obj, const QPointF& point, IncidentRole role = IncidentBegin);
    //! Returns object at specified role. If there is no object at this role, 0 is returned.
    SCgObject* objectWithRole(IncidentRole role) const;
    //! only for objects, supported connecting to other objects.
    qreal dotAtRole(IncidentRole role) const
    {
        if(role == IncidentBegin)
            return mBeginDot;
        else
            return mEndDot;
    }

protected:
    //! @see QGraphicsItem::boundingRect
    QRectF boundingRect() const;
    //! @see QGraphicsItem::shape()
    QPainterPath shape() const;
    //! @see QGraphicsItem::paint()
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //! @see SCgObject::objectDelete(). DEPRECATED
    void objectDelete(SCgObject *object);
    //! Factory method for creating point item by index.
    PointGraphicsItem* createPointItem(int pointIndex);
public:
    int type() const { return Type; }

private:
    void updateType();

public:
    //! Updates position for points
    void updatePosition();
    QPointF cross(const QPointF &from, float dot) const;
    //! @see SCgObject::dotPos
    float dotPos(const QPointF &point) const;

public:
    void setTypeAlias(const QString &typeAlias);

    //! Get positive type
    SCgAlphabet::SCgPosType getPosType() const { return mPosType; }
    //! Get permanency type
    SCgAlphabet::SCgPermType getPermType() const { return mPermType; }
    //! Check if pair is orient
    bool isOrient() const   { return mOrient; }



private:
    SCgObject *mBeginObject;
    float mBeginDot;
    SCgObject *mEndObject;
    float mEndDot;
    //! Cached value of bounding box
    QRectF mBoundRect;
    //! Path that represents shape
    QPainterPath mShape;

    //! Flag for a end arrow
    bool mEndArrow;

    //! Positive type
    SCgAlphabet::SCgPosType mPosType;
    //! Permanency type
    SCgAlphabet::SCgPermType mPermType;
    //! Orientation flag
    bool mOrient;

};

#endif // SCGPAIR_H
