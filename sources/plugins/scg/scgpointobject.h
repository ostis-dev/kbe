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
#ifndef SCGPOINTOBJECT_H
#define SCGPOINTOBJECT_H

#include "scgobject.h"

class SCgPointGraphicsItem;

//! Class for representing point objects.
//! Includes interface for controlling item geometry by point movement
class SCgPointObject : public SCgObject
{
public:
    enum IncidentRole
    {
        IncidentBegin = 0,
        IncidentEnd,
        IncidentRolesCount
    };

    virtual int type() const = 0;
    explicit SCgPointObject(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgPointObject();

    typedef QVector<QPointF> PointFVector;

    /*! Set points for an object.
      @param points Vector of points.
      @note All points must be mapped into scene coordinates
      @see SCgObject::points
      @see SCgObject::scenePoints
      */
    virtual void setPoints(const PointFVector &points);

    /*! Get points.
      @return returns vector of object's points (in this item's coordinates).
      */
    PointFVector points() const;

    /*! Get global points.
        @return Vector of points (points in scene transform space)
      */
    PointFVector scenePoints() const;

    //! @see SCgObject::updateConnected + updates position of points if needed.
    virtual void updateConnected();

    //! Creates point items for this object.
    void createPointObjects();
    //! Destroys point items for this object.
    void destroyPointObjects();

    /*! Changes point position. Point is given by it's index.
     *
     * @param pointIndex index of changed point.
     * @param newPos New point position in THIS ITEM coordinates.
     */
    virtual void changePointPosition(int pointIndex, const QPointF& newPos);

    //! Returns point at specified index (in THIS ITEM coordinates).
    QPointF pointAt(int index) const;

    //! updates shape of object without changing its points.
    virtual void updateShape() = 0;

    //! Returns normal path, without pen width affected.
    QPainterPath shapeNormal() const
    {
        return mShapeNormal;
    }

    //! Return line shape, used to work with points
    QPainterPath lineShape() const
    {
        return mLineShape;
    }

    /*! Returns true, if @p obj is acceptable for specified role.
     * e.g. this object can be begin or end object of pair, or owner for bus.
     * @see SCgPaur::isAcceptable; @see SCgBus::isAcceptable.
     */
    virtual bool isAcceptable(SCgObject* obj, IncidentRole role = IncidentBegin) const;

    //! Changes incident object for specified role.
    //! @see SCgPair::changeIncidentObject(). @see SCgBus::changeIncidentObject().
    virtual void changeIncidentObject(SCgObject* obj, const QPointF& point, IncidentRole role = IncidentBegin);

    //! only for objects, supported connecting to other objects.
    //! @see SCgPair::objectAtRole(). @see SCgBus::objectAtRole().
    virtual SCgObject* objectWithRole(IncidentRole role) const;

    //! only for objects, supported connecting to other objects.
    virtual qreal dotAtRole(IncidentRole role) const;

    /*! Look for the best place in vector for point. Checks all sectors and select the closest for given point.
     * @return Index for given point.
     * @param point Point to add. Point must be in THIS ITEM'S coordinates.
     * @param v Vector, with sectors.
     * @param closed True, if given vector represent closed subpath.
     */
    static int indexForPoint(const PointFVector& v, const QPointF& point,bool closed = false);

protected:
    //! Factory method;
    virtual SCgPointGraphicsItem* createPointItem(int pointIndex) = 0;
    //! List of created point graphics items.
    QList<SCgPointGraphicsItem*> mPointItems;
    //! Vector of object points
    PointFVector mPoints;
    //! Default Z value for this object
    qreal mDefaultZValue;
    //! Path that represents shape without any stroke (used for drawing)
    QPainterPath mShapeNormal;
    //! Line shape used to process contains function to line
    QPainterPath mLineShape;

private:
    static qreal distanceToSubpath(const QPointF& p0, const QPointF& p1, const QPointF& p);
};

#endif // SCGPOINTOBJECT_H
