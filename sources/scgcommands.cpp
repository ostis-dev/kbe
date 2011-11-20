#include "scgcommands.h"

#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgbus.h"
#include "scgscene.h"

SCgBaseCommand::SCgBaseCommand(SCgScene *scene,
                               SCgObject *object,
                               QUndoCommand *parent) :
        QUndoCommand(parent),
        mScene(scene),
        mObject(object)
{
    //Q_ASSERT(mObject);
}

SCgBaseCommand::~SCgBaseCommand()
{

}

QGraphicsScene* SCgBaseCommand::getScene() const
{
    return mScene;
}


// ------------------
SCgCommandObjectMove::SCgCommandObjectMove( SCgScene *scene,
                                            SCgObject* obj,
                                            const QPointF& oldPos,
                                            const QPointF& newPos,
                                            QUndoCommand *parent):
        SCgBaseCommand(scene, obj, parent),
        mOldPosition(oldPos),
        mNewPosition(newPos)
{
    setText(QObject::tr("Move item"));
}

SCgCommandObjectMove::~SCgCommandObjectMove()
{

}

void SCgCommandObjectMove::redo()
{
    SCgBaseCommand::redo();
    mObject->setPos(mNewPosition);
}

void SCgCommandObjectMove::undo()
{
    SCgBaseCommand::undo();
    mObject->setPos(mOldPosition);
}
// ------------------
SCgCommandSelectedObjectMove::SCgCommandSelectedObjectMove(SCgScene *scene,
                                                            const SCgScene::ObjectUndoInfo& undoInfo,
                                                            QUndoCommand *parent):
        SCgBaseCommand(scene, 0, parent),
        mUndoInfo(undoInfo)
{
    setText(QObject::tr("Move items"));
}

SCgCommandSelectedObjectMove::~SCgCommandSelectedObjectMove()
{

}

bool SCgCommandSelectedObjectMove::mergeWith (const QUndoCommand* command)
{
    if (command->id() != id() || childCount() || command->childCount())
        return false;

    const SCgCommandSelectedObjectMove* c = static_cast<const SCgCommandSelectedObjectMove*>(command);
    if(mUndoInfo.keys() != c->mUndoInfo.keys())
        return false;

    qreal maxManhattanLength = 0;

    SCgScene::ObjectUndoInfo::ConstIterator const_it = c->mUndoInfo.begin();
    while(const_it != c->mUndoInfo.end())
    {
        QPointF offset = const_it.value().second - const_it.value().first;
        if(offset.manhattanLength() > maxManhattanLength)
            maxManhattanLength = offset.manhattanLength();
        ++const_it;
    }

    if(maxManhattanLength > 35)
        return false;

    SCgScene::ObjectUndoInfo::iterator it = mUndoInfo.begin();
    while(it != mUndoInfo.end())
    {
        it.value().second = c->mUndoInfo.value(it.key()).second;
        ++it;
    }
    return true;
}

void SCgCommandSelectedObjectMove::redo()
{
    SCgScene::ObjectUndoInfo::ConstIterator const_it = mUndoInfo.begin();
    while(const_it != mUndoInfo.end())
    {
        const_it.key()->setPos(const_it.value().second);
        ++const_it;
    }
    SCgBaseCommand::redo();
}

void SCgCommandSelectedObjectMove::undo()
{
    SCgScene::ObjectUndoInfo::ConstIterator const_it = mUndoInfo.begin();
    while(const_it != mUndoInfo.end())
    {
        const_it.key()->setPos(const_it.value().first);
        ++const_it;
    }
}
// -------------------
SCgCommandPointMove::SCgCommandPointMove(SCgScene* scene,
                                        SCgPointObject* obj,
                                        int pointIndex,
                                        const QPointF& oldPos,
                                        const QPointF& newPos,
                                        QUndoCommand* parent):
            SCgBaseCommand(scene, obj, parent),
            mPointIndex(pointIndex),
            mOldPos(oldPos),
            mNewPos(newPos)
{
    setText(QObject::tr("Move object's point"));
}

SCgCommandPointMove::~SCgCommandPointMove()
{

}

void SCgCommandPointMove::redo()
{
    SCgBaseCommand::redo();
    ((SCgPointObject*)mObject)->changePointPosition(mPointIndex, mNewPos);
}
void SCgCommandPointMove::undo()
{
    ((SCgPointObject*)mObject)->changePointPosition(mPointIndex, mOldPos);
    SCgBaseCommand::undo();
}


