/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QKeyEvent>

#include "../scgscene.h"

/*! Event handling on SCgScene depends on edit mode.
 *  This is a base class for providing different reaction for each edit mode.
 *  NOTE: Then subclass don't forget to call appropriate methods in overriding functions.
 */
class SCgMode: public QObject
{
    Q_OBJECT
public:
    explicit SCgMode(SCgScene* parent);

    virtual ~SCgMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    virtual void mouseDoubleClick(QGraphicsSceneMouseEvent *event);

    virtual void mousePress(QGraphicsSceneMouseEvent *event);

    virtual void mouseMove(QGraphicsSceneMouseEvent *event);

    virtual void mouseRelease(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    /*! @defgroup keyboardEvendHandling Keyboard Events
     *  @{
     */
    virtual void keyPress(QKeyEvent *event);
    virtual void keyRelease(QKeyEvent *event);
    /*! @}*/

    //! Cleans current edit state.
    virtual void clean()
    {
        if (mPathItem)
            endLineCreation();
    }

    //! @return edit mode corresponding to this handler
    virtual SCgScene::EditMode mode() = 0;

    //! Activate current event handler. Need to be overridden in subclasses.
    virtual void activate() {return; }

    //! Deactivate current event handler. Need to be overridden in subclasses.
    virtual void deactivate() {return; }

protected:
    //! goes through all ancestors and checks if one of them movable and selected
    static bool movableAncestorIsSelected(const QGraphicsItem* item);
    //! align last point of line such that the line has one of
    //! folowing angles: 0,45,90,135,180,225,270,315.
    static QPointF degreeAlign(const QLineF& l);

    /*! Start linear object creation
        @param point    begin point
      */
    virtual void startLineCreation(const QPointF &point);

    /*! End linear object creation
      */
    virtual void endLineCreation();

    /*! Update line path in line creation.
      */
    void updatePath();

    /*!
     * Updates a line between last point and current mouse position
     */
    virtual void updateLastLine(QPointF mousePos);

    //! Vector of line object points
    QVector<QPointF> mLinePoints;

    //! Item to draw linear objects
    QGraphicsPathItem *mPathItem;

    //! parent scene
    SCgScene* mScene;

    //! Line drawn from last point to mouse position
    QGraphicsLineItem* mLastLineItem;

    //! Pen for drawing path;
    QPen mPen;

    //! object at first line point
    SCgObject* mObjectAtFirstPoint;
private:

};

