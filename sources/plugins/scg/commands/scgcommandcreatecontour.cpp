/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandcreatecontour.h"
#include "scgcontour.h"

SCgCommandCreateContour::SCgCommandCreateContour(SCgScene *scene,
                                                 const QList<QGraphicsItem *> &childs,
                                                 const QVector<QPointF> &points,
                                                 SCgContour *parentContour,
                                                 QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mPoints(points)
    , mChildObjects(childs)
    , mParentContour(parentContour)
{
    mObject = mScene->createSCgContour(mPoints);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(contourDestroyed()));
    setText(QObject::tr("Create contour"));
}

SCgCommandCreateContour::~SCgCommandCreateContour()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateContour::contourDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateContour::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::redo()",
               "Contour doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setDead(false);

    QList<QGraphicsItem*>::iterator it = mChildObjects.begin();
    for (; it != mChildObjects.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        (*it)->setParentItem(mObject);
    }

    if(mParentContour)
        mObject->setParentItem(mParentContour);
}

void SCgCommandCreateContour::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::undo()",
               "Contour doesn't exists");

    QGraphicsItem *parent = mObject->parentItem();
    QList<QGraphicsItem*> childs = mObject->childItems();
    QList<QGraphicsItem*>::iterator it = childs.begin();
    for (; it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        item->setParentItem(parent);
    }

    mObject->setParentItem(0);
    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
