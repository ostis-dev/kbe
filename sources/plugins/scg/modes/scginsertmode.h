/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCGINSERTMODE_H_
#define SCGINSERTMODE_H_

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

#endif /* SCGINSERTMODEEVENTHANDLER_H_ */
