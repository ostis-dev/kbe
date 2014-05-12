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


#include "scgfivemode.h"
#include "scgcontour.h"
#include "commands/scgcommandchangeincedentobject.h"
#include "scgpair.h"

SCgFiveMode::SCgFiveMode(SCgScene* parent):SCgMode(parent)
{
    mPen.setColor(Qt::red);
}

SCgFiveMode::~SCgFiveMode()
{
    clean();
}

void SCgFiveMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF mousePos = event->scenePos();
        QPointF positionSecNode(mousePos.x() + 100,mousePos.y());

        SCgContour *contour = 0;
        mScene->createNodeCommand(mousePos, contour);
        mScene->createNodeCommand(positionSecNode, contour);

        SCgObject *begObj = mScene->objectAt(mousePos);
        SCgObject *endObj = mScene->objectAt(positionSecNode);

        mScene->createPairCommand(mLinePoints, begObj, endObj, contour);
        QPointF positionThirdNode((mousePos.x()+positionSecNode.x()) / 2,mousePos.y()-50);
        mScene->createNodeCommand(positionThirdNode,contour);
        begObj = mScene->objectAt(positionThirdNode);

        QPointF positionArc((mousePos.x()+positionSecNode.x()) / 2,mousePos.y());
        endObj = mScene->objectAt(positionArc);

        mScene->createPairCommand(mLinePoints,begObj,endObj,contour);

         QPointF positionArc2((mousePos.x()+positionThirdNode.x()) / 2,
                     (mousePos.y()+positionThirdNode.y()) / 2);
         SCgObject* arc2 = mScene->objectAt(positionArc2);
         SCgPair *pair = dynamic_cast<SCgPair*>(arc2);
         pair->changePointPosition(1,positionArc);
         event->accept();
    }


}



