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

#include "scgobject.h"

#include "scgscene.h"
#include "scgview.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgtextitem.h"

#include "scgpointgraphicsitem.h"
#include "scgconfig.h"

#include <QCursor>
#include <QVector2D>
#include <QGraphicsScene>
#include <QApplication>

SCgObject::SCgObject(QGraphicsItem *parent, QGraphicsScene *scene) :
        QGraphicsItem(parent, scene),
        mConstType(SCgAlphabet::ConstUnknown),
        mIsBoundingBoxVisible(false),
        mTextItem(0),
        mIsDead(false),
        mParentChanging(false)
{
    mColor = scg_cfg_get_value_color(scg_key_element_color_normal);

    setFlags(QGraphicsItem::ItemIsSelectable
    		| QGraphicsItem::ItemIsFocusable
    		| QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

SCgObject::~SCgObject()
{
    SCgObjectList::iterator it;
    SCgObjectList objects = mConnectedObjects;
    for (it = objects.begin(); it != objects.end(); it++)
        (*it)->objectDelete(this);

    if (mTextItem)  delete mTextItem;
}

bool SCgObject::isSCgObjectType(int type)
{
    return (type >= (int)SCgNode::Type && type <= (int)SCgContour::Type);
}

bool SCgObject::isSCgPointObjectType(int type)
{
    return (type > (int)SCgNode::Type && type <= (int)SCgContour::Type);
}

void SCgObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (mIsBoundingBoxVisible)
    {
        QPen pen(QBrush(Qt::red, Qt::SolidPattern), 1.f, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);

        painter->drawRect(boundingRect());
    }

}

QVariant SCgObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // item selection changed
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (isSelected())
        {
            mColor = scg_cfg_get_value_color(scg_key_element_color_selected);//QColor(255, 128, 64);
            //setCursor(QCursor(Qt::SizeAllCursor));
        }
        else
        {
            mColor = scg_cfg_get_value_color(scg_key_element_color_normal);//QColor(0, 0, 0);
            //setCursor(QCursor(Qt::ArrowCursor));
        }
    }

    // move to correct position automaticly
    if (change == QGraphicsItem::ItemParentChange && scene())
    {
        // we need to set this flag to prevent processing ItemPositionHasChanged,
        // because item position at this moment not actual
        mParentChanging = true;
        QGraphicsItem* newParent = value.value<QGraphicsItem*>();
        if(newParent)
            setPos(newParent->mapFromScene(scenePos()));
        else
            setPos(scenePos());
    }

    if (change == QGraphicsItem::ItemParentHasChanged)
    {
        // now item position has valid value
        mParentChanging = false;
        updateConnected();
    }

    // Change stacking order
    if (scene() && change == QGraphicsItem::ItemSelectedHasChanged
                && isSelected() && scene()->selectedItems().size() == 1)
    {
        QGraphicsItem* top = this;
        QList<QGraphicsItem*> lst = scene()->items();
        foreach(QGraphicsItem* it, lst)
        {
            if(it != this &&
               it->type() == type() &&
               it->parentItem() == parentItem())
            {
                it->stackBefore(top);
                top = it;
            }
        }
    }

    // Position changed
    if (scene() && change == QGraphicsItem::ItemPositionHasChanged )
        updateConnected();

    return QGraphicsItem::itemChange(change, value);
}

void SCgObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
        mColor = scg_cfg_get_value_color(scg_key_element_color_highlight);//QColor(64, 128, 255, 255);

    QGraphicsItem::hoverEnterEvent(event);
}

void SCgObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
        mColor = scg_cfg_get_value_color(scg_key_element_color_normal);//QColor(0, 0, 0, 255);
    else
        mColor = scg_cfg_get_value_color(scg_key_element_color_selected);//QColor(255, 128, 64);

    QGraphicsItem::hoverLeaveEvent(event);
}

void SCgObject::setBoundingBoxVisible(bool value)
{
    mIsBoundingBoxVisible = value;
}

bool SCgObject::isBoundingBoxVisible() const
{
    return mIsBoundingBoxVisible;
}

void SCgObject::addConnectedObject(SCgObject *object)
{
    if (mConnectedObjects.contains(object))
        return;

    mConnectedObjects.push_back(object);
}

void SCgObject::removeConnectedObject(SCgObject *object)
{
    if (!mConnectedObjects.contains(object))
        return;

    mConnectedObjects.removeOne(object);
}

bool SCgObject::haveConnectedObject(SCgObject *object) const
{
    return mConnectedObjects.contains(object);
}

SCgObject::SCgObjectList SCgObject::connectedObjects() const
{
    return mConnectedObjects;
}

void SCgObject::updateConnected()
{
    SCgObjectList::iterator it;
    for (it = mConnectedObjects.begin(); it != mConnectedObjects.end(); it++)
    {
        if (!(*it)->isDead())
            (*it)->positionChanged();
    }
}

void SCgObject::setIdtfValue(const QString &idtf)
{
    mIdtfValue = idtf;
    if(idtf != "")
    {
        if (!mTextItem)
        {
            mTextItem = new SCgTextItem;

            QFont font("Times New Roman [Arial]", 10, 10, false);
            font.setBold(true);
            font.setItalic(true);

            mTextItem->setFont(font);
            mTextItem->setParentItem(this);
            mTextItem->setZValue(7);
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_normal));
            //scene()->addItem(mTextItem);
        }
        mTextItem->setPlainText(mIdtfValue);
    } else if (mTextItem)
    {
        delete mTextItem;
        mTextItem = 0;
    }

    positionChanged();
}

QString SCgObject::idtfValue() const
{
    return mIdtfValue;
}

void SCgObject::setTypeAlias(const QString &type_alias)
{
    mTypeAlias = type_alias;
    update();
}

QString SCgObject::typeAlias() const
{
    return mTypeAlias;
}

void SCgObject::setColor(QColor color)
{
    mColor = color;
    update();
}

QColor SCgObject::color() const
{
    return mColor;
}

bool SCgObject::isDead() const
{
    return mIsDead;
}

void SCgObject::setDead(bool dead)
{
    mIsDead = dead;
    update();
}

void SCgObject::del(QList<SCgObject*> &delList)
{
    if (mIsDead)    return;

    mIsDead = true;

    delList.append(this);
    SCgObjectList::iterator obj = mConnectedObjects.begin();

    while (obj != mConnectedObjects.end())
    {
        (*obj)->del(delList);
        ++obj;
    }
}

void SCgObject::undel(SCgScene *scene)
{
    if (!mIsDead)   return;

    mIsDead = false;

    // add item to scene
    Q_ASSERT(scene);
    scene->addItem(this);
}

