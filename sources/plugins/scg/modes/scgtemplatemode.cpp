#include "scgtemplatemode.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgnode.h"
#include <math.h>
#include <QtDebug>

SCgTemplateMode::SCgTemplateMode(SCgScene *parent)
    :SCgMode(parent),
      ghostsetVisibleClickCount(0)

{

}

void SCgTemplateMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

        QGraphicsItem *pItem = mScene->itemAt(mousePos);

        if(!pItem)
        {
            if (event->button() == Qt::LeftButton)
            {
                 mScene->createTemplateCommand(mousePos);
                 event->accept();
            }
        }
        else if ( pItem->type() == SCgNode::Type)
        {
            SCgNode *node = static_cast<SCgNode*>(pItem);
            SCgPair *pair = 0;
            SCgPair *pair2 = 0;

            if(node->typeAlias() == "node/const/group")
            {
                node->setSelected(true);
                SCgObject::SCgObjectList connected = node->connectedObjects();
                SCgObject *c_obj = 0;
                foreach(c_obj, connected)
                {
                    if(c_obj->type() == SCgPair::Type)
                    {
                        pair = static_cast<SCgPair*>(c_obj);
                        break;
                    }
                }
                pair->setSelected(true);
                SCgNode *endPairNode = static_cast<SCgNode*>(pair->endObject());
                endPairNode->setSelected(true);
                SCgBus *bus = endPairNode->bus();
                bus->setSelected(true);
                SCgObject::SCgObjectList busConnected = bus->connectedObjects();

                    for (int index = 0; index < busConnected.size(); index++) {
                        pair2 = static_cast<SCgPair*>(busConnected.at(index));
                        pair2->setSelected(true);
                        pair2->endObject()->setSelected(true);
                        SCgObject::SCgObjectList connectedGhosts = pair2->connectedObjects();
                        foreach(SCgObject *c_obj, connectedGhosts){
                            c_obj->setSelected(true);
                            static_cast<SCgPair*>(c_obj)->beginObject()->setSelected(true);
                        }
                    }
            }
        }
}

void SCgTemplateMode::mouseMove(QGraphicsSceneMouseEvent *event)
{

}

void SCgTemplateMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton)
    {
        QGraphicsItem *pItem = mScene->itemAt(event->scenePos());

        if(mScene->itemAt(event->scenePos()) == 0)
            return;

        if(pItem->type() == SCgNode::Type && ghostsetVisibleClickCount % 2 != 0)
        {
            SCgNode *node = static_cast<SCgNode*>(pItem);
            if(node->isGhost())
            {
                node->setOpacity(1.0f);
                SCgObject::SCgObjectList connected = node->connectedObjects();
                foreach(SCgObject *c_obj, connected)
                    c_obj->setOpacity(1.0f);
                 node->setGhost(false);


            }
            else if(!node->isGhost())
            {
                node->setGhost(true);
                node->setOpacity(.25f);
                SCgObject::SCgObjectList connected = node->connectedObjects();
                foreach(SCgObject *c_obj, connected)
                    c_obj->setOpacity(.25f);
            }
        }
    }
    if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::RightButton)
    {
        QGraphicsItem *pItem = mScene->itemAt(event->scenePos());

        if(mScene->itemAt(event->scenePos()) == 0)
            return;

        if(pItem->type() == SCgPair::Type)
        {
            SCgPair *pair = static_cast<SCgPair*>(pItem);
            if(pair->beginObject()->type() == SCgBus::Type)
            {
                ghostsetVisibleClickCount++;
                SCgObject::SCgObjectList connected = pair->connectedObjects();
                foreach(SCgObject *c_obj, connected){
                    SCgPair *obj = static_cast<SCgPair*>(c_obj);
                    if(!obj->isVisible()){
                        obj->setVisible(true);
                        obj->beginObject()->setVisible(true);
                    }else if(obj->isVisible() && obj->opacity() < 1.0f){
                        obj->setVisible(false);
                        obj->beginObject()->setVisible(false);
                    }
                }

            }
        }

    }

}


