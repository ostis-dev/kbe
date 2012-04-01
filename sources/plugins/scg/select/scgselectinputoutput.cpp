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

#include "scgselectinputoutput.h"

#include "../scgscene.h"
#include "../scgobject.h"

SCgSelectInputOutput::SCgSelectInputOutput(QObject *parent) :
    SCgSelect(parent)
{
}

SCgSelectInputOutput::~SCgSelectInputOutput()
{
}

void SCgSelectInputOutput::doSelection(SCgScene *scene)
{
    Q_ASSERT(scene != 0);

    // get all selected objects
    QList<QGraphicsItem*> items = scene->selectedItems();
    QGraphicsItem *item = 0;
    foreach(item, items)
    {
        // skip non scg-objects
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        SCgObject *obj = static_cast<SCgObject*>(item);

        // set selection for all input and output pairs
        SCgObject::SCgObjectList connected = obj->connectedObjects();
        SCgObject *c_obj = 0;
        foreach(c_obj, connected)
            c_obj->setSelected(true);
    }
}
