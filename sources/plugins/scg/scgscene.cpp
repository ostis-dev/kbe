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

#include "scgscene.h"

#include "scgobject.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"
#include "scgtextitem.h"
#include "scgpointgraphicsitem.h"
#include "scgcontentfactory.h"

#include "modes/scgbusmode.h"
#include "modes/scgpairmode.h"
#include "modes/scgcontourmode.h"
#include "modes/scgselectmode.h"
#include "modes/scginsertmode.h"
#include "modes/scgclonemode.h"

#include "commands/scgbasecommand.h"
#include "commands/scgcommandchangeincedentobject.h"
#include "commands/scgcommandclone.h"
#include "commands/scgcommandcontentchange.h"
#include "commands/scgcommandcontentvisibility.h"
#include "commands/scgcommandcreatebus.h"
#include "commands/scgcommandcreatecontour.h"
#include "commands/scgcommandcreatenode.h"
#include "commands/scgcommandcreatepair.h"
#include "commands/scgcommanddeletecontour.h"
#include "commands/scgcommandinsert.h"
#include "commands/scgcommandobjectdelete.h"
#include "commands/scgcommandobjectidtfchange.h"
#include "commands/scgcommandobjectmove.h"
#include "commands/scgcommandpointmove.h"
#include "commands/scgcommandobjecttypechange.h"
#include "commands/scgcommandselectedobjectmove.h"
#include "commands/scgcommandpointschange.h"
#include "commands/scgcommandidtfmove.h"
#include "commands/scgcommandswappairorient.h"

#include <QUrl>
#include <QFile>
#include <QMessageBox>
#include <QKeyEvent>
#include <QVector2D>
#include <QUndoStack>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QCursor>

SCgScene::SCgScene(QUndoStack *undoStack, QObject *parent) :
    QGraphicsScene(parent),
    mMode(0),
    mUndoStack(undoStack),
    mIsGridDrawn(false),
    mIsIdtfModelDirty(true),
    mCursor(0,0)
{
    mSceneModes.fill(0,(int)Mode_Count);

    mSceneModes[Mode_Bus] = new SCgBusMode(this);
    mSceneModes[Mode_Pair] = new SCgPairMode(this);
    mSceneModes[Mode_Contour] = new SCgContourMode(this);
    mSceneModes[Mode_Select] = new SCgSelectMode(this);
    mSceneModes[Mode_InsertTemplate] = new SCgInsertMode(this);
    mSceneModes[Mode_Clone] = new SCgCloneMode(this);

    setEditMode(Mode_Select);
    // grid foreground
    //setBackgroundBrush(QBrush(QColor(204, 255, 204, 164), Qt::CrossPattern));
    //    connect(this, SIGNAL(selectionChanged()), this, SLOT(ensureSelectedItemVisible()));
}

SCgScene::~SCgScene()
{
    // delete event handlers
    for (int i = 0; i < mSceneModes.size(); ++i)
        delete mSceneModes[i];
    mSceneModes.clear();
}

void SCgScene::setEditMode(EditMode mode)
{
    if(mMode)
    {
        if(mMode->mode() != mode) {
            mMode->deactivate();
            mPreviousEditMode = mMode->mode();
        }

        mMode->clean();
    }

    mMode = mSceneModes.at(mode);
    mMode->activate();

    editModeChanged(mode);
}

SCgScene::EditMode SCgScene::editMode() const
{
    return mMode->mode();
}

SCgObject* SCgScene::objectAt(const QPointF &point) const
{
    QList<QGraphicsItem*> itemList = items(point, Qt::IntersectsItemShape, Qt::DescendingOrder);


    foreach(QGraphicsItem* it, itemList)
        if (SCgObject::isSCgObjectType(it->type()))
            return static_cast<SCgObject*>(it);

    return 0;
}

void SCgScene::renderToImage(QPainter *painter, const QRectF &target, const QRectF &source, Qt::AspectRatioMode aspectRatioMode)
{
    QBrush brush = backgroundBrush();
    setBackgroundBrush(QBrush(Qt::NoBrush));
    render(painter, target, source, aspectRatioMode);
    setBackgroundBrush(brush);
}

