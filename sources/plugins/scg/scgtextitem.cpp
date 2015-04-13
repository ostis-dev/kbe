/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgtextitem.h"
#include "scgconfig.h"
#include <QGraphicsSceneEvent>

SCgTextItem::SCgTextItem(const QString &str, QGraphicsItem *parent)
    : QGraphicsTextItem(str, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsFocusable);

    setAcceptHoverEvents(true);
}

SCgTextItem::SCgTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);
}

SCgTextItem::~SCgTextItem() {}

void SCgTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);
}

QRectF SCgTextItem::boundingRect() const
{
    return QGraphicsTextItem::boundingRect();
}

QVariant SCgTextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (isSelected())
        {
            setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_selected));
        }
        else
        {
            setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_normal));
        }
    }

    return QGraphicsTextItem::itemChange(change, value);
}

void SCgTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
        setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_highlight));

    QGraphicsTextItem::hoverEnterEvent(event);
}

void SCgTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
        setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_normal));
    else
        setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_selected));

    QGraphicsTextItem::hoverLeaveEvent(event);
}

void SCgTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (parentItem()->isSelected())
        setFlag(QGraphicsItem::ItemIsMovable);
    QGraphicsTextItem::mousePressEvent(event);
}

void SCgTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseMoveEvent(event);
}

void SCgTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    QGraphicsTextItem::mouseReleaseEvent(event);
}

void SCgTextItem::setTextPos(const QPointF &pos)
{
    setPos(pos);
}

QPointF SCgTextItem::textPos() const
{
    return QGraphicsTextItem::pos();
}

void SCgTextItem::setPos(const QPointF &pos)
{
    QGraphicsTextItem::setPos(pos);
}

void SCgTextItem::setPos(qreal x, qreal y)
{
    QGraphicsTextItem::setPos(x,y);
}

QPointF SCgTextItem::pos() const
{
    return QGraphicsTextItem::pos();
}

void SCgTextItem::setPlainText(const QString &text)
{
    QGraphicsTextItem::setPlainText(text);
}
