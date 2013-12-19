#include "scgcommandtemplate.h"

SCgCommandTemplate::SCgCommandTemplate(SCgScene *scene,
                                       const QPointF &point,
                                       QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent),
      mPoint(point)
{
    graphicsItems = mScene->createSCgTemplate(mPoint);
    setText(QObject::tr("Create Template"));
}

void SCgCommandTemplate::redo()
{
    foreach (SCgObject *ob, graphicsItems)
        if(ob->scene() != mScene)
            mScene->addItem(ob);
}

void SCgCommandTemplate::undo()
{
    foreach (SCgObject *ob, graphicsItems)
        mScene->removeItem(ob);
}
