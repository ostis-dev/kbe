/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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

qreal SCgContour::CornerRadius = 20.f;
qreal SCgContour::BorderDistance = 20.f;

SCgContour::SCgContour() :
        mColorBack(QColor(250, 250, 250, 164))
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

void SCgContour::minimize()
{
    setPoints(minimizedPoints());
}

SCgPointObject::PointFVector SCgContour::minimizedPoints() const
{
    PointFVector newPoints;

    // Collect items which is a scgObject
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

        for (++it; it != scgObjects.end(); ++it)
        {
            SCgObject *obj = *it;
            QRectF objRect = obj->boundingRect();

            QPointF topLeft = obj->mapToScene(objRect.topLeft());
            QPointF bottomRight = obj->mapToScene(objRect.bottomRight());

            if (topLeft.x() < minX)
                minX = topLeft.x();
            if (topLeft.y() < minY)
                minY = topLeft.y();
            if (bottomRight.x() > maxX)
                maxX = bottomRight.x();
            if (bottomRight.y() > maxY)
                maxY = bottomRight.y();
        }

        // Increase distance from borders:
        minX -= BorderDistance;
        minY -= BorderDistance;
        maxX += BorderDistance;
        maxY += BorderDistance;

        // Remove all points and set only 4 corner points:
        newPoints << QPointF(minX, minY) << QPointF(maxX, minY)
                  << QPointF(maxX, maxY) << QPointF(minX, maxY);
    }

    return newPoints;
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
        qreal cornerRadiusAdjusted = CornerRadius;
        qreal dirLength = dir.length();
        if(dirLength < CornerRadius * 2)
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
    Q_UNUSED(object);
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
    Q_UNUSED(dot);

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
    Q_UNUSED(point);
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

void SCgContour::setTypeAlias(const QString &type_alias)
{
    SCgObject::setTypeAlias(type_alias);
    updateType();
}

void SCgContour::updateType()
{
    mConstType = SCgAlphabet::Const;
    mPermType = SCgAlphabet::Permanent;

    /* updating information based on type alias */
    QStringList sl = mTypeAlias.split("/");

    if (sl.size() > 2) {
        mConstType = SCgAlphabet::getInstance().aliasToConstCode(sl[1]);
        mPermType = SCgAlphabet::getInstance().aliasToPermanencyCode(sl[2]);
    }
}
