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

#include "scgcontour.h"
#include "scgalphabet.h"

#include "scgpointgraphicsitem.h"
#include "scgpair.h"
#include "scgcontour.h"

#include <QColor>
#include <QGraphicsScene>
#include <QVector2D>

#define CONTOUR_CORNER_RADIUS 20.f

SCgContour::SCgContour() :
        mColorBack(QColor(250, 250, 250, 224))
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    //setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    setToolTip(QObject::tr("sc.g-contour"));
    mDefaultZValue = 7;
    setZValue(mDefaultZValue);
}

SCgContour::~SCgContour()
{

}

QPainterPath SCgContour::shape() const
{
    return mShape;
}

QRectF SCgContour::boundingRect() const
{
    return mShape.boundingRect().adjusted(-5.f, -5.f, 5.f, 5.f);
}

bool SCgContour::contains(const QPointF &point) const
{
    SCgPointGraphicsItem *pointItem;
    foreach (pointItem, mPointItems)
    {
        if (pointItem->contains(point))
            return true;
    }

    return QGraphicsItem::contains(point);
}

void SCgContour::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCgAlphabet::paintContour(painter, this);

    SCgObject::paint(painter, option, widget);
}

void SCgContour::setColorBack(const QColor &color)
{
    mColorBack = color;
}

QColor SCgContour::colorBack() const
{
    return mColorBack;
}

void SCgContour::setPoints(const PointFVector &points)
{
    if (points.size() < 3)
        return;

    SCgPointObject::setPoints(points);
}

void SCgContour::positionChanged()
{
    updateShape();
}

void SCgContour::updateShape()
{
    prepareGeometryChange();

    mShape = QPainterPath();

    PointFVector points;
    quint32 pointsSize = mPoints.size();
    for (quint32 i = 0; i < pointsSize; i++)
    {
        QPointF p2 = mPoints[(i + 1) % pointsSize];
        QPointF p1 = mPoints[i];
        QVector2D dir(p2 - p1);
        dir.normalize();

        QPointF dv = dir.toPointF() * CONTOUR_CORNER_RADIUS;
        points.push_back(p1);
        points.push_back(p1 + dv);
        points.push_back(p2 - dv);
    }

    // draw path
    quint32 psz3 = pointsSize * 3;
    for (quint32 i = 0; i < pointsSize; i++)
    {
        quint32 idx = i * 3;

        if (i == 0)
            mShape.moveTo(points[idx + 1]);
        mShape.lineTo(points[idx + 2]);
        mShape.quadTo(points[(idx + 3) % psz3], points[(idx + 4) % psz3]);
    }
    mShape.closeSubpath();

    mShapeNormal = mShape;
    QPainterPathStroker path_stroker;
    //path_stroker.setJoinStyle(Qt::MiterJoin);
    path_stroker.setWidth(SCgAlphabet::lineWidthForShape() + 2);
    mShape = path_stroker.createStroke(mShape);

    mLineShape = mShape;

    mShape = mShapeNormal.united(mShape);

    updateConnected();

    update();
}

void SCgContour::updateConnected()
{
    SCgPointObject::updateConnected();
    // update child items
    foreach(QGraphicsItem* grItem, childItems())
    {
        if (SCgObject::isSCgObjectType(grItem->type()))
        {
            SCgObject *scgObject = static_cast<SCgObject*>(grItem);
            if(!scgObject->isDead())
                scgObject->updateConnected();
        }
    }
}

void SCgContour::objectDelete(SCgObject *object)
{

}

void SCgContour::del(QList<SCgObject*> &delList)
{
    foreach(QGraphicsItem* grItem, childItems())
    {
        if (SCgObject::isSCgObjectType(grItem->type()))
        {
            SCgObject *scgObject = static_cast<SCgObject*>(grItem);
            if(!scgObject->isDead())
                scgObject->del(delList);
        }
    }
    SCgObject::del(delList);
}

QPointF SCgContour::cross(const QPointF &from, float dot) const
{
    QRectF bound = QPolygonF(mPoints).boundingRect();
    QPointF p(bound.center());

    QPointF p1 = mPoints.last();
    QPointF p2, intersectPoint, result;
    QLineF line, pair(mapFromScene(from), p);
    // Ensure, that pair definitely have intersections with contour.
    pair.setLength(pair.length() + bound.width() + bound.height());
    qreal minLength = -1;

    //Find intersection point with minimal distance from @p from to contour
    for (int i = 0; i < mPoints.size(); i++)
    {
        p2 = mPoints[i];
        line.setPoints(p1,p2);
        QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            pair.setP2(intersectPoint);
            if(minLength == -1 || pair.length() < minLength)
            {
                minLength = pair.length();
                result = intersectPoint;
            }
        }

        p1 = p2;
    }

    return mapToScene(result);
}

float SCgContour::dotPos(const QPointF &point) const
{
    // we doesn't need dot position for contour
    return 0.f;
}

SCgPointGraphicsItem* SCgContour::createPointItem(int pointIndex)
{
    return new SCgPointGraphicsItem(this, pointIndex);
}

void SCgContour::changePointPosition(int pointIndex, const QPointF& newPos)
{
    SCgPointObject::changePointPosition(pointIndex, newPos);

    positionChanged();
}

