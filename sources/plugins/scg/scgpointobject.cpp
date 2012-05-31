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

#include "scgpointobject.h"
#include "scgpointgraphicsitem.h"

#include <QVector2D>

////////////////////////////////////////////////////////////////////////////////////////////////////
SCgPointObject::SCgPointObject(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgObject(parent, scene)
{

}

SCgPointObject::~SCgPointObject()
{
}

SCgPointObject::PointFVector SCgPointObject::points() const
{
    return mPoints;
}

SCgPointObject::PointFVector SCgPointObject::scenePoints() const
{
    return mapToScene(mPoints);
}

void SCgPointObject::updateConnected()
{
    if(!mPointItems.empty())
    {
        foreach(SCgPointGraphicsItem* p, mPointItems)
            p->setPos(mPoints.at(p->pointIndex()));
    }
    SCgObject::updateConnected();
}

void SCgPointObject::createPointObjects()
{
    int i = mPoints.size() - 1;
    while(i >= 0)
    {
        SCgPointGraphicsItem* p = createPointItem(i);
        mPointItems.push_front(p);
        --i;
    }
    setZValue(100);
}

void SCgPointObject::destroyPointObjects()
{
    foreach(SCgPointGraphicsItem* p, mPointItems)
        delete p;
    mPointItems.clear();
    setZValue(mDefaultZValue);
}

void SCgPointObject::changePointPosition(int pointIndex, const QPointF& newPos)
{
    Q_ASSERT_X(pointIndex > -1 && pointIndex < mPoints.size(),
                "void SCgPointObject::changePointPosition(int pointIndex, const QPointF& newPos)",
                "invalid point index");
    mPoints[pointIndex] = newPos;
}


void SCgPointObject::setPoints(const PointFVector &points)
{
    if(points.size() < 2)
        return;

    mPoints = points;
    for (quint32 idx = 0; idx < mPoints.size(); idx++)
        mPoints[idx] = mapFromScene(mPoints[idx]);
    //////////////////////////////////////////////////
    // update points if they're displayed
    if(!mPointItems.empty())
    {
        destroyPointObjects();
        createPointObjects();
    }
    ///////////////////////////////////////////////////
    positionChanged();
}

qreal SCgPointObject::distanceToSubpath(const QPointF& p0, const QPointF& p1, const QPointF& p)
{
    QVector2D v(p1 - p0);
    QVector2D w(p - p0);

    qreal dp1 = QVector2D::dotProduct(w,v);
    qreal dp2 = QVector2D::dotProduct(v,v);

    if (dp1 <= 0)
        return w.lengthSquared();
    if (dp2 <= dp1)
        return QVector2D(p - p1).lengthSquared();

    qreal b = dp1 / dp2;
    QPointF pb = p0 + (b*v).toPointF();
    return QVector2D(p - pb).lengthSquared();
}

int SCgPointObject::indexForPoint(const PointFVector& vector, const QPointF& point, bool closed)
{
    ////////////////////////////////////////////
    // get sector with minimal distance to point
    qreal minDist = -1.f;
    int pointIndex = -1;

    int i = 1;

    for (; i < vector.size(); i++)
    {
        qreal curDist = distanceToSubpath(vector.at(i-1), vector.at(i), point);

        if(minDist < 0 || minDist > curDist)
        {
            minDist = curDist;
            pointIndex = i;
        }
    }

    if (closed)
    {
        qreal curDist = distanceToSubpath(vector.at(i-1), vector.at(0), point);

        if(minDist < 0 || minDist > curDist)
        {
            minDist = curDist;
            pointIndex = i;
        }
    }

    return pointIndex;
}

QPointF SCgPointObject::pointAt(int index) const
{
    Q_ASSERT(index > -1 && index < mPoints.size());
    return mPoints.at(index);
}

bool SCgPointObject::isAcceptable(SCgObject *obj, SCgPointObject::IncidentRole role) const
{
    Q_ASSERT_X(obj != 0,
               "bool SCgPointObject::isAcceptable(SCgObject *obj, IncidentRole role) const",
               "obj is null");
    Q_ASSERT_X(role >= 0 && role < SCgPointObject::IncidentRolesCount,
               "bool SCgPointObject::isAcceptable(SCgObject *obj, SCgPointObject::IncidentRole role) const",
               "unknown incident role");
    return false;
}

void SCgPointObject::changeIncidentObject(SCgObject *obj, const QPointF &point, SCgPointObject::IncidentRole role)
{
    Q_ASSERT_X(obj != 0,
               "void SCgPointObject::changeIncidentObject(SCgObject *obj, const QPointF &point, SCgPointObject::IncidentRole role)",
               "obj is null");
    Q_ASSERT_X(role >= 0 && role < SCgPointObject::IncidentRolesCount,
               "bool SCgPointObject::isAcceptable(SCgObject *obj, SCgPointObject::IncidentRole role) const",
               "unknown incident role");
}

SCgObject* SCgPointObject::objectWithRole(SCgPointObject::IncidentRole role) const
{
    Q_ASSERT_X(role >= 0 && role < SCgPointObject::IncidentRolesCount,
               "SCgObject* SCgPointObject::objectWithRole(SCgPointObject::IncidentRole role) const",
               "unknown incident role");
    return 0;
}

qreal SCgPointObject::dotAtRole(SCgPointObject::IncidentRole role) const
{
    Q_ASSERT_X(role >= 0 && role < SCgPointObject::IncidentRolesCount,
               "qreal SCgPointObject::dotAtRole(SCgPointObject::IncidentRole role) const",
               "unknown incident role");
    return 0;
}
