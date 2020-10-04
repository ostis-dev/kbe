/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <QGraphicsScene>

#include "scgdefaultobjectbuilder.h"
#include "scgobjectsinfo.h"

#include "scgnode.h"
#include "scgbus.h"
#include "scgcontour.h"
#include "scgpair.h"

DefaultSCgObjectBuilder::DefaultSCgObjectBuilder(QGraphicsScene* scene)
    : AbstractSCgObjectBuilder()
    , mScene(scene)
{
}

DefaultSCgObjectBuilder::~DefaultSCgObjectBuilder()
{
}

void DefaultSCgObjectBuilder::buildObjects(const AbstractSCgObjectBuilder::TypeToObjectsMap& objects)
{
    SCgObjectInfo* info;
    // parse nodes
    foreach(info, objects[SCgNode::Type])
        buildNode(static_cast<SCgNodeInfo*>(info));
    // parse pairs
    foreach(info, objects[SCgPair::Type])
        buildPair(static_cast<SCgPairInfo*>(info));
    // parse buses
    foreach(info, objects[SCgBus::Type])
        buildBus(static_cast<SCgBusInfo*>(info));
    // parse contours
    foreach(info, objects[SCgContour::Type])
        buildContour(static_cast<SCgContourInfo*>(info));

    // set parents relation
    ParentChildMap::iterator parentIt;
    for (parentIt = mParentChild.begin(); parentIt != mParentChild.end(); parentIt++)
    {
        if (!mId2SCgObj.contains(parentIt.value()))
            continue;

        SCgObject *parent = mId2SCgObj[parentIt.value()];
        SCgObject *child = mId2SCgObj[parentIt.key()];

        child->setParentItem(parent);
    }

    // holds true, if there are errors while setting begin and end objects.
    bool isConnectedDuty = false;
    // set begin and end objects for pairs
    foreach(SCgObjectInfo* info, objects[SCgPair::Type])
    {
        SCgPairInfo* pairInfo = static_cast<SCgPairInfo*>(info);
        SCgPair *pair = static_cast<SCgPair*>(mId2SCgObj[pairInfo->id()]);

        // we can't build pair without begin or end objects
        if (!mId2SCgObj.contains(pairInfo->beginObjectId()) ||
            !mId2SCgObj.contains(pairInfo->endObjectId()))
        {
            mErrors.append(QObject::tr("Can't find begin or end object for pair id=\"%1\"")
                                            .arg(pairInfo->id()));
            mId2SCgObj.remove(pairInfo->id());
            isConnectedDuty = true;
            delete pair;
            continue;
        }

        SCgObject *begObject = mId2SCgObj[pairInfo->beginObjectId()];
        SCgObject *endObject = mId2SCgObj[pairInfo->endObjectId()];

        pair->setBeginObject(begObject);
        pair->setEndObject(endObject);
    }
    // In this case we must check if all begin and end objects are valid.
    // If they not, we have to delete all unfinished pairs.
    // It isn't optimal solution but it executed only if there are errors in loaded file.
    while(isConnectedDuty)
    {
        isConnectedDuty = false;
        foreach(SCgObjectInfo* info, objects[SCgPair::Type])
        {
            SCgPairInfo* pairInfo = static_cast<SCgPairInfo*>(info);

            bool isNotContainOne = !(mId2SCgObj.contains(pairInfo->beginObjectId()) &&
                                     mId2SCgObj.contains(pairInfo->endObjectId()));
            if (  mId2SCgObj.contains(pairInfo->id()) && isNotContainOne)
            {
                SCgPair *pair = static_cast<SCgPair*>(mId2SCgObj[pairInfo->id()]);
                mId2SCgObj.remove(pairInfo->id());
                delete pair;
                isConnectedDuty = true;
            }
        }
    }

    // set bus owners
    foreach(SCgObjectInfo* info, objects[SCgBus::Type])
    {
        SCgBusInfo* busInfo = static_cast<SCgBusInfo*>(info);
        SCgObject *objectOwner = 0;

        if (!mId2SCgObj.contains(busInfo->ownerId()))
        {
            SCgNode *node = new SCgNode;

            node->setPos(busInfo->points().first());
            node->setTypeAlias("node/const/general_node");
            objectOwner = node;
            mScene->addItem(node);
        }else
            objectOwner = mId2SCgObj[busInfo->ownerId()];

        // check type and set owner to bus
        if (objectOwner->type() != SCgNode::Type)
        {
            mErrors.append(QObject::tr("Try to set the bus owner(\"%1\") which is not a node type. Bus id=\"%2\"")
                                            .arg(busInfo->ownerId())
                                            .arg(busInfo->id()));
            continue;
        }

        SCgBus *bus = static_cast<SCgBus*>(mId2SCgObj[busInfo->id()]);
        SCgNode *owner = static_cast<SCgNode*>(objectOwner);

        bus->setOwner(owner);
    }
}

void DefaultSCgObjectBuilder::setObjectInfo(SCgObject* obj, SCgObjectInfo* info)
{
    obj->setTypeAlias(info->typeAlias());
    obj->setIdtfValue(info->idtfValue());

    // store parent id
    mParentChild[info->id()] = info->parentId();

    // store for id mapping
    mId2SCgObj[info->id()] = obj;

    // Adding item on scene
    mScene->addItem(obj);
}

void DefaultSCgObjectBuilder::buildNode(SCgNodeInfo* info)
{
    if(!mId2SCgObj.contains(info->id()))
    {
        SCgNode *node = new SCgNode;

        node->setPos(info->pos());
        node->setContent(info->contentMimeType(),
                         info->contentData(),
                         info->contentFilename(),
                         (SCgContent::ContType)info->contentType());
        if (!node->contentData().isNull() && info->contentVisible())
            node->showContent();
        setObjectInfo(node, info);
        node->setIdtfPos((SCgNode::IdentifierPosition)info->idtfPos());

    }
}

void DefaultSCgObjectBuilder::buildPair(SCgPairInfo* info)
{
    if(!mId2SCgObj.contains(info->id()))
    {
        SCgPair* pair = new SCgPair;

        pair->setBeginDot(info->beginDot());
        pair->setEndDot(info->endDot());
        pair->setPoints(info->points());

        setObjectInfo(pair, info);
    }
}

void DefaultSCgObjectBuilder::buildBus(SCgBusInfo* info)
{
    if(!mId2SCgObj.contains(info->id()))
    {
        SCgBus* bus = new SCgBus;

        bus->setPoints(info->points());

        setObjectInfo(bus, info);
    }
}

void DefaultSCgObjectBuilder::buildContour(SCgContourInfo* info)
{
    if(info->points().size() > 2)
    {
        if(!mId2SCgObj.contains(info->id()))
        {
            SCgContour* contour = new SCgContour;

            contour->setPos(QPolygonF(info->points()).boundingRect().center());
            contour->setPoints(info->points());
            if ((info->pos().x()!= 0) | (info->pos().y()!= 0)) {
                contour->setIdtfValue(info->idtfValue());
                contour->setIdtfPos(info->pos());
            }

            setObjectInfo(contour, info);
        }
    }else
    {
        mErrors.append(QObject::tr("Try to create contour (\"%1\") with less than 3 points.")
                                        .arg(info->id()) );
    }
}
