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

#include "SCgBusModeEventHandler.h"
#include "scgcontour.h"
#include "scgnode.h"

#include <QMessageBox>
#include <QVector2D>
#include <QApplication>

SCgBusModeEventHandler::SCgBusModeEventHandler(SCgScene* parent):SCgEventHandler(parent)
{
    mPen.setColor(Qt::blue);
    mPen.setWidthF(5.f);
}

SCgBusModeEventHandler::~SCgBusModeEventHandler()
{
    clean();
}

void SCgBusModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mousePress(event);
    if (event->button() == Qt::LeftButton)
    {
        QPointF mousePos = event->scenePos();

        if (!mPathItem)
        {
            SCgObject *obj = mScene->objectAt(mousePos);
            SCgNode *owner = (obj != 0 && obj->type() == SCgNode::Type) ? static_cast<SCgNode*>(obj) : 0;

            if (owner != 0 && owner->bus())
                QMessageBox::information(0, qAppName(), tr("Node can't have more than one bus!"));
            else
                if(owner)
                    startLineCreation(mousePos);

        }else
        {
            QVector2D vec(*(mLinePoints.end() - 2) - mousePos);
            Q_ASSERT(mObjectAtFirstPoint);
            if (mLinePoints.size() > 2 && vec.length() < 5.f && !mObjectAtFirstPoint->isDead())
            {
                mLinePoints.pop_back();

                SCgContour* contour = 0;
                // get parent contour
                QGraphicsItem* parent = mObjectAtFirstPoint->parentItem();

                if (parent && parent->type() == SCgContour::Type)
                    contour = static_cast<SCgContour*>(parent);

                SCgNode *owner = static_cast<SCgNode*>(mObjectAtFirstPoint);
                mScene->createBusCommand(owner, mLinePoints, contour);
                endLineCreation();
            }
        }
    }
}

void SCgBusModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event)
{
    if(mPathItem)
    {
        QVector2D vec(event->scenePos() - mLinePoints.last());
        Qt::PenStyle s;

        if (vec.length() < 5.f)
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


