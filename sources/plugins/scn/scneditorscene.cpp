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

#include <QKeyEvent>

SCnEditorScene::SCnEditorScene(QObject *parent) :
    QGraphicsScene(parent),
    mLevelOffset(30),
    mLevelDistance(10)
{
    appendField()->setSelected(true);

    // test
    for (quint32 i = 0; i < 10; i++)
    {
        SCnFieldItem *item = appendField();
        //item->setLevel(rand() % 2 + 1);
    }
}

SCnEditorScene::~SCnEditorScene()
{
    SCnFieldItem *item = 0;
    foreach(item, mFields)
        delete item;
    mFields.clear();
}

SCnFieldItem* SCnEditorScene::appendField(SCnFieldItem *afterField)
{
    SCnFieldItem *item = new SCnFieldItem();
    item->mEditorScene = this;

    if (afterField != 0)
    {
        bool inserted = false;
        FieldItems::iterator it;
        for (it = mFields.begin(); it != mFields.end(); ++it)
        {
            if (*it == afterField)
            {
                mFields.insert(it + 1, item);
                inserted = true;
                break;
            }
        }

        if (!inserted)
            mFields.push_back(item);
    }else
        mFields.push_back(item);

    connect(item, SIGNAL(changed(SCnFieldItem*, SCnFieldItem::ChangeType)), this, SLOT(itemChanged(SCnFieldItem*,SCnFieldItem::ChangeType)));

    addItem(item);
    updateFieldsPositions();

    return item;
}

void SCnEditorScene::removeField(SCnFieldItem *field)
{
    Q_ASSERT(mFields.contains(field));

    removeItem(field);
    for (quint32 i = 0; i < mFields.size(); i++)
    {
        if (mFields[i] == field)
        {
            mFields.remove(i);
            break;
        }
    }

    delete field;

    updateFieldsPositions();
}

void SCnEditorScene::moveField(SCnFieldItem *field, SCnFieldItem *afterField)
{
    Q_ASSERT(field != 0 && afterField != 0);

    bool inserted = false;
    FieldItems::iterator it;
    for (it != mFields.begin(); it != mFields.end(); ++it)
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

    updateFieldsPositions();
}

void SCnEditorScene::removeAllFields()
{
    SCnFieldItem *field = 0;
    foreach(field, mFields)
        delete field;
    mFields.clear();
}

void SCnEditorScene::selectNextField(SCnFieldItem *field)
{
    FieldItems::iterator it, it1;
    for (it = mFields.begin(); it != mFields.end(); ++it)
    {
        if (*it == field)
        {
            it1 = it + 1;
            if (it1 != mFields.end())
            {
                unselectItems();
                (*it1)->setSelected(true);
            }
            break;
        }
    }
}

void SCnEditorScene::selectPrevField(SCnFieldItem *field)
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
        {
            unselectItems();
            (*it1)->setSelected(true);
            break;
        }


        it1 = it;
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
    qreal y_offset = 0.f;
    foreach(field, mFields)
    {
        QRectF rect = field->boundingRect();
        // calculate new position
        QPointF pos;
        pos.setX(mLevelOffset * field->level() + rect.width() / 2.f);
        pos.setY(y_offset + rect.height() / 2.f);

        y_offset += mLevelDistance +rect.height();

        field->setPos(pos);
    }
}

void SCnEditorScene::itemChanged(SCnFieldItem *field, SCnFieldItem::ChangeType changeType)
{

}

void SCnEditorScene::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem*> selected = selectedItems();

    if (selected.size() == 1)
    {
        SCnFieldItem *field = qgraphicsitem_cast<SCnFieldItem*>(selected.first());

        if (field != 0)
        {
            SCnFieldItem::FieldState state = field->mState;

            if (event->key() == Qt::Key_Enter && state != SCnFieldItem::StateEdit)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                    field->startEditAttr();
                else
                    field->startEditValue();
            }

            if (event->key() == Qt::Key_Enter && (event->modifiers() & Qt::ControlModifier) && state == SCnFieldItem::StateEdit)
                field->applyEdit();

            if (event->key() == Qt::Key_Escape && state == SCnFieldItem::StateEdit)
                field->cancelEdit();

            if (state == SCnFieldItem::StateSelected)
            {
                if (event->key() == Qt::Key_Down)
                    selectNextField(field);
                if (event->key() == Qt::Key_Up)
                    selectPrevField(field);
            }
        }
    }

}

void SCnEditorScene::keyReleaseEvent(QKeyEvent *event)
{

}
