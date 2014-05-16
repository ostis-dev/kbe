#ifndef SCGCOMMANDGOTOTEMPLATE_H
#define SCGCOMMANDGOTOTEMPLATE_H
#include "scgbasecommand.h"

class SCgCommandGotoTemplate: public QObject, public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    points   Position of nodes

        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandGotoTemplate(SCgScene *scene,
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


#endif // SCGCOMMANDGOTOTEMPLATE_H
