#include "scgcommanddeletelayer.h"

SCgCommandDeleteLayer::SCgCommandDeleteLayer(SCgScene *scene,
                                               uint id,
                                               QString const& layerName,
                                               QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent),
      mName(layerName),
      mId(id),
      mScene(scene)
{
    scene->connect(this, SIGNAL(layerAdded(int,QString)), SIGNAL(layerAdded(int, QString)), Qt::DirectConnection);
    scene->connect(this, SIGNAL(layerRemoved(int)), SIGNAL(layerRemoved(int)), Qt::DirectConnection);
    scene->connect(this, SIGNAL(currentLayerChanged(int)), SIGNAL(currentLayerChanged(int)));

    mScene->scgLayers()[mId]->setDead(true);
    emit layerRemoved(mId);
    emit currentLayerChanged(mId);

    setText(QObject::tr("Delete layer"));
}

SCgCommandDeleteLayer::~SCgCommandDeleteLayer()
{

}

void SCgCommandDeleteLayer::undo()
{
    mScene->scgLayers()[mId]->setDead(false);
    emit layerAdded(mId, mName);
    mScene->selectCurrentLayer(mId);
    emit currentLayerChanged(mId);

    SCgBaseCommand::undo();
}

void SCgCommandDeleteLayer::redo()
{
    mScene->scgLayers()[mId]->setDead(true);
    emit layerRemoved(mId);
    emit currentLayerChanged(0);

    SCgBaseCommand::redo();
}
