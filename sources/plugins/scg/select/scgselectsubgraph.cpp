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

#include "scgselectsubgraph.h"

#include "scgscene.h"
#include "scgbus.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"

SCgSelectSubGraph::SCgSelectSubGraph(QObject *parent) :
    SCgSelect(parent)
{
}

SCgSelectSubGraph::~SCgSelectSubGraph()
{
}

void SCgSelectSubGraph::doSelection(SCgScene *scene)
{
    Q_ASSERT(scene != 0);

    QList<QGraphicsItem*> items = scene->selectedItems();
    QGraphicsItem *item = 0;
    foreach(item, items)
    {
        if (item && SCgObject::isSCgObjectType(item->type()))
            select(static_cast<SCgObject*>(item));
    }
}

void SCgSelectSubGraph::select(SCgObject *obj)
{
    obj->setSelected(true);

    // select parent
    //if (obj->parentItem() != 0 && SCgObject::isSCgObjectType(obj->parentItem()->type()))
        //select(static_cast<SCgObject*>(obj->parentItem()));

    Q_ASSERT(obj);
    if (!obj)
        return;

    switch(obj->type())
    {
    case SCgBus::Type:
        {
            SCgBus *bus = static_cast<SCgBus*>(obj);
            if (bus->owner() != 0 && !bus->owner()->isSelected())
                select(bus->owner());
        }
        break;

    case SCgNode::Type:
        {
            SCgNode *node = static_cast<SCgNode*>(obj);
            if (node->bus() != 0 && !node->bus()->isSelected())
                select(node->bus());
        }
        break;

    case SCgPair::Type:
        {
            SCgPair *pair = static_cast<SCgPair*>(obj);
            if (pair->beginObject() != 0 && !pair->beginObject()->isSelected())
                select(pair->beginObject());

            if (pair->endObject() != 0 && !pair->endObject()->isSelected())
                select(pair->endObject());
        }
        break;

    case SCgContour::Type:
        {
            SCgContour *contour = static_cast<SCgContour*>(obj);
            QList<QGraphicsItem*> items = contour->childItems();
            QGraphicsItem *item = 0;
            foreach(item, items)
            {
                // skip not sc.g-objects and selected objects
                if (!SCgObject::isSCgObjectType(item->type()) || item->isSelected())
                    continue;

                select(static_cast<SCgObject*>(item));
            }
        }
        break;
    }

    SCgObject::SCgObjectList connected = obj->connectedObjects();
    SCgObject *c_obj = 0;
    foreach(c_obj, connected)
    {
        // skip selected objects
        if (c_obj->isSelected())
            continue;

        select(c_obj);
    }
}
