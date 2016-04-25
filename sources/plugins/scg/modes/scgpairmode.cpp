/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgpairmode.h"
#include "scgcontour.h"

SCgPairMode::SCgPairMode(SCgScene* parent):SCgMode(parent)
{
    mPen.setColor(Qt::red);
}

SCgPairMode::~SCgPairMode()
{
    clean();
}

void SCgPairMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgMode::mousePress(event);
    if (event->button() == Qt::LeftButton)
    {
        QPointF mousePos = event->scenePos();

        SCgObject *obj = mScene->objectAt(mousePos);
        // if we not create pair yet and press on scg-object, then
        // start pair creation
        if (obj && !mPathItem)
            startLineCreation(mousePos);
        else
        if (obj && obj != mPathItem->parentItem())
        {
            SCgObject *begObj = mObjectAtFirstPoint;
            SCgObject *endObj = obj;

            // do not create lines with equivalent begin end end object
            if (begObj != endObj && begObj && !begObj->isDead())
            {
                SCgContour* c=0;
                // get parent contour
                QGraphicsItem* parent = begObj->parentItem();
                if(parent && parent == endObj->parentItem())
                    if (parent->type() == SCgContour::Type)
                        c = static_cast<SCgContour*>(parent);

                mScene->createPairCommand(mLinePoints, begObj, endObj, c);
            }

            endLineCreation();
        } // if (obj)
    }
}

void SCgPairMode::mouseMove(QGraphicsSceneMouseEvent *event)
{
    Qt::PenStyle s;

    if(mPathItem)
    {
        SCgObject *begObj = mObjectAtFirstPoint;
        SCgObject *endObj = mScene->objectAt(event->scenePos());
        if (endObj != begObj && endObj && begObj && endObj != mPathItem->parentItem())
            s = Qt::SolidLine;
        else
            s = Qt::DashDotLine;

        if(s != mPen.style())
        {
            mPen.setStyle(s);
            updatePath();
        }
    }
    SCgMode::mouseMove(event);
}

