/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandobjectdelete.h"
#include "scgobject.h"

SCgCommandObjectDelete::SCgCommandObjectDelete(SCgScene *scene,
                                               SCgObject *object,
                                               QUndoCommand *parent)
        : SCgBaseCommand(scene, object, parent)
{
    setText(QObject::tr("Delete object"));
}

SCgCommandObjectDelete::~SCgCommandObjectDelete()
{

}

void SCgCommandObjectDelete::redo()
{
    mDelList.clear();
    mParents.clear();

    mObject->del(mDelList);

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        QGraphicsItem *parent = object->parentItem();

        mParents[object] = parent;

        if(object->scene() == mScene)
        {
            object->setParentItem(0);
            mScene->removeItem(object);
        }
    }

    SCgBaseCommand::redo();
}
//back
void SCgCommandObjectDelete::undo()
{
    SCgBaseCommand::undo();

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        if(!object->parentItem())
        {
            QGraphicsItem *parent = mParents[object];

            object->undel(mScene);

            object->setParentItem(parent);
            object->positionChanged();
        }
    }

}
