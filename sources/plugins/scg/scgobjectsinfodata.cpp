/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgobjectsinfodata.h"

SCgObjectInfoData::SCgObjectInfoData(const SCgObject* obj):mTypeAlias(obj->typeAlias()),
                                    mIdtfValue(obj->idtfValue()),
                                    mShapeColor(obj->color()),
                                    mId(QString::number(obj->id())),
                                    mParentId(QString::number(obj->parentId()))
{

}

SCgObjectInfoData::SCgObjectInfoData(const SCgObjectInfoData &other): QSharedData(other),
                                    mTypeAlias(other.mTypeAlias),
                                    mIdtfValue(other.mIdtfValue),
                                    mShapeColor(other.mShapeColor),
                                    mId(other.mId),
                                    mParentId(other.mParentId)
{

}

SCgObjectInfoData::SCgObjectInfoData()
{

}

SCgObjectInfoData::~SCgObjectInfoData()
{

}

//________________________________________________

SCgNodeInfoData::SCgNodeInfoData(const SCgNode* obj): mPos(obj->scenePos()),
                                    mHaveBus(obj->bus()),
                                    mContentType(obj->contentType()),
                                    mContentMimeType(obj->contentMimeType()),
                                    mContentVisible(obj->isContentVisible()),
                                    mContentFilename(obj->contentFileName()),
                                    mContentData(obj->contentData()),
                                    mIdtfPos((int)obj->idtfPos())
{

}

SCgNodeInfoData::SCgNodeInfoData(const SCgNodeInfoData &other): QSharedData(other),
                                    mPos(other.mPos),
                                    mHaveBus(other.mHaveBus),
                                    mContentType(other.mContentType),
                                    mContentMimeType(other.mContentMimeType),
                                    mContentVisible(other.mContentVisible),
                                    mContentFilename(other.mContentFilename),
                                    mContentData(other.mContentData),
                                    mIdtfPos(other.mIdtfPos),
                                    scsId(other.scsId)
{

}

SCgNodeInfoData::SCgNodeInfoData()
{

}

SCgNodeInfoData::~SCgNodeInfoData()
{

}

//_______________________________________________

SCgPairInfoData::SCgPairInfoData(const SCgPair* obj):  mPoints(obj->points()),
                                    mBeginObjectId(QString::number(obj->beginObject()->id())),
                                    mEndObjectId(QString::number(obj->endObject()->id())),
                                    mBeginDot(obj->beginDot()),
                                    mEndDot(obj->endDot())
{

}

SCgPairInfoData::SCgPairInfoData(const SCgPairInfoData &other): QSharedData(other),
                                    mPoints(other.mPoints),
                                    mBeginObjectId(other.mBeginObjectId),
                                    mEndObjectId(other.mEndObjectId),
                                    mBeginDot(other.mBeginDot),
                                    mEndDot(other.mEndDot)
{

}

SCgPairInfoData::SCgPairInfoData()
{

}

SCgPairInfoData::~SCgPairInfoData()
{

}

//____________________________________________________

SCgContourInfoData::SCgContourInfoData(const SCgContour* obj): mPoints(obj->points()), mPos(obj->scenePos())
{

}

SCgContourInfoData::SCgContourInfoData(const SCgContourInfoData &other): QSharedData(other),
                                        mPoints(other.mPoints), mPos(other.mPos)
{

}

SCgContourInfoData::SCgContourInfoData()
{

}

SCgContourInfoData::~SCgContourInfoData()
{

}
//____________________________________________________


SCgBusInfoData::SCgBusInfoData(const SCgBus* obj): mPoints(obj->points()),
                                    mOwnerId(QString::number( obj->owner()->id() ))
{

}

SCgBusInfoData::SCgBusInfoData(const SCgBusInfoData &other): QSharedData(other),
                                        mPoints(other.mPoints),
                                        mOwnerId(other.mOwnerId)
{

}

SCgBusInfoData::SCgBusInfoData()
{

}

SCgBusInfoData::~SCgBusInfoData()
{

}
