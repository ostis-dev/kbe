/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "scgcommandcreatelayer.h"

SCgCommandCreateLayer::SCgCommandCreateLayer(SCgScene *scene,
                                         QString const& layerName,
                                         SCgLayer::Type type,
                                         QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent),
      mName(layerName),
      mId(0),
      mScene(scene)
{
    scene->connect(this, SIGNAL(layerAdded(int,QString)),
                   SIGNAL(layerAdded(int, QString)),
                   Qt::DirectConnection);
    scene->connect(this, SIGNAL(layerRemoved(int)),
                   SIGNAL(layerRemoved(int)),
                   Qt::DirectConnection);
    scene->connect(this, SIGNAL(currentLayerChanged(int)),
                   SIGNAL(currentLayerChanged(int)),
                   Qt::DirectConnection);

    mId = scene->createSCgLayer(mName, type);

    if (mName.isEmpty())
        mName = tr("New layer") + " " + QString::number(mId);

    emit layerAdded(mId, mName);
    emit currentLayerChanged(mId);

    setText(QObject::tr("Create layer")+ " \"" + mName+ "\"");
}

SCgCommandCreateLayer::~SCgCommandCreateLayer()
{

}

void SCgCommandCreateLayer::undo()
{
    mScene->getLayers()[mId]->setDead(true);
    emit layerRemoved(mId);

    SCgBaseCommand::undo();
}

void SCgCommandCreateLayer::redo()
{
    mScene->getLayers()[mId]->setDead(false);
    emit layerAdded(mId, mName);
    mScene->selectCurrentLayer(mId);
    emit currentLayerChanged(mId);

    SCgBaseCommand::redo();
}
