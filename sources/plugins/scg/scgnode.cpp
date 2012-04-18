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

#include "scgnode.h"

#include "scgcontentfactory.h"
#include "scgcontentviewer.h"
#include "scgbus.h"
#include "scgview.h"

#include <QPainter>
#include <QVector2D>
#include <QGraphicsScene>
#include <QGraphicsView>

SCgNode::SCgNode(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgObject(parent, scene),
    SCgContent(),
    mStructType(SCgAlphabet::StructUnknown),
    mIsContentVisible(false),
    mContentViewer(0),
    mBus(0)
{
    mSize = QSizeF(19.f, 19.f);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setToolTip(QObject::tr("sc.g-node"));
    setZValue(2);
}

SCgNode::~SCgNode()
{
    //Q_ASSERT(!mBus);    // must be deleted before
    if (mContentViewer)
    {
        delete mContentViewer;
        mContentViewer = 0;
    }

    if (mBus)
    {
    	mBus->setOwner(0);
    	mBus = 0;
    }
}

void SCgNode::setTypeAlias(const QString &typeAlias)
{
    SCgObject::setTypeAlias(typeAlias);
    updateType();
}

void SCgNode::updateType()
{    
    /* updating information based on type alias */
    QStringList sl = mTypeAlias.split("/");

    Q_ASSERT(sl.size() > 1);

    mConstType = SCgAlphabet::getInstance().aliasToConstCode(sl[1]);
    mStructType = SCgAlphabet::getInstance().aliasToStructCode(sl[2]);
}

QRectF SCgNode::boundingRect() const
{
    QRectF res;

    if (!mIsContentVisible)
    {
        res = QRectF(-mSize.width() / 2.f, -mSize.height() / 2.f, mSize.width(), mSize.height());
    }else
    {
        Q_ASSERT(mContentViewer);

        QSizeF size = mContentViewer->size();
        res = QRectF(0, 0, size.width(), size.height());
        res.moveCenter(QPointF(0.f, 0.f));
        res.adjust(-5, -5, 5, 5);
    }

    return res;
}

QPainterPath SCgNode::shape() const
{
    QPainterPath path;
    QRectF boundRect = boundingRect();

    if (mIsContentVisible)
    {
        path.addRect(boundRect);
    }else
    {
        QMatrix matrix;
        switch (mConstType)
        {
        case SCgAlphabet::Const:
        case SCgAlphabet::ConstUnknown:
            path.addEllipse(boundRect);
            break;

        case SCgAlphabet::Var:
            path.addRect(boundRect);
            break;

        default:
            break;
        }
    }

    return path;
}

QVariant SCgNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (mBus && !mBus->isDead() && change == QGraphicsItem::ItemParentHasChanged)
    {
        mBus->setParentItem(parentItem());
        updateConnected();
    }

    return SCgObject::itemChange(change, value);
}

void SCgNode::updatePosition()
{
}

void SCgNode::objectDelete(SCgObject *object)
{
    if (mBus)   mBus->setOwner(0);
}

void SCgNode::del(QList<SCgObject*> &delList)
{
    if(mIsContentVisible)
        mContentViewer->hide();

    if(mBus)
    	mBus->del(delList);

    SCgObject::del(delList);
}

void SCgNode::undel(SCgScene* scene)
{
    if(mBus)
    	mBus->undel(scene);

    SCgObject::undel(scene);
    if(mIsContentVisible)
        mContentViewer->show();
}

QPointF SCgNode::cross(const QPointF &from, float dot) const
{
    QPointF p(0.f, 0.f);

    if (!mIsContentVisible)
    {
        QVector2D vec(from - scenePos());
        p = vec.normalized().toPointF() * (mSize.width() / 2.f + 5.f);
    }else
    {

        // count intersection with content border
        QPolygonF polygon(boundingRect());
        QPointF p1 = polygon.last();
        QPointF p2, intersectPoint;
        QLineF line, pair(p, mapFromScene(from));
        bool haveItersect = false;

        for (int i = 0; i < polygon.size(); i++)
        {
            p2 = polygon.at(i);
            line = QLineF(p1, p2);
            QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
            {
                haveItersect = true;
                break;
            }

            p1 = p2;
        }
        p = haveItersect ? intersectPoint : p;
    }

    return mapToScene(p);
}

float SCgNode::dotPos(const QPointF &point) const
{
    return 0.f;
}

void SCgNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* need to rebuild that code to more flexible.
       Just for example make drawers class for different types.
     */

    QRectF boundRect = boundingRect();

    if (!mIsContentVisible)
    {
        painter->save();
        SCgAlphabet::getInstance().paintNode(painter, mColor, boundRect, mConstType, mStructType);
        painter->restore();

        if (isContentData())
        {
            QBrush brush(QColor(128, 0, 255), Qt::SolidPattern);
            painter->setBrush(brush);

            painter->drawRect(boundRect.right() - 5, boundRect.bottom() - 5, 5, 5);
        }
    }else
    {
        QPen pen(mColor);
        pen.setWidthF(3.f);
        painter->setPen(pen);
        painter->drawRect(boundRect.adjusted(2, 2, -2, -2));
    }

    SCgObject::paint(painter, option, widget);

    // draw content corner
    if (mIsContentVisible)
    {
        QRectF rc = boundRect.adjusted(2, 2, -2, -2);
        QPolygonF polygon;
        polygon.append(rc.topLeft());
        polygon.append(QPointF(rc.left() + 10, rc.top()));
        polygon.append(QPointF(rc.left(), rc.top() + 10));

        QPainterPath path;
        path.addPolygon(polygon);
        path.closeSubpath();

        painter->fillPath(path, QBrush(mColor));

    }
}

void SCgNode::updateConnected()
{
    SCgObject::updateConnected();
    if (mBus && !mBus->isDead())
        mBus->updatePosition();
}

void SCgNode::setContent(const QString& mimeType, const QVariant& data,
                         const QString& fileName, SCgContent::ContType cType)
{
    SCgContent::setContent(mimeType, data, fileName, cType);
    updateContentViewer();
    emit(contentChanged());
}

void SCgNode::showContent()
{
    Q_ASSERT(!mIsContentVisible && mContentViewer);

    prepareGeometryChange();

    mIsContentVisible = true;
    updateConnected();

    mContentViewer->show();
    update();
}

void SCgNode::hideContent()
{
    Q_ASSERT(mIsContentVisible && mContentViewer);

    prepareGeometryChange();

    mIsContentVisible = false;
    updateConnected();

    mContentViewer->hide();
    update();
}

bool SCgNode::isContentVisible() const
{
    return mIsContentVisible;
}


void SCgNode::updateContentViewer()
{
    bool isCntVis = mIsContentVisible;

    if(isCntVis)
        hideContent();

    if (mContentViewer != 0)
    {
        delete mContentViewer;
        mContentViewer = 0;
    }

    if (!contentType() == SCgContent::Empty)
    {
        // creating new viewer
        if (!mContentViewer) mContentViewer = SCgContentFactory::createViewer(contentFormat());
        Q_ASSERT(mContentViewer);

        mContentViewer->setData(contentData());
        mContentViewer->setParentItem(this);

        if (isCntVis)
            showContent();
    }
    update();
}

bool SCgNode::isContentData() const
{
    return mContentViewer != 0;
}

SCgBus* SCgNode::bus() const
{
    return mBus;
}

void SCgNode::setBus(SCgBus *bus)
{
    mBus = bus;
}