// -------------------
SCgCommandPointsChange::SCgCommandPointsChange(SCgScene* scene,
                                                SCgPointObject* obj,
                                                const QVector<QPointF>& newPoints,
                                                QUndoCommand* parent):
            SCgBaseCommand(scene, obj, parent),
            mOldPoints(obj->points()),
            mNewPoints(newPoints)
{
    setText(QObject::tr("Change object's points"));
    if(obj->type() == SCgPair::Type)
    {
        mIsPair = true;
        mOldBeginDot = ((SCgPair*)obj)->getBeginDot();
        mOldEndDot = ((SCgPair*)obj)->getEndDot();
    }else
        mIsPair = false;
}

SCgCommandPointsChange::~SCgCommandPointsChange()
{

}

void SCgCommandPointsChange::redo()
{
    SCgBaseCommand::redo();
    ((SCgPointObject*)mObject)->setPoints(mNewPoints);
}

void SCgCommandPointsChange::undo()
{
    ((SCgPointObject*)mObject)->setPoints(mOldPoints);
    if(mIsPair)
    {
        ((SCgPair*)mObject)->setBeginDot(mOldBeginDot);
        ((SCgPair*)mObject)->setEndDot(mOldEndDot);
    }
    SCgBaseCommand::undo();
}
// -------------------

SCgCommandChangeIncedentObject::SCgCommandChangeIncedentObject(SCgScene* scene,
                                                                SCgPointObject* obj,
                                                                SCgPointObject::IncidentRole role,
                                                                SCgObject* newObj,
                                                                const QPointF& newPoint,
                                                                QUndoCommand* parent):
                                            SCgBaseCommand(scene, obj, parent),
                                            mRole(role),
                                            mOldObject(obj->objectWithRole(role)),
                                            mNewObject(newObj),
                                            mNewPoint(newPoint)
{
    setText(QObject::tr("Change incident object"));
    int i = role == SCgPointObject::IncidentBegin ? 1 : obj->points().size() - 1;
    if(mOldObject)
        mOldPoint = obj->mapFromScene(mOldObject->cross(obj->mapToScene(obj->pointAt(i)), obj->dotAtRole(role)));
    else
        mOldPoint = obj->pointAt(0);
}

SCgCommandChangeIncedentObject::~SCgCommandChangeIncedentObject()
{

}

void SCgCommandChangeIncedentObject::redo()
{
    ((SCgPointObject*)mObject)->changeIncidentObject(mNewObject, mNewPoint, mRole);
    SCgBaseCommand::redo();
}

void SCgCommandChangeIncedentObject::undo()
{
    SCgBaseCommand::undo();
    ((SCgPointObject*)mObject)->changeIncidentObject(mOldObject, mOldPoint, mRole);
}


//------------------------------------
SCgCommandObjectDelete::SCgCommandObjectDelete(SCgScene *scene,
                                               SCgObject *object,
                                               QUndoCommand *parent) :
        SCgBaseCommand(scene, object, parent)
{
    setText(QObject::tr("Delete object"));
}

SCgCommandObjectDelete::~SCgCommandObjectDelete()
{

}

void SCgCommandObjectDelete::redo()
{
    mDelList.clear();
    mParents.clear();

    mObject->del(mDelList);

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        QGraphicsItem *parent = object->parentItem();

        mParents[object] = parent;

        if(object->scene() == mScene)
        {
            object->setParentItem(0);
            mScene->removeItem(object);
        }
    }

    SCgBaseCommand::redo();
}
//back
void SCgCommandObjectDelete::undo()
{
    SCgBaseCommand::undo();

    QList<SCgObject*>::iterator it;
    for (it = mDelList.begin(); it != mDelList.end(); ++it)
    {
        SCgObject *object = *it;
        if(!object->parentItem())
        {
            QGraphicsItem *parent = mParents[object];

            object->undel(mScene);

            object->setParentItem(parent);
            object->updatePosition();
        }
    }

}

// -------------------
SCgCommandInsert::SCgCommandInsert( SCgScene *scene,
                                    QList<SCgObject*> objList,
                                    SCgContour* parentContour,
                                    QUndoCommand *parent) :
        SCgBaseCommand(scene, 0, parent),
        mList(objList),
        mParent(parentContour)
{
    foreach(SCgObject* obj, mList)
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(objectFromListDestroyed(QObject*)));

    setText(QObject::tr("Insert"));
}

SCgCommandInsert::~SCgCommandInsert()
{
    foreach(SCgObject* obj, mList)
        delete obj;
}

void SCgCommandInsert::objectFromListDestroyed(QObject* obj)
{
    mList.removeOne((SCgObject*)obj);
}

void SCgCommandInsert::redo()
{
    SCgBaseCommand::redo();

    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;

        object->setDead(false);
        if(object->scene() != mScene)
            mScene->addItem(object);

        object->setParentItem(mParent);
        object->updatePosition();
    }
}

