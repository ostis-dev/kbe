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

#ifndef SCGINSERTMODEEVENTHANDLER_H_
#define SCGINSERTMODEEVENTHANDLER_H_

#include "SCgEventHandler.h"

class SCgInsertModeEventHandler: public SCgEventHandler
{
public:
    explicit SCgInsertModeEventHandler(SCgScene* parent);

    virtual ~SCgInsertModeEventHandler();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mousePress(QGraphicsSceneMouseEvent *event);

    void mouseMove(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    /*! @defgroup keyboardEvendHandling Keyboard Events
     *  @{
     */
    void keyPress(QKeyEvent *event);
    /*! @}*/

    //! Cleans current edit state.
    void clean();

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_InsertTemplate;
    }
};

#endif /* SCGINSERTMODEEVENTHANDLER_H_ */
