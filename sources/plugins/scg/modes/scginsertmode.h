/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once
#include "scgmode.h"

class SCgInsertMode: public SCgMode
{
public:
    explicit SCgInsertMode(SCgScene* parent);

    virtual ~SCgInsertMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    virtual void mousePress(QGraphicsSceneMouseEvent *event);

    virtual void mouseMove(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    /*! @defgroup keyboardEvendHandling Keyboard Events
     *  @{
     */
    virtual void keyPress(QKeyEvent *event);
    /*! @}*/

    //! Cleans current edit state.
    virtual void clean();

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_InsertTemplate;
    }

    //! @sa SCgEventHandler::deactivate()
    virtual void activate();

    //! @sa SCgEventHandler::deactivate()
    virtual void deactivate();

protected:
    //! Inserted objects
    QGraphicsItemGroup* mInsertedObjectGroup;

};

