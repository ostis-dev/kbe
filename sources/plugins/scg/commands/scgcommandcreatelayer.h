#ifndef SCGCOMMANDADDLAYER_H
#define SCGCOMMANDADDLAYER_H

#include <QObject>
#include "scgbasecommand.h"
#include "scglayer.h"

/*! Layer adding command
  */
class SCgCommandCreateLayer : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    layerName  Layer's name
      @param    type        Layer's type
      @param    parent      Pointer to parent command
      */
    explicit SCgCommandCreateLayer(SCgScene *scene,
                                  QString const& layerName,
                                  SCgLayer::Type type,
                                  QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateLayer();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

signals:
    /*! Signal that emitting on layer adding
      * @param id Layer's id
      * @param name Layer's name
      */
    void layerAdded(int id, QString name);

    /*! Signal that emitting on layer removing
      * @param id Layer's id
      */
    void layerRemoved(int id);

    /*! Signal that emitting on current layer changing
      * @param id Layer's id
      */
    void currentLayerChanged(int id);

private:
    //! Layer name
    QString mName;

    //! Layer id
    uint mId;

    //! SCgScene
    SCgScene* mScene;

};

#endif // SCGCOMMANDADDLAYER_H
