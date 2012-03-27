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

#include "scgtextitem.h"
#include "scgconfig.h"

SCgTextItem::SCgTextItem(const QString &str, QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsTextItem(str, parent, scene)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsFocusable);

    setAcceptHoverEvents(true);
}

SCgTextItem::SCgTextItem(QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsTextItem(parent, scene)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
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
