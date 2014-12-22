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
#ifndef SCGSELECTMODE_H_
#define SCGSELECTMODE_H_

#include "scgmode.h"
#include <QMap>
#include <QCursor>
#include <QPointF>
#include <scgnodetextitem.h>

class SCgPointObject;

class SCgSelectMode : public SCgMode
{
    Q_OBJECT
public:
    explicit SCgSelectMode(SCgScene* parent);

    virtual ~SCgSelectMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mousePress(QGraphicsSceneMouseEvent *event);

    void mouseMove(QGraphicsSceneMouseEvent *event);

    void mouseRelease(QGraphicsSceneMouseEvent *event);

    void mouseDoubleClick(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Select;
    }

    void clean();

protected:

private:
    //! Holds initial items positions and parents before and after moving
    SCgScene::ItemUndoInfo mUndoInfo;
    //! True if items positions have changed.
    bool mIsItemsMoved;
    //! Showed if type cloning proccess is started
    bool mIsTypeClonning;
    //! Type of object that taken part in type clonning
    int mObjectType;
    //! Cloning type alias
    QString mCloningType;
    //! Cursor for type cloning
    QCursor mCloningCursor;
    //! Currently controlled pointObject.
    SCgPointObject* mCurrentPointObject;
    //! find nearest countour according to stack order for @p item
    SCgContour *findNearestParentContour(QGraphicsItem* item);
    SCgNodeTextItem *mTextItem;
};

#endif /* SCGSCENEEVENTHANDLERS_H_ */
