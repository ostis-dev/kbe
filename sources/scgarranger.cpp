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

#include "scgarranger.h"

#include "scgcommands.h"
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

    mParentCommand = 0;

    mView = view;
    mScene = static_cast<SCgScene*>(mView->scene());
    if(userMenu())
    {
        startOperation();
        if(mParentCommand)
        {
        	mParentCommand->setText(tr("Arrange objects"));
        	mScene->addCommandToStack(mParentCommand);
        }
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
        SCgObject* begGhost = createGhost(p->getBeginObject());
        SCgObject* endGhost = createGhost(p->getEndObject());
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

//_______________________________________________________________//
SCgVerticalArranger::SCgVerticalArranger(QObject *parent) :
    SCgArranger(parent)
{
}

SCgVerticalArranger::~SCgVerticalArranger()
{
}

bool SCgVerticalArranger::userMenu()
{
    return true;
}

void SCgVerticalArranger::startOperation()
{
    QList<SCgObject*> objects;
    foreach(QGraphicsItem* it, mView->scene()->selectedItems())
        if(SCgObject::isSCgObjectType(it->type()) && it->type() != SCgPair::Type)
            objects.append(static_cast<SCgObject*>(it));

    if(objects.isEmpty() || objects.size() == 1)
    {
    	QMessageBox::information(0, qAppName(), tr("Nothing to align. Did you forget to select objects for alignment?"));
    	return;
    }

    QList<SCgObject*>::const_iterator it;
    double averageX = 0;

    // Calculate average X coordinate
    for (it = objects.begin(); it != objects.end(); ++it)
        averageX += (*it)->x();
    averageX = averageX/objects.size();

    // Set objects position
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it)->type() == SCgBus::Type)
        {
            SCgBus* b = static_cast<SCgBus*>(*it);
            QVector<QPointF> points = b->mapToParent(b->points());

            for(int i = 0; i < points.size(); ++i)
                points[i].setX(averageX);

            registerCommand(b,  b->mapFromParent(points));
        }else
        {
            QPointF p = (*it)->pos();
            p.setX(averageX);
            registerCommand(*it, p);
        }
    }
}

//_______________________________________________________________//
SCgHorizontalArranger::SCgHorizontalArranger(QObject *parent) :
    SCgArranger(parent)
{
}

SCgHorizontalArranger::~SCgHorizontalArranger()
{
}

bool SCgHorizontalArranger::userMenu()
{
    return true;
}

void SCgHorizontalArranger::startOperation()
{
    QList<SCgObject*> objects;
    foreach(QGraphicsItem* it, mView->scene()->selectedItems())
        if(SCgObject::isSCgObjectType(it->type()) && it->type() != SCgPair::Type)
            objects.append(static_cast<SCgObject*>(it));

    if(objects.isEmpty() || objects.size() == 1)
    {
    	QMessageBox::information(0, qAppName(), tr("Nothing to align. Did you forget to select objects for alignment?"));
    	return;
    }

    QList<SCgObject*>::const_iterator it;
    double averageY = 0;

    // Calculate average Y coordinate
    for (it = objects.begin(); it != objects.end(); ++it)
       averageY += (*it)->y();
    averageY = averageY/objects.size();

    // Set objects position
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it)->type() == SCgBus::Type)
        {
            SCgBus* b = static_cast<SCgBus*>(*it);
            QVector<QPointF> points = b->mapToParent(b->points());

            for(int i = 0; i < points.size(); ++i)
                points[i].setY(averageY);

            registerCommand(b,  b->mapFromParent(points));
        }else
        {
            QPointF p = (*it)->pos();
            p.setY(averageY);
            registerCommand(*it, p);
        }
    }
}

//_______________________________________________________________//
SCgGridArranger::SCgGridArranger(QObject *parent):
    SCgArranger(parent),
    mDialog(0),
    mXStep(15),
    mYStep(15),
    mIsSymmetrical(true),
    mXSpinBox(0),
    mYSpinBox(0),
    mGridColor(QColor(191, 100, 150, 150))
{

}

