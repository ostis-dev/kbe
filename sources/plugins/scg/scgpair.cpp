/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgpair.h"
#include "scgbus.h"
#include "scgtextitem.h"
#include "scgpointgraphicsitem.h"

#include <QPainter>
#include <QVector2D>

SCgPair::SCgPair() :
    mBeginObject(0),
    mBeginDot(0.f),
    mEndObject(0),
    mEndDot(0.f),
    mEndArrow(false),
    mPosType(SCgAlphabet::PosUnknown),
    mPermType(SCgAlphabet::PermUnknown),
    mIsMembership(false),
    mIsOrient(false),
    mIsParentChangeInProcess(false)
{
    mPoints.push_back(QPointF());
    mPoints.push_back(QPointF());

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setToolTip(QObject::tr("sc.g-pair"));
    mDefaultZValue = 1;
    setZValue(mDefaultZValue);
}

SCgPair::~SCgPair()
{
    if (mBeginObject)
        mBeginObject->removeConnectedObject(this);
    if (mEndObject)
        mEndObject->removeConnectedObject(this);
}

QRectF SCgPair::boundingRect() const
{
    return mShape.boundingRect().adjusted(-11, -11, 11, 11);
}

QPainterPath SCgPair::shape() const
{
    return mShape;
}

void SCgPair::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // don't draw pair if end and begin object collides
    /*if (mBeginObject && mEndObject && mBeginObject->collidesWithItem(mEndObject))
        return;*/

    SCgAlphabet::paintPair(painter, this);
    // draw line
    /*QPen pen(mColor);
    pen.setWidth(4);

    painter->setPen(pen);
    painter->drawPath(mShape);*/

    SCgObject::paint(painter, option, widget);
}

void SCgPair::updateShape()
{
    prepareGeometryChange();

    // Rebuilding shape
    mShapeNormal = QPainterPath();

    mShapeNormal.moveTo(mPoints.at(0));
    for (int i = 1; i < mPoints.size(); i++)
        mShapeNormal.lineTo(mPoints.at(i));

    QPainterPathStroker path_stroker;
    path_stroker.setJoinStyle(Qt::MiterJoin);
    path_stroker.setWidth(SCgAlphabet::lineWidthForShape());
    mShape = path_stroker.createStroke(mShapeNormal);

    mLineShape = mShape;

    // updating pair
    update();

    // updating connected objects
    updateConnected();

    // update text position
    if (mTextItem)
    {
        Q_ASSERT(mPoints.size() > 1);
        QPointF text_pos = (mPoints[0] + mPoints[1]) / 2.f;
        mTextItem->setTextPos(text_pos);
    }
}

void SCgPair::positionChanged()
{
    // this notifies the scene of the imminent change, so that it can update its item geometry index.
    if (!mBeginObject || !mEndObject)   return;

    mPoints.front() = mapFromScene(mBeginObject->scenePos());
    mPoints.last() = mapFromScene(mEndObject->scenePos());

    int begType = mBeginObject->type();

    // if pair goes from line object (pair, bus), then start update from front point
    if (begType == SCgPair::Type || begType == SCgBus::Type)
    {
        mPoints.front() = mapFromScene(mBeginObject->cross(mapToScene(mPoints[1]), mBeginDot));
        mPoints.last() = mapFromScene(mEndObject->cross(mapToScene(mPoints[mPoints.size() - 2]), mEndDot));
    }else
        {
            mPoints.last() = mapFromScene(mEndObject->cross(mapToScene(mPoints[mPoints.size() - 2]), mEndDot));
            mPoints.front() = mapFromScene(mBeginObject->cross(mapToScene(mPoints[1]), mBeginDot));
        }

    // change parent item for the pair if parent's item for begin or end objects was changed
    if (mBeginObject->isSelected() && mBeginObject->parentItem() != parentItem())
        setParentItem(mBeginObject->parentItem());
    else if (mEndObject->isSelected() && mEndObject->parentItem() != parentItem())
        setParentItem(mEndObject->parentItem());

    // update shape with new points.
    updateShape();
}

void SCgPair::objectDelete(SCgObject *object)
{
    if (mBeginObject == object)
        mBeginObject = 0;

    if (mEndObject == object)
        mEndObject = 0;
}

QVariant SCgPair::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemParentChange)
        mIsParentChangeInProcess = true;

    if (change == QGraphicsItem::ItemParentHasChanged)
        mIsParentChangeInProcess = false;

    if (change == QGraphicsItem::ItemPositionHasChanged && !mIsParentChangeInProcess)
        positionChanged();

    return SCgObject::itemChange(change, value);
}

QPointF SCgPair::cross(const QPointF &from, float dot) const
{
    Q_UNUSED(from);

    // get sector num
    int s = (int)dot;
    // get relative pos in sector
    float ds = dot - s;

    Q_ASSERT(mPoints.size() > 1);

    // calculating position
    if (s >= mPoints.size() - 1)
        s = mPoints.size() - 2;
    if (s < 0)
        s = 0;

    return mapToScene(mPoints[s] + (mPoints[s+1] - mPoints[s]) * ds);
}

