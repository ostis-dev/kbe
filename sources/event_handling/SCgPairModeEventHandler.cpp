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


#include "SCgPairModeEventHandler.h"
#include "scgcontour.h"

SCgPairModeEventHandler::SCgPairModeEventHandler(SCgScene* parent):SCgEventHandler(parent)
{
    mPen.setColor(Qt::red);
}

SCgPairModeEventHandler::~SCgPairModeEventHandler()
{
    clean();
}

void SCgPairModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mousePress(event);
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

void SCgPairModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event)
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
    SCgEventHandler::mouseMove(event);
}