SCgGridArranger::~SCgGridArranger()
{

}

bool SCgGridArranger::userMenu()
{
    if(!mDialog)
            createDialog();
    mDialog->setParent(mView->viewport(), Qt::Dialog);

    // Create ghost only for visible objects
    QList<QGraphicsItem*> items = mView->items(QRect(0,0,mView->width(), mView->height()));
    createGhosts(items);

    recalculateGhostsPosition();

    bool res = mDialog->exec() == QDialog::Accepted;

    deleteGhosts();
    mPlaced.clear();
    drawGrid(false);

    mDialog->setParent(0, Qt::Dialog);

    return res;
}

void SCgGridArranger::xValueChanged(int newSpacing)
{
    mXStep = newSpacing;
    if(mIsSymmetrical && mYStep != mXStep)
        mYSpinBox->setValue(newSpacing);
    else
        recalculateGhostsPosition();
}

void SCgGridArranger::yValueChanged(int newSpacing)
{
    mYStep = newSpacing;
    if(mIsSymmetrical && mYStep != mXStep)
        mXSpinBox->setValue(newSpacing);
    else
        recalculateGhostsPosition();
}

void SCgGridArranger::symmetricalCheckBoxClicked(bool checked)
{
    if(checked)
        mYSpinBox->setValue(mXSpinBox->value());

    mIsSymmetrical = checked;
}

QDialog* SCgGridArranger::createDialog()
{
    mDialog = new QDialog();
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    buttonBox->setParent(mDialog);

    QSpinBox* xSpin = new QSpinBox(mDialog);
    QSpinBox* ySpin = new QSpinBox(mDialog);

    QLabel* xLabel= new QLabel(tr("X axis step"),mDialog);
    QLabel* yLabel= new QLabel(tr("Y axis step"),mDialog);

    xSpin->setToolTip(tr("X axis step"));
    xSpin->setMinimum(15);
    xSpin->setMaximum(200);
    xSpin->setValue(mXStep);
    ySpin->setToolTip(tr("Y axis step"));
    ySpin->setMinimum(15);
    ySpin->setMaximum(200);
    ySpin->setValue(mYStep);
    mXSpinBox = xSpin;
    mYSpinBox = ySpin;

    QHBoxLayout *hl = new QHBoxLayout();

    QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(xLabel);
    vl->addWidget(xSpin);
    hl->addLayout(vl);

    vl = new QVBoxLayout();
    vl->addWidget(yLabel);
    vl->addWidget(ySpin);
    hl->addLayout(vl);

    QCheckBox* symChkBox = new QCheckBox(tr("Symmetrical grid"));

    symChkBox->setChecked(mIsSymmetrical);

    vl = new QVBoxLayout();
    vl->addLayout(hl);
    vl->addWidget(symChkBox);
    vl->addWidget(buttonBox);

    connect(xSpin, SIGNAL(valueChanged(int)), this, SLOT(xValueChanged(int)));
    connect(ySpin, SIGNAL(valueChanged(int)), this, SLOT(yValueChanged(int)));
    connect(symChkBox, SIGNAL(clicked (bool)), this, SLOT(symmetricalCheckBoxClicked(bool)));
    connect(buttonBox, SIGNAL(accepted()), mDialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), mDialog, SLOT(reject()));

    mDialog->setLayout(vl);
    return mDialog;
}

inline QPointF SCgGridArranger::mapFromSceneToGrid(const QPointF& point)
{
    return QPointF(qRound(point.x() / mXStep) * mXStep, qRound(point.y() / mYStep) * mYStep);
}

void SCgGridArranger::recalculateGhostsPosition()
{
    drawGrid(true);
    mPlaced.clear();
    QMap<SCgObject*, SCgObject*>::const_iterator i = mGhosts.constBegin();
    while (i != mGhosts.constEnd())
    {
        placeToGrid(i.value(), i.key());
        ++i;
    }

}


