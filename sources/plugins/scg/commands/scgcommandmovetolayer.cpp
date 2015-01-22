#include "scgcommandmovetolayer.h"

SCgCommandMoveToLayer::SCgCommandMoveToLayer(SCgScene *scene,
                                               QList<SCgObject *> const& objects,
                                               QList<uint> const& prevIds,
                                               uint nextId,
                                               QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent),
      mObjects(objects),
      mPrevIds(prevIds),
      mNextId(nextId),
      mScene(scene)
{
    Q_FOREACH(SCgObject* object, objects)
    {
        scene->moveObjectToLayer(object, mNextId);
    }

    setText(QObject::tr("Move to layer"));
}

SCgCommandMoveToLayer::~SCgCommandMoveToLayer()
{

}

void SCgCommandMoveToLayer::undo()
{
    QList<SCgObject*>::iterator objIt;
    QList<uint>::iterator prevIdIt;
    for(objIt = mObjects.begin(),
        prevIdIt = mPrevIds.begin();
        objIt != mObjects.end() && prevIdIt != mPrevIds.end();
        ++objIt, ++prevIdIt)
    {
        mScene->moveObjectToLayer(*objIt, *prevIdIt);
    }

    SCgBaseCommand::undo();
}

void SCgCommandMoveToLayer::redo()
{
    Q_FOREACH(SCgObject* object, mObjects)
    {
        mScene->moveObjectToLayer(object, mNextId);
    }

    SCgBaseCommand::redo();
}
