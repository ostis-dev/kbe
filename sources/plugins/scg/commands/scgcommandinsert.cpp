/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandinsert.h"
#include "scgobject.h"
#include "scgcontour.h"

SCgCommandInsert::SCgCommandInsert(SCgScene *scene,
                                   QList<SCgObject*> objList,
                                   SCgContour* parentContour,
                                   QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mList(objList)
    , mParent(parentContour)
{
    foreach(SCgObject* obj, mList)
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(objectFromListDestroyed(QObject*)));

    setText(QObject::tr("Insert"));
}

SCgCommandInsert::~SCgCommandInsert()
{
    foreach(SCgObject* obj, mList)
        delete obj;
}

void SCgCommandInsert::objectFromListDestroyed(QObject* obj)
{
    mList.removeOne((SCgObject*)obj);
}

void SCgCommandInsert::redo()
{
    SCgBaseCommand::redo();

    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;

        object->setDead(false);
        if(object->scene() != mScene)
            mScene->addItem(object);

        object->setParentItem(mParent);
        object->positionChanged();
    }
}

void SCgCommandInsert::undo()
{
    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;
        object->setDead(true);
        object->setParentItem(0);
        mScene->removeItem(object);
    }

    SCgBaseCommand::undo();
}
