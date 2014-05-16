#include "scgcommandelsetemplate.h"

SCgCommandElseTemplate::SCgCommandElseTemplate(SCgScene *scene,
                                       const  QVector<QGraphicsItem*> &nodes,
                                       QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent),
      mPoint(QPointF(0,0))
{
    graphicsItems = mScene->createElseTemplate(nodes);
    setText(QObject::tr("Create Else Template"));
}

void SCgCommandElseTemplate::redo()
{
    foreach (SCgObject *ob, graphicsItems)
        if(ob->scene() != mScene)
            mScene->addItem(ob);
}

void SCgCommandElseTemplate::undo()
{
    foreach (SCgObject *ob, graphicsItems)
        mScene->removeItem(ob);
}
