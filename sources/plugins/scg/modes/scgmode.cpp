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

#include "scgmode.h"
#include "scgcontour.h"
#include "scgnode.h"

#include <QPainterPath>
#include <QGraphicsView>
#include <QVector2D>

#define KEYBOARD_SELECTION_RANGE 30.f
#define KEYBOARD_SELECTION_MAX_DISTANCE 250.f

SCgMode::SCgMode(SCgScene* parent) :
        QObject(parent),
        mPathItem(0),
        mScene(parent),
        mLastLineItem(0),
        mObjectAtFirstPoint(0)
{
    mPen.setWidthF(2.f);
    mPen.setCapStyle(Qt::RoundCap);
    mPen.setStyle(Qt::DashDotLine);
}

SCgMode::~SCgMode()
{
    clean();
}

void SCgMode::mousePress(QGraphicsSceneMouseEvent* event)
{
    event->accept();
    if (event->modifiers() == Qt::ShiftModifier && mLinePoints.size() > 0)
    {
        QLineF l(mLinePoints.last(), event->scenePos());
        event->setScenePos(degreeAlign(l));
    }
    QPointF mousePos = event->scenePos();
    if (mPathItem && event->button() == Qt::LeftButton)
    {
        mLinePoints.push_back(mousePos);
        updatePath();
        updateLastLine(mousePos);
    }
    // right button
    if (event->button() == Qt::RightButton)
    {
        if (mPathItem && !mLinePoints.empty())
        {
            mLinePoints.pop_back();
            if (mLinePoints.empty())
                endLineCreation();
            else
            {
                updatePath();
                updateLastLine(mousePos);
            }
        }
    }
}

void SCgMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{

}

QPointF SCgMode::degreeAlign(const QLineF& l)
{
    qreal a = l.angle();
    bool isOnOX = a > 360 - 22.5 || a < 22.5;
    bool isOnNegativeOX = a > 180 - 22.5 && a < 180 + 22.5;
    if ( isOnOX || isOnNegativeOX)
        return QPointF(l.x2(),l.y1());
    else
    {
        bool isOnOY = a > 45 + 22.5 && a < 90 + 22.5;
        bool isOnNegativeOY = a > 270 - 22.5 && a < 270 + 22.5;
        if ( isOnOY || isOnNegativeOY)
            return QPointF(l.x1(),l.y2());
        else
        {
            QLineF l2 = l;
            l2.setAngle(a - 45);
            l2.setP2(degreeAlign(l2));
            l2.setAngle(l2.angle()+45);
            return l2.p2();
        }
    }
}

void SCgMode::mouseMove(QGraphicsSceneMouseEvent *event)
{
    if(mLastLineItem)
    {
        if (event->modifiers() == Qt::ShiftModifier)
        {
            QLineF l(mLinePoints.last(), event->scenePos());
            event->setScenePos(degreeAlign(l));
        }
        updateLastLine(event->scenePos());
    }
}

void SCgMode::mouseRelease(QGraphicsSceneMouseEvent *event)
{

}

void SCgMode::startLineCreation(const QPointF &point)
{
    Q_ASSERT(!mPathItem);
    Q_ASSERT(!mLastLineItem);
    Q_ASSERT(!mObjectAtFirstPoint);

    mLinePoints.clear();

    //make path visible on contours
    QGraphicsItem* parent = 0;
    SCgScene::EditMode curr_mode = mode();
    mObjectAtFirstPoint = mScene->objectAt(point);
    if(mObjectAtFirstPoint)
    {
        if(mObjectAtFirstPoint->type() == SCgNode::Type || mObjectAtFirstPoint->type() == SCgContour::Type )
            mLinePoints.push_back(mObjectAtFirstPoint->scenePos());
        else
            mLinePoints.push_back(mObjectAtFirstPoint->cross(point, mObjectAtFirstPoint->dotPos(point)));

        if (curr_mode == SCgScene::Mode_Contour)
        {
            mLinePoints.first() = point;
            parent = mObjectAtFirstPoint;
        }
        else
            parent = mObjectAtFirstPoint->parentItem();
    }
    else
        mLinePoints.push_back(point);

    mLastLineItem = new QGraphicsLineItem(parent);
    mPathItem = new QGraphicsPathItem(parent);

    mPathItem->setAcceptedMouseButtons(Qt::NoButton);

    mPathItem->setPen(mPen);
    mLastLineItem->setPen(mPen);

    mScene->addItem(mPathItem);
    mScene->addItem(mLastLineItem);
}

void SCgMode::endLineCreation()
{
    delete mPathItem;
    delete mLastLineItem;
    mPathItem = 0;
    mLastLineItem = 0;
    mObjectAtFirstPoint = 0;
}

