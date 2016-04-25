/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once
#include "scgmode.h"

class SCgConstructionMode: public SCgMode
{
public:
    typedef enum {

        Type_3elements,
        Type_5elements

    } ConstructionType;

    explicit SCgConstructionMode(SCgScene* parent, ConstructionType type);

    virtual ~SCgConstructionMode();

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

    virtual SCgScene::EditMode mode();

    //! @sa SCgEventHandler::deactivate()
    virtual void activate();

    //! @sa SCgEventHandler::deactivate()
    virtual void deactivate();

private:
    ConstructionType type;
    QGraphicsItemGroup* mConstruction;

    void threeElementConstruction(QList<QGraphicsItem*> & items);

    void fiveElementConstruction(QList<QGraphicsItem*> & items);
};
