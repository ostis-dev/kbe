#ifndef SCGCOMMANDTEMPLATE_H
#define SCGCOMMANDTEMPLATE_H

#include "scgbasecommand.h"

#include <QGraphicsItemGroup>

class SCgCommandTemplate :public QObject, public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    point   Position in scene
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandTemplate(SCgScene *scene,
                               const QPointF &point,
                               QUndoCommand *parent = 0);

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Node position in scene
    QPointF mPoint;

    QVector<SCgObject*> graphicsItems;

};

#endif // SCGCOMMANDTEMPLATE_H
