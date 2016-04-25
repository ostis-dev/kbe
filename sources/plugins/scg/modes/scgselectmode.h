/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgmode.h"
#include <QMap>
#include <QCursor>

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

};

