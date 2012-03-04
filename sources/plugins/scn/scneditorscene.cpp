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

SCnEditorScene::SCnEditorScene(QObject *parent) :
    QGraphicsScene(parent),
    mLevelOffset(30),
    mLevelDistance(10)
{
    appendField();
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
        QList<SCnFieldItem*>::iterator it;
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
    }

    connect(item, SIGNAL(changed(SCnFieldItem*,ChangeType)), this, SLOT(itemChanged(SCnFieldItem*,SCnFieldItem::ChangeType)));
    updateFieldsPositions();

    addItem(item);

    return item;
}

void SCnEditorScene::removeField(SCnFieldItem *field)
{
    Q_ASSERT(mFields.contains(field));

    removeItem(field);
    mFields.removeOne(field);
    delete field;

    updateFieldsPositions();
}

void SCnEditorScene::moveField(SCnFieldItem *field, SCnFieldItem *afterField)
{
    Q_ASSERT(field != 0 && afterField != 0);

    bool inserted = false;
    QList<SCnFieldItem*>::iterator it;
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

        field->setPos(pos);
    }
}

void SCnEditorScene::itemChanged(SCnFieldItem *field, SCnFieldItem::ChangeType changeType)
{

}
