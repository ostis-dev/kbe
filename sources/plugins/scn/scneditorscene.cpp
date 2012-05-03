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

#include "scneditorscene.h"
#include "scnfielditem.h"
#include "scnfieldglobalidtf.h"

#include <QKeyEvent>
#include <QGraphicsView>
#include <QDebug>

SCnEditorScene::SCnEditorScene(QObject *parent) :
    QGraphicsScene(parent),
    mLevelOffset(30),
    mLevelDistance(10)
{

    SCnFieldItem *root_item = new SCnFieldGlobalIdtf(this);
    root_item->setValue("Item1");
    appendField(root_item);
    root_item->acceptedMouseButtons();
    root_item->acceptDrops();


    //root_item->scale();

    SCnFieldItem *pitem = new SCnFieldGlobalIdtf(this);
    pitem->setValue("Item");
    appendField(pitem);

    for (quint32 i = 0; i < 10; i++)
    {
        SCnFieldItem *item = new SCnFieldGlobalIdtf(pitem);
        item->setValue(QString("test %1").arg(i));
        item->setParentItem(pitem);
    }
    mMenu = new QMenu();
    mMenu->addAction("Add New Item");
    connect(mMenu, SIGNAL(triggered(QAction*)), SLOT(menuActivated(QAction*)));

}

SCnEditorScene::~SCnEditorScene()
{
    SCnFieldItem *item = 0;
    foreach(item, mFields)
        delete item;
    mFields.clear();
    delete mMenu;
}

void SCnEditorScene::updateItems(QRectF){
    updateFieldsPositions();
}

SCnFieldItem* SCnEditorScene::appendField(SCnFieldItem *field, SCnFieldItem *afterField)
{
    if (field->mEditorScene != 0)
        field->mEditorScene->removeField(field);

    field->mEditorScene = this;

    if (afterField != 0)
    {
        bool inserted = false;
        FieldItems::iterator it;
        for (it = mFields.begin(); it != mFields.end(); ++it)
        {
            if (*it == afterField)
            {
                mFields.insert(it + 1, field);
                inserted = true;
                break;
            }
        }

        if (!inserted)
            mFields.push_back(field);
    }else
        mFields.push_back(field);

    addItem(field);
    updateFieldsPositions();

    return field;
}

void SCnEditorScene::removeField(SCnFieldItem *field)
{
    Q_ASSERT(mFields.contains(field));

    removeItem(field);
    for (qint32 i = 0; i < mFields.size(); i++)
    {
        if (mFields[i] == field)
        {
            mFields.remove(i);
            break;
        }
    }



    updateFieldsPositions();
}

void SCnEditorScene::removeAllFields()
{
    SCnFieldItem *field = 0;
    foreach(field, mFields)
        delete field;
    mFields.clear();
}

SCnFieldItem* SCnEditorScene::nextField(SCnFieldItem *field)
{
    FieldItems::iterator it, it1;
    for (it = mFields.begin(); it != mFields.end(); ++it)
    {
        if (*it == field)
        {
            it1 = it + 1;
            if (it1 != mFields.end())
                return *it1;
            break;
        }
    }

    return 0;
}

SCnFieldItem* SCnEditorScene::prevField(SCnFieldItem *field)
{
    FieldItems::iterator it, it1;
    for (it = mFields.begin(); it != mFields.end(); ++it)
    {
        if (it == mFields.begin())
        {
            it1 = it;
            continue;
        }

        if (*it == field)
            return *it1;

        it1 = it;
    }

    return 0;
}

void SCnEditorScene::selectNextField(SCnFieldItem *field)
{
    SCnFieldItem *next = nextField(field);
    if (next != 0)
    {
        unselectItems();
        next->setSelected(true);
        views().first()->centerOn(next);
    }
}

void SCnEditorScene::selectPrevField(SCnFieldItem *field)
{
    SCnFieldItem *prev = prevField(field);
    if (prev != 0)
    {
        unselectItems();
        prev->setSelected(true);
        views().first()->centerOn(prev);
    }
}

void SCnEditorScene::unselectItems()
{
    QList<QGraphicsItem*> items = selectedItems();
    QGraphicsItem *item = 0;
    foreach(item, items)
        item->setSelected(false);
}

void SCnEditorScene::updateFieldsPositions()
{
    SCnFieldItem *field = 0;
    qreal y_offset = 40.f;
    qreal max_width = 0.f;
    foreach(field, mFields)
    {
        QRectF rect = field->boundingRect();
        // calculate new position
        QPointF pos;
        pos.setX(20);
        pos.setY(y_offset);

        y_offset += mLevelDistance + rect.height();

        qreal w = rect.width();
        max_width = qMax(w, max_width);

        field->setPos(pos);
    }

    // setup new bounding box for scene
    setSceneRect(0, 0, max_width, y_offset);
}

void SCnEditorScene::itemChanged(SCnFieldItem *field, SCnFieldItem::ChangeType changeType)
{
    switch (changeType)
    {

    case SCnFieldItem::StateChanged:
    case SCnFieldItem::BoundChanged:
        updateFieldsPositions();
    };
}

void SCnEditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QList<QGraphicsItem*> selected = selectedItems();
            if (selected.size() == 0)
                mMenu->exec(event->screenPos());
    }
    QGraphicsScene::mousePressEvent(event);
}

void SCnEditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void SCnEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        AddNewItem();
    }
}

void SCnEditorScene::AddNewItem()
{
    QList<QGraphicsItem*> selected = selectedItems();
    if (selected.size() == 0)
    {
        SCnFieldItem* item = new SCnFieldGlobalIdtf(this);
        item->setValue("newItem");
        appendField(item);
        item->EditSlot();
    }
    update();
    updateFieldsPositions();
}

void SCnEditorScene::menuActivated(QAction *act)
{
    AddNewItem();
}

void SCnEditorScene::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem*> selected = selectedItems();

    if (selected.size() == 1)
    {
        SCnFieldItem *field = qgraphicsitem_cast<SCnFieldItem*>(selected.first());

        if (field != 0 && field->state() != SCnFieldItem::StateEdit)
        {
            SCnFieldItem::FieldState state = field->state();

            if (state == SCnFieldItem::StateSelected)
            {
                if (event->key() == Qt::Key_Down)
                    selectNextField(field);
                if (event->key() == Qt::Key_Up)
                    selectPrevField(field);

            }

            // change level

        }
    }

    QGraphicsScene::keyPressEvent(event);

}

