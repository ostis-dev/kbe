/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgmode.h"

class SCpMode : public SCgMode
{
    Q_OBJECT
public:
    explicit SCpMode(SCgScene * parent);
    virtual ~SCpMode();

protected:
    virtual SCgScene::EditMode mode() const;

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mousePress(QGraphicsSceneMouseEvent *event);

    void mouseMove(QGraphicsSceneMouseEvent *event);

    void mouseRelease(QGraphicsSceneMouseEvent *event);

    void mouseDoubleClick(QGraphicsSceneMouseEvent *event);
    /*! @}*/
};
