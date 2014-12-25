#include "scgfivemode.h"
#include "scgcontour.h"
#include "commands/scgcommandchangeincedentobject.h"
#include "scgpair.h"
#include "scgpointobject.h"

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
