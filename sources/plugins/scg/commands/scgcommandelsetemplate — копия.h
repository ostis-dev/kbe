#ifndef SCGCOMMANDELSETEMPLATE_H
#define SCGCOMMANDELSETEMPLATE_H


#include "scgbasecommand.h"

#include <QGraphicsItemGroup>

class SCgCommandElseTemplate :public QObject, public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    points   Position of nodes

        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandElseTemplate(SCgScene *scene,
                               const  QVector<QGraphicsItem*> &nodes,
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




#endif // SCGCOMMANDELSETEMPLATE_H
