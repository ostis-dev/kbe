/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef SCGBUSMODE_H_
#define SCGBUSMODE_H_

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
    void mousePress(QGraphicsSceneMouseEvent *event);
    void mouseMove(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Bus;
    }

protected:


};

#endif /* SCGBUSMODEEVENTHANDLER_H_ */
