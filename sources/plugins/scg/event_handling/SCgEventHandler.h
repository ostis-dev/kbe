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

#ifndef SCGEVENTHANDLER_H_
#define SCGEVENTHANDLER_H_

#include <QObject>
#include <QKeyEvent>

#include "../scgscene.h"

/*! Event handling on SCgScene depends on edit mode.
 *  This is a base class for providing different reaction for each edit mode.
 *  NOTE: Then subclass don't forget to call appropriate methods in overriding functions.
 */
class SCgEventHandler: public QObject
{
    Q_OBJECT
public:
    explicit SCgEventHandler(SCgScene* parent);

    virtual ~SCgEventHandler();

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

#endif /* SCGEVENTHANDLER_H_ */
