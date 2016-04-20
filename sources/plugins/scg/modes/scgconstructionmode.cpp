#include "scgconstructionmode.h"
#include "scgcontour.h"
#include "scgwindow.h"
#include "scgnode.h"
#include "scgpair.h"

#include <QGraphicsView>
#include <QApplication>


SCgConstructionMode::SCgConstructionMode(SCgScene* parent, ConstructionType type):
    SCgMode(parent),
    mConstruction(0)
{
    this->type = type;
}

SCgConstructionMode::~SCgConstructionMode()
{
    clean();
}

SCgScene::EditMode SCgConstructionMode::mode()
{
    if(type == SCgConstructionMode::Type_3elements)
    {
        return SCgScene::Mode_3elementConstruction;
    }
    else
    {
       return SCgScene::Mode_5elementConstruction;
    }
}

void SCgConstructionMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgMode::mousePress(event);
    if (mConstruction)
    {
        SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
        SCgContour* parent = 0;
        if (underMouseObj && underMouseObj->type() == SCgContour::Type)
            parent = static_cast<SCgContour*>(underMouseObj);
        mScene->pasteCommand(mConstruction->childItems(), parent);
    }
    else
        mScene->setEditMode(mScene->previousMode());
    clean();
}

void SCgConstructionMode::mouseMove(QGraphicsSceneMouseEvent *event)
{
    SCgMode::mouseMove(event);
    if (mConstruction)
    {
        mConstruction->setPos(event->scenePos());
    }
}

void SCgConstructionMode::keyPress(QKeyEvent *event)
{
    SCgMode::keyPress(event);
    if(event->key() == Qt::Key_Escape)
    {
        clean();
        mScene->setEditMode(SCgScene::Mode_Select);
        event->accept();
    }
}

void SCgConstructionMode::clean()
{
    SCgMode::clean();
    if (mConstruction)
    {
        delete mConstruction;
        mConstruction = 0;
    }
}

void SCgConstructionMode::activate()
{
    if (mConstruction)
    {
        delete mConstruction;
        mConstruction = 0;
    }
    QList<QGraphicsItem*> items;

    QGraphicsView* v = mScene->views().at(0);
    QPointF p = v->mapToScene(v->mapFromGlobal(QCursor::pos()));

    SCgNode * firstNode = mScene->createSCgNode(QPointF(0, 0));
    SCgNode * secondNode = mScene->createSCgNode(QPointF(100, 0));

    QVector<QPointF> mFirsLinePoints;
    mFirsLinePoints.append(firstNode->scenePos());
    mFirsLinePoints.append(secondNode->scenePos());

    SCgPair * firstPair = mScene->createSCgPair(firstNode, secondNode, mFirsLinePoints);

    items.append(firstNode);
    items.append(secondNode);
    items.append(firstPair);

    if(type == SCgConstructionMode::Type_5elements) {
        SCgNode * thirdNode = mScene->createSCgNode(QPointF(50, -50));

        QVector<QPointF> mSecondLinePoints;
        mSecondLinePoints.append(thirdNode->scenePos());
        mSecondLinePoints.append(QPointF(50, 0));

        SCgPair * secondPair = mScene->createSCgPair(thirdNode, firstPair, mSecondLinePoints);

        items.append(thirdNode);
        items.append(secondPair);
    }

    mConstruction = mScene->createItemGroup(items);

    mConstruction->setPos(p);
    mConstruction->setOpacity(0.5);
}

void SCgConstructionMode::deactivate()
{
    clean();
}
