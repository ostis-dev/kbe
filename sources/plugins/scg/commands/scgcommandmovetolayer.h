#ifndef SCGCOMMANDMOVETOLAYER_H
#define SCGCOMMANDMOVETOLAYER_H

#include <QObject>

#include <QList>

#include "scgbasecommand.h"
#include "scglayer.h"

/*! Move to layer command
  */
class SCgCommandMoveToLayer : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    objects     List of pointers to moved objects
      @param    nextId      Next layer's id
      @param    parent      Pointer to parent command
      */
    explicit SCgCommandMoveToLayer(SCgScene *scene,
                                    QList<SCgObject*> objects,
                                    QList<uint> prevIds,
                                    uint nextId,
                                    QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandMoveToLayer();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

private:
    //! Moved objects
    QList<SCgObject*> mObjects;

    //! Previous layer's ids
    QList<uint> mPrevIds;

    //! Next layer's id
    uint mNextId;

    //! SCgScene
    SCgScene* mScene;

};

#endif // SCGCOMMANDMOVETOLAYER_H