void SCgGridArranger::startOperation()
{
    mPlaced.clear();
    foreach(QGraphicsItem* it, mView->items())
    {
        if(SCgObject::isSCgObjectType(it->type()))
        {
            SCgObject* obj = static_cast<SCgObject*>(it);
            if(!obj->isDead())
                calculatePosition(obj);
        }
    }
}

void SCgGridArranger::calculatePosition(SCgObject* obj)
{
    Q_ASSERT_X(obj != 0, "void SCgGridArranger::calculatePosition(SCgObject* obj)",
               "Object pointer is null");

    if(!mPlaced.contains(obj))
    {
        mPlaced.insert(obj);

        QGraphicsItem* parent = obj->parentItem();

        int objType = obj->type();

        if(parent && SCgObject::isSCgObjectType(parent->type()))
        {
            SCgObject *_obj = static_cast<SCgObject*>(parent);
            if (_obj != 0)
                calculatePosition(_obj);
        }

        // If it isn't a point object, then simple maps it coordinates to grid.
        if(objType == SCgNode::Type)
        {
            QPointF pos = mapFromSceneToGrid(obj->scenePos());
            if(!parent)
                registerCommand(obj, pos);
            else
                registerCommand(obj, parent->mapFromScene(pos));
        }
        // Else, map each point to grid and set new points to object.
        // By the way we should map incident objects.
        else if (SCgObject::isSCgPointObjectType(objType))
        {
            SCgPointObject* pointObj = static_cast<SCgPointObject*>(obj);

            QVector<QPointF> points = pointObj->scenePoints();

            for(int i = 0; i < points.size(); ++i)
                points[i] = mapFromSceneToGrid(points.at(i));

            SCgObject *b_obj = pointObj->objectWithRole(SCgPointObject::IncidentBegin);
            if (b_obj != 0)
                calculatePosition(b_obj);
            SCgObject *e_obj = pointObj->objectWithRole(SCgPointObject::IncidentEnd);
            if (e_obj != 0)
                calculatePosition(e_obj);

            registerCommand(pointObj, pointObj->mapFromScene(points));
        }
    }
}

void SCgGridArranger::placeToGrid(SCgObject* obj, SCgObject* realObj)
{
    if(!mPlaced.contains(obj))
    {
        if(!obj || !realObj)
            return;
        mPlaced.insert(obj);

        QGraphicsItem* parent = obj->parentItem();

        if(parent && SCgObject::isSCgObjectType(parent->type()))
            placeToGrid(static_cast<SCgObject*>(parent),static_cast<SCgObject*>(realObj->parentItem()));

        int objType = obj->type();

        // If it isn't a point object, then simple maps it coordinates to grid.
        if(objType == SCgNode::Type)
        {
            QPointF pos = mapFromSceneToGrid(realObj->scenePos());
            if(!parent)
                obj->setPos(pos);
            else
                obj->setPos(parent->mapFromScene(pos));
        }
        // Else, map each point to grid and set new points to object.
        // By the way we should map incident objects.
        else if (SCgObject::isSCgPointObjectType(objType))
        {
            SCgPointObject* realPointObj = static_cast<SCgPointObject*>(realObj);
            SCgPointObject* ghostPointObj = static_cast<SCgPointObject*>(obj);

            QVector<QPointF> points = realPointObj->scenePoints();

            for(int i = 0; i < points.size(); ++i)
                points[i] = mapFromSceneToGrid(points.at(i));

            placeToGrid(ghostPointObj->objectWithRole(SCgPointObject::IncidentBegin),
                        realPointObj->objectWithRole(SCgPointObject::IncidentBegin));
            placeToGrid(ghostPointObj->objectWithRole(SCgPointObject::IncidentEnd),
                        realPointObj->objectWithRole(SCgPointObject::IncidentEnd));

            ghostPointObj->setPoints(ghostPointObj->mapFromScene(points));
        }
    }
}


void SCgGridArranger::drawGrid(bool draw)
{
    SCgScene* s = static_cast<SCgScene*>(mView->scene());
    s->setDrawGrid(draw, mGridColor, mXStep, mYStep);
}
