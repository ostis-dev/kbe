/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2012 OSTIS

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
