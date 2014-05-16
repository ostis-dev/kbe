#include "scgtemplatemode.h"
#include "scgtemplate.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgnode.h"
#include <QCursor>
#include <math.h>
#include <QtDebug>
#include <qcoreevent.h>
#include <QGraphicsView>
#include <QObject>

SCgTemplateMode::SCgTemplateMode(SCgScene *parent)
    :SCgMode(parent),
      ghostsetVisibleClickCount(0)

{
     mInsertedObjectGroup=0;
    connect(mScene, SIGNAL(templateChanged(SCgScene::Template)), this, SLOT(onTemplateChanged(SCgScene::Template)));
}


void SCgTemplateMode::onTemplateChanged(SCgScene::Template templ )
{
    QPointF pos = QPointF(0,0);

    if (mInsertedObjectGroup)
    {
        delete mInsertedObjectGroup;
        mInsertedObjectGroup = 0;
    }
    QVector<SCgObject*> objVector = switchTemplate(templ);
    QList<QGraphicsItem*> withoutChilds;

    foreach(SCgObject* obj, objVector)
          if (!obj->parentItem())
               withoutChilds.append(obj);

    if(!withoutChilds.empty())
    {
        mInsertedObjectGroup = mScene->createItemGroup(withoutChilds);
        QGraphicsView* v = mScene->views().at(0);
        QPointF p = v->mapToScene(v->mapFromGlobal(QCursor::pos()));
        mInsertedObjectGroup->setPos(p);
        mInsertedObjectGroup->setOpacity(0.5);
    }
    else mScene->setEditMode(mScene->previousMode());
}



QVector<SCgObject*> SCgTemplateMode::switchTemplate(SCgScene::Template templ)
{
     QPointF pos = QPointF(0,0);
     QVector<SCgObject*> result =  QVector<SCgObject*>();
     SCgTemplate templates = SCgTemplate(mScene);

     switch(templ){
     case SCgScene::GenEl_Template:
         result = templates.createGenElTemplate(pos);
         break;
     case SCgScene::GenElStr3_Template:
         result = templates.createGenElStr3Template(pos);
         break;
     case SCgScene::GenElStr5_Template:
         result = templates.createGenElStr5Template(pos);
         break;
     case SCgScene::SearchElStr3_Template:
         result = templates.createSearchElStr3Template(pos);
         break;
     case SCgScene::SearchElStr5_Template:
         result = templates.createSearchElStr5Template(pos);
         break;
     case SCgScene::SearchSetStr3_Template:
         result = templates.createSearchSetStr3Template(pos);
         break;
     case SCgScene::SearchSetStr5_Template:
         result = templates.createSearchSetStr5Template(pos);
         break;
     case SCgScene::eraseEl_Template:
         result = templates.createEraseElTemplate(pos);
         break;
     case SCgScene::eraseElStr3_Template:
         result = templates.createEraseElStr3Template(pos);
         break;
     case SCgScene::eraseElStr5_Template:
         result = templates.createEraseElStr5Template(pos);
         break;
     case SCgScene::PrintEl_Template:
         result = templates.createPrintElTemplate(pos);
         break;
     case SCgScene::PrintNl_Template:
         result = templates.createPrintNlTemplate(pos);
         break;
     case SCgScene::Print_Template:
         result = templates.createPrintTemplate(pos);
         break;
     case SCgScene::IfType_Template:
         result = templates.createifTypeTemplate(pos);
         break;
     case SCgScene::IfEqType_Template:
         result = templates.createifEqTemplate(pos);
         break;
     case SCgScene::IfCoinType_Template:
         result = templates.createifCoinTemplate(pos);
         break;
     case SCgScene::IfGrType_Template:
         result = templates.createifGrTemplate(pos);
         break;
     case SCgScene::Add_Template:
         result = templates.createAddTemplate(pos);
         break;
     case SCgScene::Sub_Template:
         result = templates.createSubTemplate(pos);
         break;
     case SCgScene::Mult_Template:
         result = templates.createMultTemplate(pos);
         break;
     case SCgScene::Div_Template:
         result = templates.createDivTemplate(pos);
         break;
     case SCgScene::Pow_Template:
         result = templates.createPowTemplate(pos);
         break;
     case SCgScene::CallReturn_Template:
         result = templates.createCallReturnTemplate(pos);
         break;
     case SCgScene::Return_Template:
         result = templates.createReturnTemplate(pos);
         break;
     default : break;
     }
     return result;
}
void SCgTemplateMode::activate(){

}

void SCgTemplateMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
        QPointF mousePos = event->scenePos();
        QGraphicsItem *pItem = mScene->itemAt(mousePos);
        if(pItem!=0)
        if(mInsertedObjectGroup)
        {
            if (event->button() == Qt::LeftButton)
            {
                delete mInsertedObjectGroup;
                mInsertedObjectGroup = 0;

                mScene->createTemplateCommand(mousePos);
                event->accept();
                mScene->setEditMode(mScene->previousMode());
            }
        }
        else if (event->button() == Qt::RightButton && pItem->type() == SCgNode::Type )
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
    SCgMode::mouseMove(event);
    if (mInsertedObjectGroup)
        mInsertedObjectGroup->setPos(event->scenePos());

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
        QVector<QGraphicsItem*> nodes;
        nodes.append(items.at(1));
        nodes.append(items.at(0));

        mScene->createGotoTemplateCommand(nodes);
    }

    //else done
    if(event->modifiers()  == Qt::ControlModifier && event->key() == Qt::Key_E)
    {
        QList<QGraphicsItem*> items = mScene->selectedItems();
        if(items.size() > 2)
            return;

        QVector<QGraphicsItem*> nodes;
        nodes.append(items.at(1));
        nodes.append(items.at(0));

        mScene->createElseTemplateCommand(nodes);

    }
    if(event->modifiers()  == Qt::ControlModifier && event->key() == Qt::Key_T)
    {
        QList<QGraphicsItem*> items = mScene->selectedItems();
        if(items.size() > 2 && items.size() == 0)
            return;
        QVector<QGraphicsItem*> nodes;
        nodes.append(items.at(1));
        nodes.append(items.at(0));

        mScene->createThenTemplateCommand(nodes);
    }


     if(event->key() == Qt::Key_Escape && mInsertedObjectGroup)
     {
             delete mInsertedObjectGroup;
             mInsertedObjectGroup = 0;
             mScene->setEditMode(mScene->previousMode());
     }
}


