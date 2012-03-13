#ifndef SCGCLONEMODEEVENTHANDLER_H
#define SCGCLONEMODEEVENTHANDLER_H

#include "SCgEventHandler.h"

class SCgObject;

/*! Event handler for clone mode
*/
class SCgCloneModeEventHandler : public SCgEventHandler
{
public:
    explicit SCgCloneModeEventHandler(SCgScene *scene);
    virtual ~SCgCloneModeEventHandler();

    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    void mouseMove(QGraphicsSceneMouseEvent *event);

    void mousePress(QGraphicsSceneMouseEvent *event);

    virtual SCgScene::EditMode mode() {
        return SCgScene::Mode_Clone;
    }

    //! List of cloned objects
    QList<SCgObject*> mList;

    //! Value of undefined key in key pressed event
    int mNoKey;
};

#endif // SCGCLONEMODEEVENTHANDLER_H
