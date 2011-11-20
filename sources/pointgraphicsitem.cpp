/*
 * pointgraphicsitem.cpp
 *
 *  Created on: 24.01.2011
 *      Author: ZooNer
 */

#include "pointgraphicsitem.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgbus.h"
#include <QGraphicsScene>

PointGraphicsItem::PointGraphicsItem(SCgPointObject* parent, int pointIndex):QGraphicsItem(parent),mParent(parent),mPointIndex(pointIndex)
{
    setPos(parent->pointAt(mPointIndex));
    mSize = QSizeF(7,7);
    setFlags(QGraphicsItem::ItemIsSelectable
            | QGraphicsItem::ItemSendsGeometryChanges
            | QGraphicsItem::ItemIsMovable);
    mColor = QColor(170, 170, 170);
    /*
    switch (parent->type())
    {
    case SCgPair
    }*/
}

PointGraphicsItem::~PointGraphicsItem()
{

}

QRectF PointGraphicsItem::boundingRect() const
{
    return QRectF(-mSize.width() / 2.f, -mSize.height() / 2.f, mSize.width(), mSize.height());
}

QPainterPath PointGraphicsItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect().adjusted(-4,-4, 4, 4));
    return path;
}

void PointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(mColor));
    painter->drawEllipse(boundingRect());
}

QVariant PointGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // item selection changed
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (isSelected())
        {
            mColor = QColor(255, 128, 64);
            //setCursor(QCursor(Qt::SizeAllCursor));
        }
        else
        {
            mColor = QColor(170, 170, 170);
            //setCursor(QCursor(Qt::ArrowCursor));
        }
    }

    if(change == QGraphicsItem::ItemPositionHasChanged && isSelected())
        mParent->changePointPosition(mPointIndex, pos());

    return QGraphicsItem::itemChange(change, value);
}

IncidencePointGraphicsItem::IncidencePointGraphicsItem(SCgPointObject* parent, int pointIndex):
        PointGraphicsItem(parent, pointIndex)
{

}

IncidencePointGraphicsItem::~IncidencePointGraphicsItem()
{

}

SCgObject* IncidencePointGraphicsItem::objectAtPoint() const
{
    QGraphicsScene* s = scene();
    Q_ASSERT(s);

    QList<QGraphicsItem*> itemList = s->items(scenePos(), Qt::IntersectsItemShape, Qt::DescendingOrder);

    foreach(QGraphicsItem* it, itemList)
        if (it != this && it != mParent && SCgObject::isSCgObjectType(it->type()))
            return static_cast<SCgObject*>(it);

    return 0;
}

QVariant IncidencePointGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionHasChanged)
    {
        if(isUnderMouse())
        {
            if(mParent->isAcceptable(objectAtPoint(), role()))
                mColor = Qt::green;
            else
                mColor = Qt::red;
        }
        else if(isSelected())
            mColor = QColor(255, 128, 64);
        else
            mColor = QColor(170, 170, 170);
    }

    return PointGraphicsItem::itemChange(change, value);
}
