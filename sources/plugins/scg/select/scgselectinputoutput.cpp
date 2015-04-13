/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgselectinputoutput.h"

#include "scgscene.h"
#include "scgobject.h"

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