void SCgScene::updateIdtfList()
{
    mIdtfList.clear();
    foreach(QGraphicsItem* item, items())
        if(SCgObject::isSCgObjectType(item->type()))
        {
            QString idtf = static_cast<SCgObject*>(item)->idtfValue();
            if(idtf != QString())
                mIdtfList.append(idtf);
        }

    mIdtfList.removeDuplicates();

    //    mIsIdtfModelDirty = false;
}

QStringList SCgScene::idtfList()
{
    if(mIsIdtfModelDirty)
        updateIdtfList();

    return mIdtfList;
}

QList<SCgObject*> SCgScene::itemsByType(int type) const {
    QList<QGraphicsItem*> allItems = items();
    QList<SCgObject*> resultList;
    foreach (QGraphicsItem* item, allItems)
        if (item->type() == type) resultList.append(static_cast<SCgObject*>(item));
    return resultList;
}


void SCgScene::setIdtfDirtyFlag()
{
    mIsIdtfModelDirty = true;
}

void SCgScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    mMode->mouseDoubleClick(event);
    //    if(!event->isAccepted())
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void SCgScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mMode);

    mMode->mousePress(event);
    if (!event->isAccepted())
        QGraphicsScene::mousePressEvent(event);
}

void SCgScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mMode);

    mMode->mouseMove(event);
    if(!event->isAccepted())
        QGraphicsScene::mouseMoveEvent(event);
}

void SCgScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mMode);

    mMode->mouseRelease(event);
    if(!event->isAccepted())
        QGraphicsScene::mouseReleaseEvent(event);
}

void SCgScene::keyPressEvent(QKeyEvent *event)
{
    Q_ASSERT(mMode);
    //    if (event->modifiers() == Qt::ShiftModifier && mEventHandler->mode() == Mode_Select)
    //        setEditMode(Mode_Clone);
    mMode->keyPress(event);
    if(!event->isAccepted())
        QGraphicsScene::keyPressEvent(event);
}

void SCgScene::keyReleaseEvent(QKeyEvent *event)
{
    Q_ASSERT(mMode);
    mMode->keyRelease(event);
    if(!event->isAccepted())
        QGraphicsScene::keyReleaseEvent(event);
}

SCgNode* SCgScene::createSCgNode(const QPointF &pos)
{
    SCgNode *node = new SCgNode;

    node->setPos(pos);
    node->setTypeAlias("node/const/general");

    addItem(node);
    return node;
}

SCgPair* SCgScene::createSCgPair(SCgObject *begObj, SCgObject *endObj, const QVector<QPointF> &points)
{
    Q_ASSERT_X(begObj && endObj,
               "SCgPair* SCgScene::createSCgPair(SCgObject *begObj, SCgObject *endObj, const QVector<QPointF> &points)",
               "Begin or end object is null");
    SCgPair *pair = new SCgPair;

    pair->setTypeAlias("pair/const/pos/perm/orient/accessory");

    pair->setBeginObject(begObj);
    pair->setEndObject(endObj);

    pair->setPoints(points);

    addItem(pair);

    return pair;
}

SCgBus* SCgScene::createSCgBus(const QVector<QPointF>& points, SCgNode *owner)
{
    SCgBus* bus = new SCgBus;

    if (owner != 0)
        bus->setOwner(owner);

    bus->setPoints(points);

    addItem(bus);

    return bus;
}

SCgContour* SCgScene::createSCgContour(const QVector<QPointF> &points)
{
    SCgContour *contour = new SCgContour;

    SCgPointObject::PointFVector v = points;
    QPolygonF polygon(v);

    QPointF center = polygon.boundingRect().center();

    contour->setPos(center);
    contour->setPoints(v);

    addItem(contour);

    return contour;
}

