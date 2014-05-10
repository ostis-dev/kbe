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
#include <QSet>

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

void SCgContour::scalingContur(double factor)
{
    if(factor <= 0 ) {
       return;
    }
    else {
       for (int i = 0; i < mPoints.size(); i++)
       {
           double xreal = mPoints[i].x() * factor;
           double yreal = mPoints[i].y() * factor;
           const QPointF newPos(xreal,yreal);
           SCgPointObject::changePointPosition(i, newPos);
       }
       updateShape();
    }

}

void SCgContour::positionChanged()
{
    updateShape();
}

void SCgContour::minimize()
{
    setPoints(minimizedPoints());
}

SCgPointObject::PointFVector SCgContour::minimizedPoints() const
{
    // Collect items which is a scgObject:
    QSet<SCgObject *> scgObjects;
    foreach(QGraphicsItem* item, childItems())
    {
        if (SCgObject::isSCgObjectType(item->type()))
        {
            SCgObject *scgObject = static_cast<SCgObject*>(item);
            scgObjects.insert(scgObject);
        }
    }

    if (!scgObjects.isEmpty()) {
        // Find min and max points:
        qreal minX, minY, maxX, maxY;

        QSet<SCgObject *>::const_iterator it;
        it = scgObjects.begin();
        SCgObject *firstObj = *it;
        QRectF firstObjRect = firstObj->boundingRect();

        minX = firstObj->mapToScene(firstObjRect.topLeft()).x();
        minY = firstObj->mapToScene(firstObjRect.topLeft()).y();
        maxX = firstObj->mapToScene(firstObjRect.bottomRight()).x();
        maxY = firstObj->mapToScene(firstObjRect.bottomRight()).y();

        for (++it; it != scgObjects.end(); ++it) {
            SCgObject *obj = *it;
            QRectF objRect = obj->boundingRect();

            QPointF topLeft = obj->mapToScene(objRect.topLeft());
            QPointF bottomRight = obj->mapToScene(objRect.bottomRight());

            if (topLeft.x() < minX) {
                minX = topLeft.x();
            }
            if (topLeft.y() < minY) {
                minY = topLeft.y();
            }
            if (bottomRight.x() > maxX) {
                maxX = bottomRight.x();
            }
            if (bottomRight.y() > maxY) {
                maxY = bottomRight.y();
            }
        }

        // Increase distance from borders:
        minX -= borderDistance;
        minY -= borderDistance;
        maxX += borderDistance;
        maxY += borderDistance;

        // Remove all points and set only 4 corner points:
        PointFVector newPoints;
        newPoints << QPointF(minX, minY) << QPointF(maxX, minY)
                  << QPointF(maxX, maxY) << QPointF(minX, maxY);

        return newPoints;
    }
}

void SCgContour::updateShape()
{
    prepareGeometryChange();

    mShape = QPainterPath();

    // Generate control points to be used for path drawing
    PointFVector points;
    quint32 pointsSize = mPoints.size();
    for (quint32 i = 0; i < pointsSize; i++)
    {
        QPointF p2 = mPoints[(i + 1) % pointsSize];
        QPointF p1 = mPoints[i];

        QVector2D dir(p2 - p1);

        // In case two points are placed close to each other
        // we need to adjust corner radius.
        qreal cornerRadiusAdjusted = cornerRadius;
        qreal dirLength = dir.length();
        if(dirLength < cornerRadius * 2)
            cornerRadiusAdjusted = dirLength / 2;

        dir.normalize();
        QPointF dv = dir.toPointF() * cornerRadiusAdjusted;

        points.push_back(p1);
        points.push_back(p1 + dv);
        points.push_back(p2 - dv);
    }

    // Draw path using generated points
    quint32 psz3 = pointsSize * 3;
    for (quint32 i = 0; i < psz3; i += 3)
    {
        if (i == 0)
            mShape.moveTo(points[i + 1]);
        mShape.lineTo(points[i + 2]);
        mShape.quadTo(points[(i + 3) % psz3], points[(i + 4) % psz3]);
    }
    mShape.closeSubpath();

    mShapeNormal = mShape;

    QPainterPathStroker path_stroker;
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

