/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <QObject>
#include "scgbasecommand.h"
#include "scglayer.h"

/*! Layer adding command
  */
class SCgCommandCreateLayer : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    explicit SCgCommandCreateLayer(SCgScene *scene,
                                  QString const& layerName,
                                  SCgLayer::Type type,
                                  QUndoCommand *parent = 0);

    virtual ~SCgCommandCreateLayer();

protected:
    void redo();
    void undo();

signals:
    void layerAdded(int id, QString name);
    void layerRemoved(int id);
    void currentLayerChanged(int id);

private:
    QString mName;
    uint mId;
    SCgScene* mScene;

};
