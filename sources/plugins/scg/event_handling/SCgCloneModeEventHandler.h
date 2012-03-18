#ifndef SCGCLONEMODEEVENTHANDLER_H
#define SCGCLONEMODEEVENTHANDLER_H

#include "SCgInsertModeEventHandler.h"

class SCgCloneModeEventHandler : public SCgInsertModeEventHandler
{
public:
    //! Constructor
    explicit SCgCloneModeEventHandler(SCgScene* scene);

    //! Destructor
    virtual ~SCgCloneModeEventHandler();

    void mousePress(QGraphicsSceneMouseEvent *event);

    //! @sa SCgEventHandler::activate()
    void activate();

    //! @sa SCgEventHandler::deactivate()
    void deactivate();

    //! @sa SCgEventHandler::mode()
    SCgScene::EditMode mode() { return SCgScene::Mode_Clone; }
};

#endif // SCGCLONEMODEEVENTHANDLER_H
