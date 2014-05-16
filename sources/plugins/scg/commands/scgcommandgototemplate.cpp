#include "scgcommandgototemplate.h"
#include "scgbasecommand.h"

SCgCommandGotoTemplate::SCgCommandGotoTemplate(SCgScene *scene,
                                               const  QVector<QGraphicsItem*> &nodes,
                                               QUndoCommand *parent)
            : SCgBaseCommand(scene, 0, parent),
              mPoint(QPointF(0,0))
        {
            graphicsItems = mScene->createGotoTemplate(nodes);
            setText(QObject::tr("Create Goto Template"));
        }

        void SCgCommandGotoTemplate::redo()
        {
            foreach (SCgObject *ob, graphicsItems)
                if(ob->scene() != mScene)
                    mScene->addItem(ob);
        }

        void SCgCommandGotoTemplate::undo()
        {
            foreach (SCgObject *ob, graphicsItems)
                mScene->removeItem(ob);
        }

