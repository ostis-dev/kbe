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

#include "scgbus.h"

#include "scgalphabet.h"
#include "scgnode.h"
#include "scgtextitem.h"
#include "scgpointgraphicsitem.h"

#include <QPainterPathStroker>
#include <QVector2D>

SCgBus::SCgBus() :
        mWidth(5.f),
        mOwner(0)
{
    mTypeAlias = "bus";

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setToolTip(QObject::tr("sc.g-bus"));
    mDefaultZValue = 0;
}

SCgBus::~SCgBus()
{
    //Q_ASSERT(mOwner);   // must be deleted before
    if (mOwner)
    {
        mOwner->setBus(0);
        mOwner = 0;
    }
}

QRectF SCgBus::boundingRect() const
{
    return mShape.boundingRect().adjusted(-5, -5, 5, 5);
}

QPainterPath SCgBus::shape() const
{
    return mShape;
}

void SCgBus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCgAlphabet::paintBus(painter, this);

    SCgObject::paint(painter, option, widget);
}

QVariant SCgBus::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged && !mParentChanging
            && mOwner && !mOwner->isDead())
        mOwner->setPos(mapToParent(mOwnerPos));

    if (change == QGraphicsItem::ItemParentHasChanged && mOwner && !mOwner->isDead())
        mOwner->setParentItem(parentItem());

    return SCgObject::itemChange(change, value);
}

void SCgBus::positionChanged()
{
    // skip update if there are no points
    if (mPoints.empty())    return;

    if (mOwner)
    {
        mOwnerPos = mapFromScene(mOwner->scenePos());
        mPoints.first() = mapFromScene(mOwner->cross(mapToScene(mPoints.at(1)), 0.f));
    }

    updateShape();
}

void SCgBus::updateShape()
{
    prepareGeometryChange();

    // creating shape
    mShape = QPainterPath();

    mShape.moveTo(mPoints.at(0));
    for (int i = 1; i < mPoints.size(); i++)
        mShape.lineTo(mPoints.at(i));

    QPainterPathStroker path_stroker;
    path_stroker.setJoinStyle(Qt::MiterJoin);
    path_stroker.setWidth(SCgAlphabet::lineWidthForShape());
    mShape = path_stroker.createStroke(mShape);

    mLineShape = mShape;

    // update item
    update();

    // update connected objects
    updateConnected();

    // update text position
    if (mTextItem)
        mTextItem->setPos((mPoints.at(0) + mPoints.at(1)) / 2.f);
}

void SCgBus::objectDelete(SCgObject *object)
{
    if (mOwner) mOwner->setBus(0);
}

void SCgBus::del(QList<SCgObject*> &delList)
{
	SCgObject::del(delList);
	if (mOwner)
		mOwner->setBus(0);
}

void SCgBus::undel(SCgScene *scene)
{
	if (mOwner)
		mOwner->setBus(this);
	SCgObject::undel(scene);
}

QPointF SCgBus::cross(const QPointF &from, float dot) const
{
    // get sector num
    int s = (int)dot;
    // get relative pos in sector
    float ds = dot - s;

    Q_ASSERT(mPoints.size() > 1);

    // calculating position
    if (s >= mPoints.size() - 1)    s = mPoints.size() - 2;
    if (s < 0)  s = 0;

    return mapToScene(mPoints[s] + (mPoints[s+1] - mPoints[s]) * ds);
}

float SCgBus::dotPos(const QPointF &point) const
{
    // get sector with minimal distance to point
    // and calculates relative dot position on it

    qreal minDist = -1.f;
    qreal result = 0.f;
    QPointF np = mapFromScene(point);

    for (int i = 1; i < mPoints.size(); i++)
    {
        QPointF p1 = mPoints[i - 1];
        QPointF p2 = mPoints[i];

        QVector2D v(p2 - p1);
        QVector2D vp(np - p1);

        QVector2D vn = v.normalized();
        //vp.normalize();

        // calculate point on line
        QVector2D p = QVector2D(p1) + vn * QVector2D::dotProduct(vn, vp);
        if(v.length() == 0)
            return result;
        qreal dotPos = QVector2D(p.toPointF() - p1).length() / v.length();

        if (dotPos < 0.f || dotPos > 1.f)
            continue;

        // we doesn't need to get real length, because we need minimum
        // so we get squared length to make that procedure faster
        qreal d = QVector2D(np - p.toPointF()).lengthSquared();

        // compare with minimum distance
        if (minDist < 0.f || minDist > d)
        {
            minDist = d;
            result = (i - 1) + dotPos;
        }
    }

    return result;
}

SCgPointGraphicsItem* SCgBus::createPointItem(int pointIndex)
{
    if(pointIndex == 0)
        return new SCgIncidentPointGraphicsItem(this, pointIndex);

    return new SCgPointGraphicsItem(this, pointIndex);
}

bool SCgBus::isAcceptable(SCgObject* obj, SCgPointObject::IncidentRole role) const
{
    if(obj && obj->type() == SCgNode::Type && role == IncidentBegin)
        return true;
    return false;
}

void SCgBus::changeIncidentObject(SCgObject* obj, const QPointF& point, SCgPointObject::IncidentRole role)
{
    if (isAcceptable(obj, role))
        setOwner(static_cast<SCgNode*>(obj));
}

SCgObject* SCgBus::objectWithRole(SCgPointObject::IncidentRole role) const
{
    if(role == IncidentBegin)
        return mOwner;
    return 0;
}

float SCgBus::getWidth() const
{
    return mWidth;
}

void SCgBus::setOwner(SCgNode *owner)
{

    if (mOwner)
    {
        mPoints.first() = mapFromScene(mOwner->scenePos());
        mOwner->setBus(0);
    }
    mOwner = owner;
    if (mOwner) mOwner->setBus(this);
    positionChanged();
}

SCgNode* SCgBus::owner() const
{
    return mOwner;
}

void SCgBus::changePointPosition(int pointIndex, const QPointF& newPos)
{
    SCgPointObject::changePointPosition(pointIndex, newPos);

    if(!pointIndex)
        updateShape();
        else
            positionChanged();
}
