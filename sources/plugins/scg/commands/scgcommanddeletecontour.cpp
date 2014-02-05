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

#include "scgcommanddeletecontour.h"
#include "scgcommandobjectdelete.h"

#include "scgcontour.h"

SCgCommandDeleteContour::SCgCommandDeleteContour(SCgScene *scene,
                                                 SCgContour *contour,
                                                 QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mContour(contour)
{
    setText(QObject::tr("Delete contour"));
    Q_ASSERT_X(mContour != 0,
               "SCgCommandDeleteJustContour::SCgCommandDeleteJustContour(SCgScene *scene, "
               "SCgContour *contour, QUndoCommand *parent)",
               "Pointer to contour object is null");
}

SCgCommandDeleteContour::~SCgCommandDeleteContour()
{
}

void SCgCommandDeleteContour::redo()
{
    mChilds.clear();

    QGraphicsItem *parent = mContour->parentItem();
    QList<QGraphicsItem*> childs = mContour->childItems();
    QList<QGraphicsItem*>::iterator it;
    for (it = childs.begin(); it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        Q_ASSERT(item);
        if (!item || !SCgObject::isSCgObjectType(item->type()))
            continue;

        mChilds.push_back(item);
        item->setParentItem(parent);
    }

    if (childCount() == 0)
        new SCgCommandObjectDelete(mScene, mContour, this);

    SCgBaseCommand::redo();
}

void SCgCommandDeleteContour::undo()
{
    SCgBaseCommand::undo();

    QList<QGraphicsItem*>::iterator it;
    for (it = mChilds.begin(); it != mChilds.end(); ++it)
    {
        QGraphicsItem *item = *it;

        Q_ASSERT(item);
        if (item)
            item->setParentItem(mContour);
    }
}
