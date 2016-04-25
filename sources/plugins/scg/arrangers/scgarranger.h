/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QMap>
#include <QDialog>
#include <QSet>
#include "../scgscene.h"

class SCgView;
class SCgObject;
class QGraphicsItem;
class SCgBaseCommand;

/*! To create new arranger you should implement 4 functions:
 *   bool configDialog();
 *   void startOperation();
 *   int type();
 *   QString name();
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

    //! Return arranger name
    virtual QString name() const = 0;

    //! Command for changing node position.
    void registerCommand(SCgObject* obj, const QPointF& newPos);

    //! Command for changing pointObject points.
    void registerCommand(SCgPointObject* obj, const QVector<QPointF>& newPoints);

    //! Command for removing all break points of pairs.
    void registerCommandRemoveBreakPoints(SCgPair *pair);

    //! Command for minimizing contour.
    void registerCommandMinimizeContour(SCgContour *contour);

    //! Deletes all ghosts from scene.
    void deleteGhosts();

    /*! Creates ghosts of objects for current list(@p list).
    @see createGhost()*/
    void createGhosts(const QList<QGraphicsItem*>& list);

    //! Holds view items on will be arranged.
    SCgView* mView;

    //! Holds ghost items <RealObject, Ghost>
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

