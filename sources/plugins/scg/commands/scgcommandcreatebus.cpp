/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandcreatebus.h"
#include "scgnode.h"
#include "scgcontour.h"
#include "scgbus.h"

SCgCommandCreateBus::SCgCommandCreateBus(SCgScene *scene,
                                           SCgNode *owner,
                                           const QVector<QPointF> &points,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mOwner(owner)
    , mPoints(points)
    , mParentContour(parentContour)
{
    mObject = mScene->createSCgBus(mPoints, mOwner);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(busDestroyed()));
    setText(QObject::tr("Create bus"));
}

SCgCommandCreateBus::~SCgCommandCreateBus()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateBus::busDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateBus::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::redo()",
               "Bus doesn't exists");
    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setParentItem(mParentContour);
    mObject->setDead(false);

    static_cast<SCgBus*>(mObject)->setOwner(mOwner);
}

void SCgCommandCreateBus::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::undo()",
               "Bus doesn't exists");

    static_cast<SCgBus*>(mObject)->setOwner(0);
    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
