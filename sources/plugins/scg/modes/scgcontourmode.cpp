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
#include "scgcontourmode.h"
#include "scgcontour.h"

#include <QVector2D>

SCgContourMode::SCgContourMode(SCgScene* parent):SCgMode(parent),mClosingSubpathLine(0)
{
    mPen.setColor(Qt::green);
}

SCgContourMode::~SCgContourMode()
{
    clean();
}

void SCgContourMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

       QPointF mousePos = event->scenePos();

        if (!mPathItem)
        {
            startLineCreation(mousePos);
            return;
        }else
        {
            QVector2D vec(mLinePoints.first() - mousePos);
            if (vec.length() < 5.f && mLinePoints.size() > 2)
            {
                SCgContour* c = 0;
                // get parent contour
                if(mPathItem->parentItem() && mPathItem->parentItem()->type() == SCgContour::Type)
                    c = static_cast<SCgContour*>(mPathItem->parentItem());

                // get child items
                QList<QGraphicsItem*> childs = selectItemsForContour();

                mScene->createContourCommand(childs, mLinePoints, c);
                endLineCreation();
            }
        }
    }

    SCgMode::mousePress(event);
}

QList<QGraphicsItem* > SCgContourMode::selectItemsForContour() const
{
    QList<QGraphicsItem* > result;
    foreach(QGraphicsItem* it, mScene->items())
    {
        bool isWithinPath = it->collidesWithPath( it->mapFromParent(mPathItem->path()), Qt::ContainsItemShape);
        bool hasSameParent = it->parentItem() == mPathItem->parentItem();

        if (isWithinPath && hasSameParent)
            result.append(it);
    }

    return result;
}

void SCgContourMode::mouseMove(QGraphicsSceneMouseEvent *event)
{
    if(mPathItem)
    {
        Qt::PenStyle s;

        QVector2D vec(event->scenePos() - mLinePoints.first());

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

    SCgMode::mouseMove(event);
}


void SCgContourMode::startLineCreation(const QPointF &point)
{
    Q_ASSERT(!mClosingSubpathLine);

    SCgMode::startLineCreation(point);
    mClosingSubpathLine = new QGraphicsLineItem(mPathItem->parentItem());

    mClosingSubpathLine->setPen(mPen);
    mScene->addItem(mClosingSubpathLine);
}


void SCgContourMode::endLineCreation()
{
    SCgMode::endLineCreation();
    delete mClosingSubpathLine;
    mClosingSubpathLine = 0;
}


void SCgContourMode::updateLastLine(QPointF mousePos)
{
    SCgMode::updateLastLine(mousePos);
    mClosingSubpathLine->setPen(mPen);
    QPointF first = mLinePoints.first();

    if(mLastLineItem->parentItem())
    {
        first = mLastLineItem->parentItem()->mapFromScene(first);
        mousePos = mLastLineItem->parentItem()->mapFromScene(mousePos);
    }

    mClosingSubpathLine->setLine(QLineF(first, mousePos));
}
