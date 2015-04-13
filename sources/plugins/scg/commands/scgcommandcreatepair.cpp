/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandcreatepair.h"
#include "scgpair.h"
#include "scgcontour.h"

SCgCommandCreatePair::SCgCommandCreatePair(SCgScene *scene,
                                           const QVector<QPointF> &points,
                                           SCgObject *beginObject,
                                           SCgObject *endObject,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mPoints(points)
    , mBeginObject(beginObject)
    , mEndObject(endObject)
    , mParentContour(parentContour)
{
    mObject = mScene->createSCgPair(mBeginObject, mEndObject, mPoints);

    connect(mObject, SIGNAL(destroyed()), this, SLOT(pairDestroyed()));
    setText(QObject::tr("Create pair"));
}

SCgCommandCreatePair::~SCgCommandCreatePair()
{
    if(mObject)
        delete mObject;
}

void SCgCommandCreatePair::pairDestroyed()
{
    mObject = 0;
}

void SCgCommandCreatePair::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::redo()",
               "Pair doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
        mScene->addItem(mObject);

    mObject->setDead(false);

    if(mParentContour)
        mObject->setParentItem(mParentContour);

    mObject->positionChanged();

}

void SCgCommandCreatePair::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::undo()",
               "Pair doesn't exists");

    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}