SCgBaseCommand* SCgScene::deleteSelObjectsCommand(SCgBaseCommand* parentCmd, bool addToStack)
{
    QList<QGraphicsItem*> selObjects = selectedItems();
    QList<QGraphicsItem*>::iterator it = selObjects.begin();

    SCgBaseCommand *cmd = 0;

    for (; it != selObjects.end(); ++it)
    {
        // skip none sc.g-objects
        if ( !SCgObject::isSCgObjectType((*it)->type()) )
            continue;

        SCgObject *obj = static_cast<SCgObject*>(*it);

        if (!cmd)
            cmd = new SCgCommandObjectDelete(this, obj, parentCmd);
        else
            new SCgCommandObjectDelete(this, obj, cmd);
    }
    // Delete points only if object is not deleted by previous operations
    if(!cmd)
    {
        SCgPointObject* parent = 0;
        SCgPointObject::PointFVector newPoints;
        QList<int> delIndexes; //< list with indexes of points which will be deleted

        for (it = selObjects.begin(); it != selObjects.end(); ++it)
        {
            // skip none Point items
            if ( (*it)->type() != SCgPointGraphicsItem::Type)
                continue;

            SCgPointGraphicsItem *item = static_cast<SCgPointGraphicsItem*>(*it);
            if(!parent)
            {
                parent = item->parentSCgPointObject();
                newPoints = parent->points();
                if(newPoints.size() < 2 || (parent->type() == SCgContour::Type && newPoints.size() < 3))
                    break; //If there are not enough points, we  should do nothing.
            }
            //We expect, that at the same time only one SCgPointObject is editable.
            Q_ASSERT(parent == item->parentSCgPointObject());

            delIndexes.push_back(item->pointIndex());
        }
        if(parent)
        {
            // Sort list in back order. Because after erasing item from vector, indexes
            // can be wrong. So we should delete in back order.
            qSort(delIndexes.begin(), delIndexes.end(), qGreater<int>());

            foreach(const int& index, delIndexes)
            {
                int s = newPoints.size();
                if(s > 2 && (parent->type() != SCgContour::Type || s > 3))//< another checking of points count
                    newPoints.erase(newPoints.begin()+index);
            }

            if(newPoints != parent->points())
                cmd = new SCgCommandPointsChange(this, parent, newPoints, parentCmd);
        }
    }

    if(cmd && addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::changeIdtfCommand(SCgObject *object, const QString &idtf, SCgBaseCommand* parentCmd, bool addToStack)
{
    Q_ASSERT_X(object != 0,
               "void SCgScene::changeIdtf(SCgObject *object, const QString &idtf)",
               "Object pointer is null");

    SCgBaseCommand* cmd = new SCgCommandObjectIdtfChange(this, object, idtf, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::changeObjectTypeCommand(SCgObject *object, const QString &type, SCgBaseCommand* parentCmd, bool addToStack)
{
    QString oldType = object->typeAlias();

    SCgBaseCommand* cmd = new SCgCommandObjectTypeChange(this, object, type, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}


SCgBaseCommand* SCgScene::deleteContourCommand(SCgContour *contour, SCgBaseCommand* parentCmd, bool addToStack)
{
    Q_ASSERT_X(contour != 0,
               "void SCgScene::deleteContour(SCgContour *contour)",
               "Pointer to contour object is null");

    SCgBaseCommand* cmd = new SCgCommandDeleteContour(this, contour, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::swapPairOrientCommand(SCgPair *pair, SCgBaseCommand *parentCmd, bool addToStack)
{
    Q_ASSERT_X(pair != 0,
               "SCgBaseCommand* SCgScene::swapPairOrient(SCgPair *pair, SCgBaseCommand *parentCmd, bool addToStack)",
               "Pointer to pair object is null");

    SCgBaseCommand* cmd = new SCgCommandSwapPairOrient(this, pair, parentCmd);

    if (addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::changeContentVisibilityCommand(SCgNode *node, bool visibility, SCgBaseCommand* parentCmd, bool addToStack)
{
    Q_ASSERT_X(node != 0,
               "void SCgScene::changeContentVisibility(SCgNode *node, bool visibility)",
               "Pointer to node object is null");

    SCgBaseCommand* cmd = new SCgCommandContentVisibility(this, node, visibility, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::changeContentDataCommand(SCgNode *node, const SCgContent::ContInfo &contInfo, SCgBaseCommand* parentCmd, bool addToStack)
{
    Q_ASSERT_X(node != 0,
               "void SCgScene::changeContentData(SCgNode *node, const QVariant &data, const QString &format, "
               "SCgContent::ContType cType, const QString &fileName)",
               "Pointer to node is null");

    SCgBaseCommand* cmd = new SCgCommandContentChange(this, node, contInfo, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

void SCgScene::pasteCommand(QList<QGraphicsItem*> itemList, SCgContour* parent)
{
    Q_ASSERT(mMode->mode() == Mode_InsertTemplate);

    QList<SCgObject*> objList;
    foreach (QGraphicsItem* item, itemList)
        objList.append(static_cast<SCgObject*>(item));
    mUndoStack->push(new SCgCommandInsert(this,objList,parent,0));

    setEditMode(mPreviousEditMode);
}

void SCgScene::cloneCommand(QList<QGraphicsItem*> itemList, SCgContour* parent)
{
    Q_ASSERT(mMode->mode() == Mode_Clone);

    QList<SCgObject*> objList;
    foreach (QGraphicsItem* item, itemList)
        objList.append(static_cast<SCgObject*>(item));

    mUndoStack->push(new SCgCommandClone(this,objList,parent,0));

    setEditMode(mPreviousEditMode);
}


SCgScene::EditMode SCgScene::previousMode() const {
    return mPreviousEditMode;
}

SCgBaseCommand* SCgScene::moveSelectedCommand(const ItemUndoInfo& undoInfo, SCgBaseCommand* parentCmd, bool addToStack)
{
    ItemUndoInfo::const_iterator it = undoInfo.begin();
    ObjectUndoInfo objUndoInfo;
    SCgBaseCommand* cmd = 0;

    for(;it != undoInfo.end(); ++it)
    {
        QGraphicsItem* item = it.key();

        // If SCgObject has moved then create SCgCommandObjectMove;
        if(SCgObject::isSCgObjectType(item->type()))
        {
            //Temporary fix problem with node moving when node has a bus.
            if(item->type() != SCgNode::Type || !undoInfo.contains(static_cast<SCgNode*>(item)->bus()))
                objUndoInfo[item] = it.value();
            // If PointItem has moved then create  SCgCommandPointMove command.
        }else if(item->type() == SCgPointGraphicsItem::Type)
        {
            SCgPointGraphicsItem* pointItem = static_cast<SCgPointGraphicsItem*>(item);
            if(!cmd)
                cmd = new SCgCommandPointMove(this, pointItem->parentSCgPointObject(),
                                              pointItem->pointIndex(), it.value().first.second,
                                              it.value().second.second, parentCmd);
            else
                new SCgCommandPointMove(this, pointItem->parentSCgPointObject(),
                                        pointItem->pointIndex(), it.value().first.second,
                                        it.value().second.second, cmd);
        }

        // If Incidence point has moved then
        else if(item->type() == SCgIncidentPointGraphicsItem::Type)
        {
            SCgIncidentPointGraphicsItem* i_item = static_cast<SCgIncidentPointGraphicsItem*>(item);
            if(i_item->canBeFixed())
            {
                SCgPointObject* p = i_item->parentSCgPointObject();
                SCgPointObject::IncidentRole role = i_item->role();
                SCgObject* oldObject = p->objectWithRole(role);
                SCgObject* newObject = i_item->objectAtPoint();
                const QPointF& oldPoint = it.value().first.second;
                const QPointF& newPoint = it.value().second.second;

                // If state really changed, then create command.
                if(newObject->type() != SCgNode::Type || oldObject != newObject)
                {
                    if(oldObject != newObject || oldPoint != newPoint)
                    {
                        if(!cmd)
                            cmd = new SCgCommandChangeIncedentObject(this, p, role, newObject, newPoint, parentCmd);
                        else
                            new SCgCommandChangeIncedentObject(this, p, role, newObject, newPoint, cmd);
                    }
                }
            }
        }
        else if (item->type() == SCgTextItem::Type)
        {
            if(!cmd)
                cmd = new SCgCommandIdtfMove(static_cast<SCgTextItem*>(item),
                                             this,
                                             it.value().first.second,
                                             it.value().second.second);
            else
                new SCgCommandIdtfMove(static_cast<SCgTextItem*>(item),
                                       this,
                                       it.value().first.second,
                                       it.value().second.second);
        }
    }

    if(!objUndoInfo.empty())
    {
        if(!cmd)
            cmd = new SCgCommandSelectedObjectMove(this, objUndoInfo, parentCmd);
        else
            new SCgCommandSelectedObjectMove(this, objUndoInfo, cmd);
    }

    if(cmd && addToStack)
        mUndoStack->push(cmd);

    return cmd;
}


SCgBaseCommand* SCgScene::addPointCommand(SCgPointObject* obj, const QPointF& point, SCgBaseCommand* parentCmd, bool addToStack)
{
    SCgPointObject::PointFVector oldPoints = obj->scenePoints();
    SCgPointObject::PointFVector newPoints = oldPoints;
    int i = SCgPointObject::indexForPoint(oldPoints, point, obj->type() == SCgContour::Type ? true : false);
    newPoints.insert(i, point);

    SCgBaseCommand* cmd = new SCgCommandPointsChange(this, obj, newPoints, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;

}

SCgBaseCommand* SCgScene::createNodeCommand(const QPointF& pos,
                                            SCgContour* parent,
                                            SCgBaseCommand* parentCmd,
                                            bool addToStack)
{
    SCgBaseCommand* cmd = new SCgCommandCreateNode(this, pos, parent, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}


SCgBaseCommand* SCgScene::createBusCommand(SCgNode* owner,
                                           const QVector<QPointF> &points,
                                           SCgContour* parent,
                                           SCgBaseCommand* parentCmd,
                                           bool addToStack)
{
    SCgBaseCommand* cmd = new SCgCommandCreateBus(this, owner, points, parent, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::createPairCommand( const QVector<QPointF> &points,
                                             SCgObject* beginObj,
                                             SCgObject* endObj,
                                             SCgContour* parent,
                                             SCgBaseCommand* parentCmd,
                                             bool addToStack)
{
    SCgBaseCommand* cmd = (new SCgCommandCreatePair(this, points, beginObj, endObj, parent, parentCmd));

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::createContourCommand(const QList<QGraphicsItem*>& childs,
                                               const QVector<QPointF> &points,
                                               SCgContour* parent,
                                               SCgBaseCommand* parentCmd,
                                               bool addToStack)
{
    SCgBaseCommand* cmd = new SCgCommandCreateContour(this, childs, points, parent, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}


SCgBaseCommand* SCgScene::changeObjectPositionCommand(SCgObject* obj,
                                                      const QPointF& newPos,
                                                      SCgBaseCommand* parentCmd,
                                                      bool addToStack)
{
    Q_ASSERT_X(obj != 0,
               "SCgBaseCommand* SCgScene::changeObjectPositionCommand(SCgObject* obj, const QPointF& newPos, SCgBaseCommand* parentCmd)",
               "Pointer to object is null");

    SCgBaseCommand* cmd = new SCgCommandObjectMove(this, obj, obj->pos(), newPos, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

SCgBaseCommand* SCgScene::changeObjectPointsCommand(SCgPointObject* obj,
                                                    const QVector<QPointF>& newPoints,
                                                    SCgBaseCommand* parentCmd,
                                                    bool addToStack)
{
    Q_ASSERT_X(obj != 0,
               "SCgBaseCommand* SCgScene::changeObjectPositionCommand(SCgObject* obj, const QPointF& newPos, SCgBaseCommand* parentCmd)",
               "Pointer to object is null");

    SCgBaseCommand* cmd = new SCgCommandPointsChange(this, obj, newPoints, parentCmd);

    if(addToStack)
        mUndoStack->push(cmd);

    return cmd;
}

void SCgScene::addCommandToStack(SCgBaseCommand* cmd)
{
    Q_ASSERT_X(cmd != 0,
               "SCgScene::addCommandToStack(SCgBaseCommand* cmd)",
               "Pointer to command is null");

    mUndoStack->push(cmd);
}

void SCgScene::setDrawGrid(bool draw, QColor color, int xStep, int yStep)
{
    mXStep = xStep;
    mYStep = yStep;
    mIsGridDrawn = draw;
    mGridColor = color;
    update();
}

void SCgScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    if(mIsGridDrawn)
    {
        qreal left = int(rect.left()) - (int(rect.left()) % mXStep);
        qreal top = int(rect.top()) - (int(rect.top()) % mYStep);

        painter->setPen(mGridColor);

        QVector<QLineF> linesX;
        for (qreal x = left; x < rect.right(); x += mXStep)
            linesX.append(QLineF(x, rect.top(), x, rect.bottom()));

        QVector<QLineF> linesY;
        for (qreal y = top; y < rect.bottom(); y += mYStep)
            linesY.append(QLineF(rect.left(), y, rect.right(), y));

        painter->drawLines(linesX);
        painter->drawLines(linesY);
    }
    else
        QGraphicsScene::drawBackground(painter, rect);
}


void SCgScene::setCursorPos(const QPointF& cursor)
{
    mCursor = cursor;
}


//! @return true if first item @p it1 lies left and above to item @p it2
bool topToBottomleftToRightSortingPredicate(SCgObject* it1, SCgObject* it2)
{
    Q_ASSERT(it1 && it2);
    bool isLeft = it1->sceneBoundingRect().x() < it2->sceneBoundingRect().x();
    bool isAbove = it1->sceneBoundingRect().y() < it2->sceneBoundingRect().y();
    bool haveSameY = it1->sceneBoundingRect().y() == it2->sceneBoundingRect().y();

    return isAbove || (isLeft && haveSameY);
}
SCgObject* SCgScene::find(const QString &ttf, FindFlags flg)
{
    if(ttf.isEmpty())
        return 0;

    // only SCgObjects
    QList<SCgObject*> list;
    foreach(QGraphicsItem* it, items())
    {
        if(SCgObject::isSCgObjectType(it->type()))
            list.append(static_cast<SCgObject*>(it));
    }

    if(list.isEmpty())
        return false;

    //for providing the same order in different calls of this function
    //we sort itemList by scene positions of items.
    qSort(list.begin(), list.end(), topToBottomleftToRightSortingPredicate);
    QList<SCgObject*>::const_iterator beginIt = list.begin();

    //Finds item (rather iterator), that lies closer to mCursor. From this position find process begins.
    while( true )
    {
        SCgObject *curr = *beginIt;
        bool isRight = curr->sceneBoundingRect().x() >= mCursor.x();
        bool isBelow = curr->sceneBoundingRect().y() >= mCursor.y();
        if (isRight && isBelow)
            break;

        ++beginIt;
        if(beginIt == list.end())
            break;
    }

    //If we don't have to check item under mCursor
    //then we'll change iterator position corresponding to search direction
    if(beginIt != list.end())
    {
        if( !(flg & CheckCurrent) && (*beginIt)->sceneBoundingRect().topLeft() == mCursor)
        {
            if(flg & FindForward)
                ++beginIt;
            else if( beginIt != list.begin())
                --beginIt;
            else
                return 0;
        }
    }else if (flg & FindForward)
        return 0;
    else
        --beginIt;

    SCgObject* result = 0;

    //iterate over all
    QList<SCgObject*>::const_iterator it = beginIt;
    while(true)
    {
        if( (*it)->idtfValue().startsWith(ttf, flg & CaseSensitive
                                          ? Qt::CaseSensitive
                                          : Qt::CaseInsensitive) )
        {
            result = *it;
            break;
        }

        if(flg & FindForward)
        {
            ++it;
            if(it == list.end())
                break;
        }else
        {
            if(it == list.begin())
                break;
            --it;
        }
    }

    return result;
}

void SCgScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    // get only the first file
    QString fileName = event->mimeData()->urls().at(0).toLocalFile();
    QString ext = fileName.mid(fileName.lastIndexOf(".") + 1);
    QMap<QString, SCgContentFactory::MimeAndSCgTypes> ext2MIME = SCgContentFactory::registeredExtentions2MIME();
    QList<QString> list = ext2MIME.keys();
    if (list.contains(ext)) {
        QGraphicsItem *item = itemAt(event->scenePos());
        SCgContour *parentContour = 0;
        SCgNode *node = 0;
        // check if we have a contour object under cursor
        if (!item) createNodeCommand(event->scenePos(), 0);
        else if (item->type() == SCgContour::Type) {
            parentContour = dynamic_cast<SCgContour*>(item);
            createNodeCommand(event->scenePos(), parentContour);
        }
        item = itemAt(event->scenePos());
        // check item we have a proxy widget under cursor
        if (item->type() == QGraphicsProxyWidget::Type) item = item->parentItem();
        node = qgraphicsitem_cast<SCgNode*>(item);
        QString MIMEType = ext2MIME.value(ext).first;
        SCgContent::ContType cType = ext2MIME.value(ext).second;
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            changeContentDataCommand(node, SCgContent::ContInfo(QVariant(file.readAll()), MIMEType, fileName, cType));
        }
        else QMessageBox::information(0,
                                      tr("File opening error"),
                                      file.errorString());
        event->acceptProposedAction();
    }
    else {
        QMessageBox::information(0,
                                 tr("Unsupported extention"),
                                 tr("Current file's extention doesn't supported"));
        event->ignore();
    }
}

void SCgScene::ensureSelectedItemVisible() {
    if (!selectedItems().isEmpty())
        views().at(0)->ensureVisible(selectedItems().at(0));
}