void SCgMode::updateLastLine(QPointF mousePos)
{
    Q_ASSERT(mLastLineItem);
    mLastLineItem->setPen(mPen);
    QPointF last = mLinePoints.last();

    if(mLastLineItem->parentItem())
    {
        last = mLastLineItem->parentItem()->mapFromScene(last);
        mousePos = mLastLineItem->parentItem()->mapFromScene(mousePos);
    }

    mLastLineItem->setLine(QLineF(last, mousePos));
}

void SCgMode::updatePath()
{
    Q_ASSERT(mPathItem);

    QPainterPath path;

    if (!mLinePoints.isEmpty())
    {
        path.moveTo(mLinePoints.first());
        for (int idx = 1; idx != mLinePoints.size(); ++idx)
            path.lineTo(mLinePoints[idx]);
    }

    //Draw path in parent coordinates
    if (mPathItem->parentItem())
        path = mPathItem->parentItem()->mapFromScene(path);

    mPathItem->setPen(mPen);
    mPathItem->setPath(path);
}

bool SCgMode::movableAncestorIsSelected(const QGraphicsItem *item)
{
    const QGraphicsItem *parent = item->parentItem();
    return parent && (((parent->flags() & QGraphicsItem::ItemIsMovable) && parent->isSelected()) || movableAncestorIsSelected(parent));
}

void SCgMode::keyPress(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        clean();
    }
    if (event->modifiers() == Qt::ControlModifier)
    {
        QPointF offset(0,0);
        switch(event->key())
        {
        case Qt::Key_Left:
            offset.setX(- 1);
            break;
        case Qt::Key_Right:
            offset.setX(1);
            break;
        case Qt::Key_Up:
            offset.setY(-1);
            break;
        case Qt::Key_Down:
            offset.setY(1);
            break;
        }
        SCgScene::ItemUndoInfo undoInfo;
        foreach(QGraphicsItem* item, mScene->selectedItems())
        {
            if(item->flags() & QGraphicsItem::ItemIsMovable && !movableAncestorIsSelected(item))
                undoInfo[item] = qMakePair(qMakePair(item->parentItem(), item->scenePos()), qMakePair(item->parentItem(), item->scenePos()+offset));
        }
        if(!offset.isNull() && !undoInfo.empty())
        {
            event->accept();
            mScene->moveSelectedCommand(undoInfo);
        }
    }
    else
    {
        // iterate objects with keyboard arrows
        int key = event->key();
        if (key == Qt::Key_Left || key == Qt::Key_Right || key == Qt::Key_Up || key == Qt::Key_Down)
        {
            QList<QGraphicsItem*> selItems = mScene->selectedItems();
            if (selItems.size() == 1)
            {
                QGraphicsItem *selectedItem = selItems.first();
                // work just with node and contours
                int type = selectedItem->type();
                if (type == SCgNode::Type || type == SCgContour::Type)
                {
                    QList<QGraphicsItem*> items = mScene->items();
                    QGraphicsItem *it, *nextSelection = 0;
                    qreal min_dist = -1.f;
                    foreach(it, items)
                    {
                        // skip objects that aren't nodes or contours
                        if (it->type() != SCgNode::Type && it->type() != SCgContour::Type)
                            continue;

                        // skip selected item
                        if (it == selectedItem)
                            continue;

                        QVector2D dv(it->pos() - selectedItem->pos());

                        // check if object in possible ranges
                        if ((key == Qt::Key_Left || key == Qt::Key_Right) && (qAbs(dv.y()) > KEYBOARD_SELECTION_RANGE))
                            continue;
                        if ((key == Qt::Key_Up || key == Qt::Key_Down) && (qAbs(dv.x()) > KEYBOARD_SELECTION_RANGE))
                            continue;


                        switch(key)
                        {
                        case Qt::Key_Left:
                            dv *= QVector2D(-1.f, 0.f);
                            break;
                        case Qt::Key_Up:
                            dv *= QVector2D(0.f, -1.f);
                            break;
                        case Qt::Key_Right:
                            dv *= QVector2D(1.f, 0.f);
                            break;
                        case Qt::Key_Down:
                            dv *= QVector2D(0.f, 1.f);
                            break;
                        }

                        // check if object in selected direction
                        if (dv.x() + dv.y() < 0)
                            continue;

                        // calculate distance and check if it has minimum distance
                        qreal dist = dv.length();
                        if (dist > KEYBOARD_SELECTION_MAX_DISTANCE)
                            continue;

                        if (min_dist < 0 || min_dist > dist)
                        {
                            min_dist = dist;
                            nextSelection = it;
                        }
                    }

                    // set selection
                    if (nextSelection != 0)
                    {
                        selectedItem->setSelected(false);
                        nextSelection->setSelected(true);
                        nextSelection->ensureVisible();
                    }
                }
            }
        } // if (key == Qt::Key_Left ...
    }
}

void SCgMode::keyRelease(QKeyEvent *event)
{

}
