/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

// change to item that has biggest Type value
#include "scnfieldglobalidtf.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include <QKeyEvent>

SCnFieldItem::SCnFieldItem(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    mState(StateNormal),
    mEditorScene(0)
{
    setFlags(QGraphicsItem::ItemIsSelectable
                | QGraphicsItem::ItemIsFocusable
                | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

}

SCnFieldItem::~SCnFieldItem()
{

}

bool SCnFieldItem::isSCnFieldType(int type)
{
    return (type >= Type) && (type <= SCnFieldGlobalIdtf::Type);
}

void SCnFieldItem::setValue(const QString &value)
{
    mValue = value;
    changed(this, ValueChanged);
}

void SCnFieldItem::updateOnChilds()
{
    qreal offset = childsOffset();
    QGraphicsItem *child = 0;
    QList<QGraphicsItem*> _childItems = childItems();

    foreach(child, _childItems)
    {
        if (!isSCnFieldType(child->type())) return; // skip non scn-fields
        SCnFieldItem *item = static_cast<SCnFieldItem*>(child);

        item->setPos(30, offset);
        offset += 10 + item->boundingRect().height();
    }

}

QRectF SCnFieldItem::boundingRect() const
{
    return QRectF(0, 0, 100, 30);
}

void SCnFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor brushColor = QColor(240, 240, 240, 220);

    switch (mState)
    {
    case StateHighlight:
        brushColor = QColor(186, 217, 156, 180);
        break;

    case StateEdit:
        brushColor = QColor(144, 173, 146, 180);
        break;

    case StateSelected:
        brushColor = QColor(157, 201, 94, 180);
        break;

    default:
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

    if (change == ItemChildAddedChange || change == ItemChildRemovedChange)
    {
        updateOnChilds();
    }

    return QGraphicsItem::itemChange(change, value);
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

void SCnFieldItem::startEdit()
{
    mState = StateEdit;
    update();
}

void SCnFieldItem::applyEdit()
{

}

void SCnFieldItem::cancelEdit()
{

}

void SCnFieldItem::changed(SCnFieldItem *field, SCnFieldItem::ChangeType changeType)
{
    if (mEditorScene != 0)
        mEditorScene->itemChanged(field, changeType);
}
