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
#include <QtWidgets/QGraphicsView>
#include <QDebug>

SCnEditorScene::SCnEditorScene(QObject *parent) :
    QGraphicsScene(parent),
    mLevelOffset(30),
    mLevelDistance(10)
{
    SCnFieldItem *pitem = new SCnFieldGlobalIdtf(this);
    pitem->setValue("test");
    appendField(pitem);

    for (quint32 i = 0; i < 5; i++)
    {
        SCnFieldItem *item = new SCnFieldGlobalIdtf(pitem);
        item->setValue(QString("test %1").arg(i));
        item->setParentItem(pitem);

        for (quint32 j = 0; j < 5; j++)
        {
            SCnFieldItem *jitem = new SCnFieldGlobalIdtf(item);
            jitem->setValue(QString("test %1_%2").arg(i).arg(j));
            jitem->setParentItem(item);
        }
    }

    inputDialog = new SCnInputDialog();
    connect(inputDialog, SIGNAL(textRecieved(QString)), this, SLOT(setTextForSelectedField(QString)));
}

SCnEditorScene::~SCnEditorScene()
{
    foreach(SCnFieldItem *item, mFields)
        delete item;
    mFields.clear();
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
    if (!mFields.contains(field))
    {
        SCnFieldItem* parent = parentField(field);
        removeItem(field);

        delete field;

        while (parent)
        {
            parent->updateOnChilds();
            parent = parentField(parent);
        }

        updateFieldsPositions();
    }
}

void SCnEditorScene::removeAllFields()
{
    SCnFieldItem *field = 0;
    foreach(field, mFields)
        delete field;
    mFields.clear();
}

SCnFieldItem* SCnEditorScene::nextField(SCnFieldItem *field, bool withLevelChange)
{    
    SCnFieldItem *nextField = 0;
    bool prevFieldComingFlag = false;
    QGraphicsItem *parentItem = field->parentItem();
    if (!parentItem)
        return 0;
    QList<QGraphicsItem *> items = withLevelChange
            ? this->items()
            : parentItem->childItems();
    foreach(QGraphicsItem *item, items)
    {
        if (nextField->isSCnFieldType(item->type()))
        {
            nextField = static_cast<SCnFieldItem*>(item);
            if (prevFieldComingFlag)
                return nextField;
            if (nextField == field)
                prevFieldComingFlag = true;
        }
    }
    return 0;
}

SCnFieldItem* SCnEditorScene::prevField(SCnFieldItem *field, bool withLevelChange)
{
    SCnFieldItem *prevField;
    SCnFieldItem *nextField = 0;
    QGraphicsItem *parentItem = field->parentItem();
    if (!parentItem)
        return 0;
    QList<QGraphicsItem *> items = withLevelChange
            ? this->items()
            : parentItem->childItems();
    foreach (QGraphicsItem *item, items)
    {
        if (nextField->isSCnFieldType(item->type()))
        {
            prevField = nextField;
            nextField = static_cast<SCnFieldItem*>(item);
            if (nextField == field)
                return prevField;
        }
    }
    return 0;
}

SCnFieldItem* SCnEditorScene::parentField(SCnFieldItem *field)
{
    SCnFieldItem *parentField = 0;
    QGraphicsItem *parentItem = field->parentItem();
    if (parentItem && field->isSCnFieldType(parentItem->type()))
    {
        parentField = static_cast<SCnFieldItem *>(parentItem);
    }
    return parentField;
}

SCnFieldItem* SCnEditorScene::childField(SCnFieldItem *field)
{
    SCnFieldItem *childField = 0;
    QGraphicsItem *firstChildItem = 0;
    QList<QGraphicsItem *> childItems = field->childItems();
    if (!childItems.isEmpty())
    {
        firstChildItem = childItems.first();
        if (field->isSCnFieldType(firstChildItem->type()))
        {
            childField = static_cast<SCnFieldItem *>(firstChildItem);
        }
    }
    return childField;
}

void SCnEditorScene::selectField(SCnFieldItem *field)
{
    if (field)
    {
        unselectItems();
        field->setSelected(true);
        views().first()->centerOn(field);
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

void SCnEditorScene::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem*> selected = selectedItems();
    if (selected.size() == 1)
    {
        SCnFieldItem *field = static_cast<SCnFieldItem*>(selected.first());
        if (field)
        {
            SCnFieldItem::FieldState state = field->state();
            if (state == SCnFieldItem::StateSelected)
            {
                if (event->key() == Qt::Key_Down)
                {
                    if (event->modifiers() & Qt::ShiftModifier)
                    {
                        moveFieldDown(field);
                    }
                    else
                    {
                        selectField(nextField(field, false));
                    }
                }
                else if (event->key() == Qt::Key_Up)
                {
                    if (event->modifiers() & Qt::ShiftModifier)
                    {
                        moveFieldUp(field);
                    }
                    else
                    {
                        selectField(prevField(field, false));
                    }
                }
                else if (event->key() == Qt::Key_Left)
                {
                    selectField(parentField(field));
                }
                else if (event->key() == Qt::Key_Right)
                {
                    selectField(childField(field));
                }
                else if (event->key() == Qt::Key_Enter)
                {
                    //field->startEdit();
                    inputDialog->show();
                    inputDialog->setExistingText(field->value());
                }
                else if (event->key() == Qt::Key_Insert)
                {
                    insertField(field);
                }
                else if (event->key() == Qt::Key_Delete)
                {
                    removeField(field);
                }
            }
            else if (state == SCnFieldItem::StateEdit)
            {
                if (event->key() == Qt::Key_Enter)
                {
                    field->applyEdit();
                }
                else if (event->key() == Qt::Key_Escape)
                {
                    field->cancelEdit();
                }
            }
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void SCnEditorScene::moveFieldUp(SCnFieldItem *field)
{
    SCnFieldItem *previous = prevField(field, false);
    if (previous)
    {
        swapFields(field, previous);
        //field->stackBefore(previous);
    }
}

void SCnEditorScene::moveFieldDown(SCnFieldItem *field)
{
    SCnFieldItem *next = nextField(field, false);
    if (next)
    {
        swapFields(field, next);
        //next->stackBefore(field);
    }
}

void SCnEditorScene::swapFields(SCnFieldItem *field_1, SCnFieldItem *field_2)
{
    QGraphicsItem *parent = field_1->parentItem();
    if (parent == field_2->parentItem())
    {
        QList<QGraphicsItem *> children = parent->childItems();
        int index_1 = children.indexOf(field_1);
        int index_2 = children.indexOf(field_2);
        if (index_1 >= 0 && index_2 >= 0)
        {
            children.swap(index_1, index_2);
            static_cast<SCnFieldItem*>(parent)->updateOnChilds();
            updateFieldsPositions();
        }
    }
}

void SCnEditorScene::insertField(SCnFieldItem *field)
{
    SCnFieldItem *item = new SCnFieldGlobalIdtf(field);
    item->setValue("new field");
    item->setParentItem(field);
    while (field)
    {
        field->updateOnChilds();
        field = parentField(field);
    }
    updateFieldsPositions();
}

void SCnEditorScene::setTextForSelectedField(const QString &text)
{
    QList<QGraphicsItem*> selected = selectedItems();
    if (selected.size() == 1)
    {
        SCnFieldItem *field = static_cast<SCnFieldItem*>(selected.first());
        field->setValue(text);
    }
}
