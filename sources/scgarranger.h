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

#ifndef SCGOBJECTARRANGERS_H_
#define SCGOBJECTARRANGERS_H_

#include <QObject>
#include <QMap>
#include <QDialog>
#include <QSet>
#include "scgscene.h"

class SCgView;
class SCgObject;
class QGraphicsItem;
class SCgBaseCommand;

/*! To create new arranger you should implement 3 functions:
 *   bool userMenu();
 *   void startOperation();
 *   int type();
 *  If you won't use the menu then userMenu should return true.
 *  NOTE: If You want use undo/redo commands you should change objects position by calling corresponding functions:
 *  registerCommand(SCgObject*, const QPointF&);
 *  registerCommand(SCgObject*, const QVector<QPointF>&);
 *  If You use these functions, you MUSTN'T change objects! (These functions take objects state as initial).
 *  All finish positions must be in coordinates that acceptable by default changing functions.
 *  e.g. in parent coordinates for nodes and in it's local coordinates for pointed objects.
 */
class SCgArranger : public QObject
{
Q_OBJECT

public:
    explicit SCgArranger(QObject *parent = 0);
    virtual ~SCgArranger();

    //! Arranges items in specified view @p view.
    void arrange(SCgView* view);

    //! @return type of this arranger.
    virtual int type() const = 0;
protected:

    //! Shows menu to user and returns true, if user agree with changes.
    virtual bool configDialog() = 0;

    //! Start arrange process.
    virtual void startOperation() = 0;

    //! Command for changing node position.
    void registerCommand(SCgObject* obj, const QPointF& newPos);
    //! Command for changing pointObject points.
    void registerCommand(SCgPointObject* obj, const QVector<QPointF>& newPoints);

    //! Deletes all ghosts from scene.
    void deleteGhosts();

    /*! Creates ghosts of objects for current list(@p list).
    @see createGhost()*/
    void createGhosts(const QList<QGraphicsItem*>& list);

    //! Holds view items on will be arranged.
    SCgView* mView;

    //! Holds ghost items
    QMap<SCgObject*, SCgObject*> mGhosts;

private:
    SCgScene* mScene;
    //! Parent command for all changes on scene;
    SCgBaseCommand* mParentCommand;
    /*! Creates ghost for specified object (@p obj).
    * Note: the isDead flag will be set.
    * @p opacityLevel - opacity value for top level items.
    **/
    SCgObject* createGhost(SCgObject* obj, qreal opacityLevel = 0.4);
};

#endif /* SCGOBJECTARRANGERS_H_ */
