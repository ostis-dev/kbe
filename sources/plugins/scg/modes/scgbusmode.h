/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgmode.h"

class SCgBusMode: public SCgMode
{
    Q_OBJECT
public:
    explicit SCgBusMode(SCgScene* parent);

    virtual ~SCgBusMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    virtual void mousePress(QGraphicsSceneMouseEvent *event);
    virtual void mouseMove(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    virtual SCgScene::EditMode mode() const;


protected:


};