float SCgPair::dotPos(const QPointF &point) const
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


void SCgPair::setPoints(const PointFVector &points)
{
    if(points.size() < 2)
        return;

    if(mBeginObject)
    {
        qreal dPos = mBeginObject->dotPos(points.at(0));
        if(dPos != 0)
            mBeginDot = dPos;
    }
    if(mEndObject)
    {
        qreal dPos = mEndObject->dotPos(points.at(points.size()-1));
        if(dPos != 0)
            mEndDot = dPos;
    }

    SCgPointObject::setPoints(points);
}

void SCgPair::changePointPosition(int pointIndex, const QPointF& newPos)
{
    SCgPointObject::changePointPosition(pointIndex, newPos);

    if(pointIndex == 0)
    {
        mPoints.last() = mapFromScene(mEndObject->cross(mapToScene(mPoints[mPoints.size() - 2]), mEndDot));
        updateShape();
    }
    else if(pointIndex == mPoints.size() - 1)
    {
        mPoints.front() = mapFromScene(mBeginObject->cross(mapToScene(mPoints[1]), mBeginDot));
        updateShape();
    }
    else
        positionChanged();
}

SCgPointGraphicsItem* SCgPair::createPointItem(int pointIndex)
{
    if(pointIndex == 0 || pointIndex == mPoints.size()-1)
        return new SCgIncidentPointGraphicsItem(this, pointIndex);

    return new SCgPointGraphicsItem(this, pointIndex);
}


void SCgPair::setBeginObject(SCgObject *object)
{
    if (mBeginObject)
        mBeginObject->removeConnectedObject(this);

    mBeginObject = object;

    if (mBeginObject)
        mBeginObject->addConnectedObject(this);

    positionChanged();
}

SCgObject* SCgPair::beginObject() const
{
    return mBeginObject;
}

void SCgPair::setEndObject(SCgObject *object)
{
    if (mEndObject)
        mEndObject->removeConnectedObject(this);

    mEndObject = object;

    if (mEndObject)
        mEndObject->addConnectedObject(this);

    positionChanged();
}

SCgObject* SCgPair::endObject() const
{
    return mEndObject;
}

void SCgPair::setBeginDot(float pos)
{
    mBeginDot = pos;
    positionChanged();
}

float SCgPair::beginDot() const
{
    return mBeginDot;
}

void SCgPair::setEndDot(float pos)
{
    mEndDot = pos;
    positionChanged();
}

float SCgPair::endDot() const
{
    return mEndDot;
}

void SCgPair::swap()
{
    SCgObject *bObj = beginObject();
    SCgObject *eObj = endObject();

    qreal bDot = beginDot();
    qreal eDot = endDot();

    setBeginDot(eDot);
    setEndDot(bDot);

    setBeginObject(0);
    setEndObject(0);

    setBeginObject(eObj);
    setEndObject(bObj);

    // swap points
    PointFVector pts = mPoints;
    mPoints.clear();
    QPointF p;
    foreach(p, pts)
        mPoints.push_front(p);

    if (!mPointItems.empty())
    {
        destroyPointObjects();
        createPointObjects();
    }

    positionChanged();
}

bool SCgPair::isAcceptable(SCgObject* obj, SCgPointObject::IncidentRole role) const
{
    if(!obj)
        return false;
    if(obj == parentItem())
        return false;
    if(role == IncidentBegin && obj == mEndObject)
        return false;
    if(role == IncidentEnd && obj == mBeginObject)
        return false;
    if(mConnectedObjects.contains(obj))
        return false;

    return true;
}

void SCgPair::changeIncidentObject(SCgObject* obj, const QPointF& point, SCgPointObject::IncidentRole role)
{
    if (isAcceptable(obj, role))
    {
        if (role == IncidentBegin)
        {
            setBeginDot(obj->dotPos(mapToScene(point)));
            setBeginObject(obj);
        }
        else if(role == IncidentEnd)
        {
            setEndDot(obj->dotPos(mapToScene(point)));
            setEndObject(obj);
        }
    }
}

SCgObject* SCgPair::objectWithRole(SCgPointObject::IncidentRole role) const
{
    if(role == IncidentBegin)
        return mBeginObject;
    if(role == IncidentEnd)
        return mEndObject;
    return 0;
}

void SCgPair::setTypeAlias(const QString &type_alias)
{
    SCgObject::setTypeAlias(type_alias);
    updateType();
}

void SCgPair::updateType()
{
    mConstType = SCgAlphabet::ConstUnknown;
    mPosType = SCgAlphabet::PosUnknown;
    mPermType = SCgAlphabet::PermUnknown;
    mIsOrient = mIsMembership = false;

    /* updating information based on type alias */
    QStringList sl = mTypeAlias.split("/");

    mConstType = SCgAlphabet::getInstance().aliasToConstCode(sl[1]);
    mPosType = SCgAlphabet::getInstance().aliasToPositiveCode(sl[2]);
    mPermType = SCgAlphabet::getInstance().aliasToPermanencyCode(sl[3]);
    mIsOrient = (sl[4] == "orient");
    if (sl.size() == 6)
        mIsMembership = (sl[5] == "membership");
}
