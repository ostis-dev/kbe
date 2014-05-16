#include "scgcommandthentemplate.h"
#include "scgbasecommand.h"

SCgCommandThenTemplate::SCgCommandThenTemplate(SCgScene *scene,
                                               const  QVector<QGraphicsItem*> &nodes,
                                               QUndoCommand *parent)
            : SCgBaseCommand(scene, 0, parent),
              mPoint(QPointF(0,0))
        {
            graphicsItems = mScene->createThenTemplate(nodes);
            setText(QObject::tr("Create Then Template"));
        }

        void SCgCommandThenTemplate::redo()
        {
            foreach (SCgObject *ob, graphicsItems)
                if(ob->scene() != mScene)
                    mScene->addItem(ob);
        }

        void SCgCommandThenTemplate::undo()
        {
            foreach (SCgObject *ob, graphicsItems)
                mScene->removeItem(ob);
        }

