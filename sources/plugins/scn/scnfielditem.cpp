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

#include "scnfielditem.h"
#include "scneditorscene.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include <QKeyEvent>

SCnFieldItem::SCnFieldItem() :
    QGraphicsItem(),
    mSize(100, 30),
    mType(Empty),
    mEditorScene(0),
    mLevel(0),
    mState(StateNormal)
{
    setFlags(QGraphicsItem::ItemIsSelectable
                | QGraphicsItem::ItemIsFocusable
                | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

}

SCnFieldItem::~SCnFieldItem()
{
}

bool SCnFieldItem::isSubitemsPossible() const
{
    switch(mType)
    {
    case GlobalIdtf:
    case Synonym:
    case Subitem:
    case ArcIn:
    case ArcOut:
        return false;

    case RelIn:
    case RelOut:
        return true;
    };
    return false;
}

void SCnFieldItem::setLevel(quint32 level)
{
    mLevel = level;
    changed(this, LevelChanged);
}

quint32 SCnFieldItem::level() const
{
    return mLevel;
}

void SCnFieldItem::setType(FieldType type)
{
    mType = type;
    changed(this, TypeChanged);
}

QRectF SCnFieldItem::boundingRect() const
{


    return QRectF(-mSize.width() / 2.f, -mSize.height() / 2.f,
                  mSize.width(), mSize.height()).adjusted(-5, -5, 5, 5);
}

void SCnFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColor = QColor(240, 240, 240, 180);

    switch (mState)
    {
    case StateHighlight:
        brushColor = QColor(186, 217, 156, 180);
        break;

    case StateEdit:
        brushColor = QColor(143, 160, 118, 250);
        break;

    case StateSelected:
        brushColor = QColor(157, 201, 94, 180);
        break;
    };

    QBrush brush(brushColor);
    QPen pen(brush, 5.f, Qt::DashLine);

    painter->setPen(pen);
    painter->setBrush(brush);

    QRectF rect = boundingRect().adjusted(5, 5, -5, -5);

    painter->drawRoundedRect(rect, 10.f, 10.f);
}

QVariant SCnFieldItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged)
    {
        if (!value.toBool())
            mState = StateNormal;
        else
        {
            if (mState != StateEdit)
                mState = StateSelected;
        }
        update();
    }

    return value;
}

void SCnFieldItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (mState != StateEdit && mState != StateSelected)
        mState = StateHighlight;
    update();
}

void SCnFieldItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (mState == StateHighlight)
        mState = StateNormal;
    update();
}

void SCnFieldItem::startEditAttr()
{

}

void SCnFieldItem::startEditValue()
{

}