void SCgCommandInsert::undo()
{
    QList<SCgObject*>::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        SCgObject *object = *it;
        object->setDead(true);
        object->setParentItem(0);
        mScene->removeItem(object);
    }

    SCgBaseCommand::undo();
}
// -------------------
SCgCommandObjectIdtfChange::SCgCommandObjectIdtfChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newIdtf,
                                                       QUndoCommand *parent) :
        SCgBaseCommand(scene, object, parent),
        mNewIdtf(newIdtf)
{
    setText(QObject::tr("Change object's identifier"));
    mOldIdtf = mObject->idtfValue();
}

SCgCommandObjectIdtfChange::~SCgCommandObjectIdtfChange()
{

}

void SCgCommandObjectIdtfChange::redo()
{
    mObject->setIdtfValue(mNewIdtf);
}

void SCgCommandObjectIdtfChange::undo()
{
    mObject->setIdtfValue(mOldIdtf);
}

// --------------------
SCgCommandObjectTypeChange::SCgCommandObjectTypeChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newType,
                                                       QUndoCommand *parent) :
        SCgBaseCommand(scene, object, parent),
        mNewType(newType)
{
    setText(QObject::tr("Change object's type"));
    mOldType = mObject->typeAlias();
}

SCgCommandObjectTypeChange::~SCgCommandObjectTypeChange()
{

}

void SCgCommandObjectTypeChange::redo()
{
    mObject->setTypeAlias(mNewType);
}

void SCgCommandObjectTypeChange::undo()
{
    mObject->setTypeAlias(mOldType);
}

// ------------------
SCgCommandCreateNode::SCgCommandCreateNode(SCgScene *scene,
                                           const QPointF &point,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoint(point),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgNode(mPoint);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(nodeDestroyed()));

    setText(QObject::tr("Create node"));
}

SCgCommandCreateNode::~SCgCommandCreateNode()
{
    if(mObject)
        delete mObject;
}

void SCgCommandCreateNode::nodeDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateNode::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateNode::undo()",
               "Node doesn't exists");

    mObject->setParentItem(0);
    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}

void SCgCommandCreateNode::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateNode::redo()",
               "Node doesn't exists");

    if(mObject->scene() != mScene)
    	mScene->addItem(mObject);

    mObject->setDead(false);

    if (mParentContour)
        mObject->setParentItem(mParentContour);

    SCgBaseCommand::redo();
}

// ------------------
SCgCommandCreatePair::SCgCommandCreatePair(SCgScene *scene,
                                           const QVector<QPointF> &points,
                                           SCgObject *beginObject,
                                           SCgObject *endObject,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoints(points),
    mBeginObject(beginObject),
    mEndObject(endObject),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgPair(mBeginObject, mEndObject, mPoints);

    connect(mObject, SIGNAL(destroyed()), this, SLOT(pairDestroyed()));
    setText(QObject::tr("Create pair"));
}

SCgCommandCreatePair::~SCgCommandCreatePair()
{
    if(mObject)
        delete mObject;
}

void SCgCommandCreatePair::pairDestroyed()
{
    mObject = 0;
}

void SCgCommandCreatePair::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::redo()",
               "Pair doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
    	mScene->addItem(mObject);

    mObject->setDead(false);

    if(mParentContour)
        mObject->setParentItem(mParentContour);

    mObject->updatePosition();

}

void SCgCommandCreatePair::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::undo()",
               "Pair doesn't exists");

    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}

// ------------------
SCgCommandCreateBus::SCgCommandCreateBus(SCgScene *scene,
                                           SCgNode *owner,
                                           const QVector<QPointF> &points,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mOwner(owner),
    mPoints(points),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgBus(mPoints, mOwner);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(busDestroyed()));
    setText(QObject::tr("Create bus"));
}

SCgCommandCreateBus::~SCgCommandCreateBus()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateBus::busDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateBus::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::redo()",
               "Bus doesn't exists");
    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
    	mScene->addItem(mObject);

    mObject->setParentItem(mParentContour);
    mObject->setDead(false);

    ((SCgBus*)mObject)->setOwner(mOwner);
}

void SCgCommandCreateBus::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::undo()",
               "Bus doesn't exists");

    ((SCgBus*)mObject)->setOwner(0);
    mObject->setParentItem(0);

    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}


