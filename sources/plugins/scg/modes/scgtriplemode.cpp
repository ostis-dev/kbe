#include "scgtriplemode.h"
#include "scgcontour.h"
#include "commands/scgcommandchangeincedentobject.h"
#include "scgpair.h"
#include "scgpointobject.h"

SCgTripleMode::SCgTripleMode(SCgScene* parent):SCgMode(parent)
{
 mPen.setColor(Qt::red);
}

SCgTripleMode::~SCgTripleMode()
{
 clean();
}

void SCgTripleMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
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

 event->accept();
 }


}
