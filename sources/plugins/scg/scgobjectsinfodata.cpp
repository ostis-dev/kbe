/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
                                    mIdtfPos(other.mIdtfPos)
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

SCgContourInfoData::SCgContourInfoData(const SCgContour* obj): mPoints(obj->points())
{

}

SCgContourInfoData::SCgContourInfoData(const SCgContourInfoData &other): QSharedData(other),
                                        mPoints(other.mPoints)
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