void SCgTemplateMode::mouseRelease(QGraphicsSceneMouseEvent *event)
{

}

void SCgTemplateMode::keyPress(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Space)
    {
        QList<QGraphicsItem*> items = mScene->selectedItems();
        if(items.size() > 2)
            return;
        SCgObject* beginObject = static_cast<SCgObject*>(items.at(1));
        SCgObject* endObject = static_cast<SCgObject*>(items.at(0));
        QVector<QPointF> points;
        points.push_back(beginObject->pos());
        points.push_back(endObject->pos());
        SCgPair* doPair = mScene->createSCgPair(beginObject,endObject,points);

        SCgNode* roleNode = createGoToNodeAtribute(calc(beginObject->pos(),endObject->pos()));

        SCgPair* roleNodeGoToPair = mScene->createSCgPair(roleNode,doPair,points);
        roleNodeGoToPair->setEndDot(.5f);
    }

    if(event->modifiers()  == Qt::ControlModifier && event->key() == Qt::Key_E)
    {
        QList<QGraphicsItem*> items = mScene->selectedItems();
        if(items.size() > 2)
            return;
        SCgObject* beginObject = static_cast<SCgObject*>(items.at(1));
        SCgObject* endObject = static_cast<SCgObject*>(items.at(0));
        QVector<QPointF> points;
        points.push_back(beginObject->pos());
        points.push_back(endObject->pos());
        SCgPair* doPair = mScene->createSCgPair(beginObject,endObject,points);

        SCgNode* roleNode = createElseNodeAtribute(calc(beginObject->pos(),endObject->pos()));

        SCgPair* roleNodeGoToPair = mScene->createSCgPair(roleNode,doPair,points);
        roleNodeGoToPair->setEndDot(.5f);
    }
    if(event->modifiers()  == Qt::ControlModifier && event->key() == Qt::Key_T)
    {
        QList<QGraphicsItem*> items = mScene->selectedItems();
        if(items.size() > 2 && items.size() == 0)
            return;
        SCgObject* beginObject = static_cast<SCgObject*>(items.at(1));
        SCgObject* endObject = static_cast<SCgObject*>(items.at(0));
        QVector<QPointF> points;
        points.push_back(beginObject->pos());
        points.push_back(endObject->pos());
        SCgPair* doPair = mScene->createSCgPair(beginObject,endObject,points);

        SCgNode* roleNode = createThenNodeAtribute(calc(beginObject->pos(),endObject->pos()));

        SCgPair* roleNodeGoToPair = mScene->createSCgPair(roleNode,doPair,points);
        roleNodeGoToPair->setEndDot(.5f);
    }

}

SCgNode *SCgTemplateMode::createGoToNodeAtribute(const QPointF &pos)
{
    SCgNode *node = mScene->createSCgNode(pos);

    node->setIdtfValue("goto_");
    node->setIdtfPos(SCgNode::BottomLeft);
    node->setTypeAlias("node/const/role");

    return node;
}

SCgNode *SCgTemplateMode::createThenNodeAtribute(const QPointF &pos)
{
    SCgNode *node = mScene->createSCgNode(pos);

    node->setIdtfValue("then_");
    node->setIdtfPos(SCgNode::BottomLeft);
    node->setTypeAlias("node/const/role");

    return node;
}

SCgNode *SCgTemplateMode::createElseNodeAtribute(const QPointF &pos)
{
    SCgNode *node = mScene->createSCgNode(pos);

    node->setIdtfValue("else_");
    node->setIdtfPos(SCgNode::BottomLeft);
    node->setTypeAlias("node/const/role");

    return node;
}

QPointF SCgTemplateMode::calc(QPointF beginPoint, QPointF endPoint)
{
    int lenght = std::max(fabs(endPoint.x() - beginPoint.x()), fabs(endPoint.y() - beginPoint.y()));
    QPointF points((lenght / 2), endPoint.y() + 20);
    return points;
}
