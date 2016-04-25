/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgpointgraphicsitem.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgbus.h"
#include <QGraphicsScene>

#define POINT_ITEM_COLOR_SELECTED QColor(255, 128, 64)
#define POINT_ITEM_COLOR_NORMAL QColor(170, 170, 170)
#define POINT_ITEM_COLOR_HOVERED QColor(128, 255, 64)

SCgPointGraphicsItem::SCgPointGraphicsItem(SCgPointObject* parent, int pointIndex) :
    QGraphicsItem(parent),
    mParent(parent),
    mPointIndex(pointIndex)
{
    setPos(parent->pointAt(mPointIndex));
    mSize = QSizeF(10, 10);
    setFlags(QGraphicsItem::ItemIsSelectable
            | QGraphicsItem::ItemSendsGeometryChanges
            | QGraphicsItem::ItemIsMovable
            | QGraphicsItem::ItemIsFocusable);

    mColor = QColor(170, 170, 170);
    setAcceptHoverEvents(true);

    mShape.addEllipse(boundingRect());
}

SCgPointGraphicsItem::~SCgPointGraphicsItem()
{

}

QRectF SCgPointGraphicsItem::boundingRect() const
{
    return QRectF(-mSize.width() / 2.f, -mSize.height() / 2.f, mSize.width(), mSize.height());
}

QPainterPath SCgPointGraphicsItem::shape() const
{
    return mShape;
}

void SCgPointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setBrush(QBrush(mColor));
    painter->drawPath(mShape);
}

QVariant SCgPointGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // item selection changed
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (isSelected())
            mColor = POINT_ITEM_COLOR_SELECTED;
        else
            mColor = isUnderMouse() ? POINT_ITEM_COLOR_HOVERED : POINT_ITEM_COLOR_NORMAL;
    }

    if(change == QGraphicsItem::ItemPositionHasChanged && isSelected())
        mParent->changePointPosition(mPointIndex, pos());

    return QGraphicsItem::itemChange(change, value);
}

void SCgPointGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mColor = QColor(128, 255, 64);
    QGraphicsItem::hoverEnterEvent(event);
}

void SCgPointGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mColor = isSelected() ? POINT_ITEM_COLOR_SELECTED : POINT_ITEM_COLOR_NORMAL;
    QGraphicsItem::hoverLeaveEvent(event);
}


SCgIncidentPointGraphicsItem::SCgIncidentPointGraphicsItem(SCgPointObject* parent, int pointIndex):
    SCgPointGraphicsItem(parent, pointIndex)
{

}

SCgIncidentPointGraphicsItem::~SCgIncidentPointGraphicsItem()
{

}

SCgObject* SCgIncidentPointGraphicsItem::objectAtPoint() const
{
    QGraphicsScene* _scene = scene();
    Q_ASSERT(_scene);

    QList<QGraphicsItem*> itemList = _scene->items(scenePos(), Qt::IntersectsItemShape, Qt::DescendingOrder);

    foreach(QGraphicsItem* it, itemList)
        if (it != this && it != mParent && SCgObject::isSCgObjectType(it->type()))
            return static_cast<SCgObject*>(it);

    return 0;
}

QVariant SCgIncidentPointGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
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

    return SCgPointGraphicsItem::itemChange(change, value);
}