// ------------------
SCgCommandCreateContour::SCgCommandCreateContour(SCgScene *scene,
                                                 const QList<QGraphicsItem *> &childs,
                                                 const QVector<QPointF> &points,
                                                 SCgContour *parentContour,
                                                 QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoints(points),
    mChildObjects(childs),
    mParentContour(parentContour)
{
    mObject = mScene->createSCgContour(mPoints);
    connect(mObject, SIGNAL(destroyed()), this, SLOT(contourDestroyed()));
    setText(QObject::tr("Create contour"));
}

SCgCommandCreateContour::~SCgCommandCreateContour()
{
    if (mObject)
        delete mObject;
}

void SCgCommandCreateContour::contourDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateContour::redo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::redo()",
               "Contour doesn't exists");

    SCgBaseCommand::redo();

    if(mObject->scene() != mScene)
    	mScene->addItem(mObject);

    mObject->setDead(false);

    QList<QGraphicsItem*>::iterator it = mChildObjects.begin();
    for (; it != mChildObjects.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        (*it)->setParentItem(mObject);
    }

    if(mParentContour)
        mObject->setParentItem(mParentContour);
}

void SCgCommandCreateContour::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::undo()",
               "Contour doesn't exists");

    QGraphicsItem *parent = mObject->parentItem();
    QList<QGraphicsItem*> childs = mObject->childItems();
    QList<QGraphicsItem*>::iterator it = childs.begin();
    for (; it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        item->setParentItem(parent);
    }

    mObject->setParentItem(0);
    mScene->removeItem(mObject);
    mObject->setDead(true);

    SCgBaseCommand::undo();
}


// ------------------
SCgCommandDeleteContour::SCgCommandDeleteContour(SCgScene *scene,
                                                         SCgContour *contour,
                                                         QUndoCommand *parent) :
        SCgBaseCommand(scene, 0, parent),
        mContour(contour)
{
    setText(QObject::tr("Delete contour"));
    Q_ASSERT_X(mContour != 0,
               "SCgCommandDeleteJustContour::SCgCommandDeleteJustContour(SCgScene *scene, "
               "SCgContour *contour, QUndoCommand *parent)",
               "Pointer to contour object is null");
}

SCgCommandDeleteContour::~SCgCommandDeleteContour()
{
}

void SCgCommandDeleteContour::redo()
{
    mChilds.clear();

    QGraphicsItem *parent = mContour->parentItem();
    QList<QGraphicsItem*> childs = mContour->childItems();
    QList<QGraphicsItem*>::iterator it;
    for (it = childs.begin(); it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        mChilds.push_back(item);
        item->setParentItem(parent);
    }

    if (childCount() == 0)
        new SCgCommandObjectDelete(mScene, mContour, this);

    SCgBaseCommand::redo();
}

void SCgCommandDeleteContour::undo()
{
    SCgBaseCommand::undo();

    QList<QGraphicsItem*>::iterator it;
    for (it = mChilds.begin(); it != mChilds.end(); ++it)
    {
        QGraphicsItem *item = *it;
        item->setParentItem(mContour);
    }
}

// ------------------
SCgCommandContentVisibility::SCgCommandContentVisibility(SCgScene *scene,
                                                         SCgNode *node,
                                                         bool visibility,
                                                         QUndoCommand *parent) :
    SCgBaseCommand(scene, node, parent),
    mNode(node),
    mVisibility(visibility)
{
    Q_ASSERT_X(mNode != 0,
               "SCgCommandContentVisibility::SCgCommandContentVisibility(SCgScene *scene,"
               "SCgNode *node, bool visibility, QUndoCommand *parent)",
               "Pointer to node is null");

    setText(QObject::tr("Change content visibility"));
}

SCgCommandContentVisibility::~SCgCommandContentVisibility()
{

}

void SCgCommandContentVisibility::redo()
{
    if (mVisibility)
        mNode->showContent();
    else
        mNode->hideContent();

    SCgBaseCommand::redo();
}

void SCgCommandContentVisibility::undo()
{
    SCgBaseCommand::undo();

    if (!mVisibility)
        mNode->showContent();
    else
        mNode->hideContent();
}

// ------------------
SCgCommandContentChange::SCgCommandContentChange(SCgScene *scene,
                                                 SCgNode *node,
                                                 const SCgContent::ContInfo &contInfo,
                                                 QUndoCommand *parent):
    SCgBaseCommand(scene, mNode, parent),
    mNode(node),
    mContentInfo(contInfo)
{
    setText(QObject::tr("Change content"));
    mContentVisibility = mNode->isContentVisible();
}

SCgCommandContentChange::~SCgCommandContentChange()
{

}

void SCgCommandContentChange::redo()
{
    mNode->contentInfo(mOldContentInfo);

    mNode->setContent(mContentInfo.mimeType,
                      mContentInfo.data,
                      mContentInfo.fileName,
                      mContentInfo.type);

    SCgBaseCommand::redo();
}

void SCgCommandContentChange::undo()
{
    SCgBaseCommand::undo();

    mNode->setContent(mOldContentInfo.mimeType,
                      mOldContentInfo.data,
                      mOldContentInfo.fileName,
                      mOldContentInfo.type);

    if(!mNode->isContentVisible() && mContentVisibility)
        mNode->showContent();
}
