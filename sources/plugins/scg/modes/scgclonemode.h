/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scginsertmode.h"

class SCgCloneMode : public SCgInsertMode
{
public:
    //! Constructor
    explicit SCgCloneMode(SCgScene* scene);

    //! Destructor
    virtual ~SCgCloneMode();

    void mousePress(QGraphicsSceneMouseEvent *event);

    //! @sa SCgEventHandler::activate()
    void activate();

    //! @sa SCgEventHandler::deactivate()
    void deactivate();

    //! @sa SCgEventHandler::mode()
    SCgScene::EditMode mode() { return SCgScene::Mode_Clone; }
};

