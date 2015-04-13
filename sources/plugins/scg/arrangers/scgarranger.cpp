/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgarranger.h"

#include "scgview.h"
#include "scgobject.h"
#include "scgpair.h"
#include "scgnode.h"
#include "scgcontour.h"
#include "scgbus.h"

#include <QDialogButtonBox>
#include <QApplication>
#include <QMessageBox>
#include <QSpinBox>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>

SCgArranger::SCgArranger(QObject *parent) :
    QObject(parent),
    mView(0)
{
}

SCgArranger::~SCgArranger()
{
}


void SCgArranger::arrange(SCgView* view)
{
    if(!view)
        return;

    mParentCommand = new SCgBaseCommand(0, 0, 0);
    mParentCommand->setText(name());

    mView = view;
    mScene = static_cast<SCgScene*>(mView->scene());
    if(configDialog())
    {
        startOperation();
        mScene->addCommandToStack(mParentCommand);
    }
}

void SCgArranger::registerCommand(SCgObject* obj, const QPointF& newPos)
{
    if(!mParentCommand)
        mParentCommand = mScene->changeObjectPositionCommand(obj, newPos, 0, false);
    else
        mScene->changeObjectPositionCommand(obj, newPos, mParentCommand, false);
}

void SCgArranger::registerCommand(SCgPointObject* obj, const QVector<QPointF>& newPoints)
{

    if(!mParentCommand)
        mParentCommand = mScene->changeObjectPointsCommand(obj, newPoints, 0, false);
    else
        mScene->changeObjectPointsCommand(obj, newPoints, mParentCommand, false);
}

void SCgArranger::registerCommandRemoveBreakPoints(SCgPair *pair)
{
    if (!mParentCommand) {
        mParentCommand = mScene->removeBreakPointsCommand(pair, 0, false);
    } else {
        mScene->removeBreakPointsCommand(pair, mParentCommand, false);
    }
}

void SCgArranger::registerCommandMinimizeContour(SCgContour *contour)
{
    if (!mParentCommand) {
        mParentCommand = mScene->minimizeContourCommand(contour, 0, false);
    } else {
        mScene->minimizeContourCommand(contour, mParentCommand, false);
    }
}

SCgObject* SCgArranger::createGhost(SCgObject* obj, qreal opacityLevel)
{
    if(!obj)
        return 0;

    SCgObject* ghost = 0;
    SCgScene* s = static_cast<SCgScene*>(mView->scene());

    if(mGhosts.contains(obj))
        return mGhosts.value(obj);
    //Creating object
    switch(obj->type())
    {
    case SCgNode::Type:
        ghost = s->createSCgNode(obj->scenePos());
        ghost->setTypeAlias(obj->typeAlias());
        break;
    case SCgPair::Type:
    {
        SCgPair* p = static_cast<SCgPair*>(obj);
        SCgObject* begGhost = createGhost(p->beginObject());
        SCgObject* endGhost = createGhost(p->endObject());
        ghost = s->createSCgPair(begGhost, endGhost, p->points());
        ghost->setTypeAlias(obj->typeAlias());
        break;
    }
    case SCgBus::Type:
    {
        SCgBus* b = static_cast<SCgBus*>(obj);
        SCgNode* ownerGhost = static_cast<SCgNode*>(createGhost(b->owner()));
        ghost = s->createSCgBus(b->points(), ownerGhost);
        break;
    }
    case SCgContour::Type:
    {
        SCgContour* c = static_cast<SCgContour*>(obj);
        ghost = s->createSCgContour(c->scenePoints());
        break;
    }
    default:
        return 0;
    }

    mGhosts[obj] = ghost;

    ghost->setZValue(ghost->zValue()+0.5);
    ghost->setDead(true);

    //Setting parent object
    SCgObject* parentGhost = 0;
    if(obj->parentItem() && SCgObject::isSCgObjectType(obj->parentItem()->type()))
        parentGhost = createGhost(static_cast<SCgObject*>(obj->parentItem()));
    else
        ghost->setOpacity(opacityLevel);// Set opacity only for top level items(cause of inheriting parameters)

    ghost->setParentItem(parentGhost);

    return ghost;
}


void SCgArranger::deleteGhosts()
{
    QMap<SCgObject*, SCgObject*>::const_iterator i = mGhosts.constBegin();
    for (;i != mGhosts.constEnd();++i)
        i.value()->setParentItem(0);
    for (i = mGhosts.begin();i != mGhosts.constEnd(); ++i)
        delete i.value();

    mGhosts.clear();
}

void SCgArranger::createGhosts(const QList<QGraphicsItem*>& list)
{
    foreach(QGraphicsItem* it, list)
        if (it->opacity() == 1 && SCgObject::isSCgObjectType(it->type()))
            createGhost(static_cast<SCgObject*>(it));
}
