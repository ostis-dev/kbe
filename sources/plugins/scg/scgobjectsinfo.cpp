/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgobjectsinfo.h"
#include "scgobjectsinfodata.h"

SCgObjectInfo::SCgObjectInfo(const SCgObject* obj)
{
    d = new SCgObjectInfoData (obj);
}

SCgObjectInfo::SCgObjectInfo(const SCgObjectInfo &other): d(other.d)
{

}

SCgObjectInfo::SCgObjectInfo()
{
    d = new SCgObjectInfoData();
}

SCgObjectInfo::~SCgObjectInfo()
{

}

int SCgObjectInfo::objectType() const
{
    return SCgObject::Type;
}

const QString& SCgObjectInfo::typeAlias() const
{
    return d->mTypeAlias;
}
const QString& SCgObjectInfo::idtfValue() const
{
    return d->mIdtfValue;
}
QColor SCgObjectInfo::shapeColor() const
{
    return d->mShapeColor;
}
const QString& SCgObjectInfo::id() const
{
    return d->mId;
}
const QString& SCgObjectInfo::parentId() const
{
    return d->mParentId;
}


QString& SCgObjectInfo::typeAliasRef()
{
    return d->mTypeAlias;
}
QString& SCgObjectInfo::idtfValueRef()
{
    return d->mIdtfValue;
}
QColor& SCgObjectInfo::shapeColorRef()
{
    return d->mShapeColor;
}
QString& SCgObjectInfo::idRef()
{
    return d->mId;
}
QString& SCgObjectInfo::parentIdRef()
{
    return d->mParentId;
}

//________________________________________________
SCgNodeInfo::SCgNodeInfo(const SCgNode* obj)
{
    d = new SCgNodeInfoData (obj);
}

SCgNodeInfo::SCgNodeInfo(const SCgNodeInfo &other): SCgObjectInfo(other)
{

}

SCgNodeInfo::SCgNodeInfo()
{
    d = new SCgNodeInfoData();
}

SCgNodeInfo::~SCgNodeInfo()
{

}

int SCgNodeInfo::objectType() const
{
    return SCgNode::Type;
}

QPointF SCgNodeInfo::pos() const
{
    return d->mPos;
}
bool SCgNodeInfo::haveBus() const
{
    return d->mHaveBus;
}
int SCgNodeInfo::contentType() const
{
    return d->mContentType;
}
const QString& SCgNodeInfo::contentMimeType() const
{
    return d->mContentMimeType;
}

bool SCgNodeInfo::contentVisible() const
{
    return d->mContentVisible;
}
const QString& SCgNodeInfo::contentFilename() const
{
    return d->mContentFilename;
}
const QVariant& SCgNodeInfo::contentData() const
{
    return d->mContentData;
}

int SCgNodeInfo::idtfPos() const
{
    return d->mIdtfPos;
}

QString SCgNodeInfo::scsId() const
{
    return d->scsId;
}

QPointF& SCgNodeInfo::posRef()
{
    return d->mPos;
}
bool& SCgNodeInfo::haveBusRef()
{
    return d->mHaveBus;
}
int& SCgNodeInfo::contentTypeRef()
{
    return d->mContentType;
}
QString& SCgNodeInfo::contentMimeTypeRef()
{
    return d->mContentMimeType;
}

bool &SCgNodeInfo::contentVisibleRef()
{
    return d->mContentVisible;
}
QString& SCgNodeInfo::contentFilenameRef()
{
    return d->mContentFilename;
}
QVariant& SCgNodeInfo::contentDataRef()
{
    return d->mContentData;
}

int& SCgNodeInfo::idtfPosRef()
{
    return d->mIdtfPos;
}

QString& SCgNodeInfo::scsIdRef()
{
    return d->scsId;
}

//________________________________________________
SCgPairInfo::SCgPairInfo(const SCgPair* obj)
{
    d = new SCgPairInfoData (obj);
}

SCgPairInfo::SCgPairInfo(const SCgPairInfo &other): SCgObjectInfo(other)
{

}

SCgPairInfo::SCgPairInfo()
{
    d = new SCgPairInfoData();
}

SCgPairInfo::~SCgPairInfo()
{

}

int SCgPairInfo::objectType() const
{
    return SCgPair::Type;
}

const QVector<QPointF>& SCgPairInfo::points() const
{
    return d->mPoints;
}
const QString& SCgPairInfo::beginObjectId() const
{
    return d->mBeginObjectId;
}
const QString& SCgPairInfo::endObjectId() const
{
    return d->mEndObjectId;
}
double SCgPairInfo::beginDot() const
{
    return d->mBeginDot;
}
double SCgPairInfo::endDot() const
{
    return d->mEndDot;
}
QVector<QPointF>& SCgPairInfo::pointsRef()
{
    return d->mPoints;
}
QString& SCgPairInfo::beginObjectIdRef()
{
    return d->mBeginObjectId;
}
QString& SCgPairInfo::endObjectIdRef()
{
    return d->mEndObjectId;
}
double& SCgPairInfo::beginDotRef()
{
    return d->mBeginDot;
}
double& SCgPairInfo::endDotRef()
{
    return d->mEndDot;
}
//________________________________________________
SCgBusInfo::SCgBusInfo(const SCgBus* obj)
{
    d = new SCgBusInfoData (obj);
}

SCgBusInfo::SCgBusInfo(const SCgBusInfo &other): SCgObjectInfo(other)
{

}

SCgBusInfo::SCgBusInfo()
{
    d = new SCgBusInfoData();
}

SCgBusInfo::~SCgBusInfo()
{

}

int SCgBusInfo::objectType() const
{
    return SCgBus::Type;
}

const QVector<QPointF>& SCgBusInfo::points() const
{
    return d->mPoints;
}
const QString& SCgBusInfo::ownerId() const
{
    return d->mOwnerId;
}
QVector<QPointF>& SCgBusInfo::pointsRef()
{
    return d->mPoints;
}

QString& SCgBusInfo::ownerIdRef()
{
    return d->mOwnerId;
}
//________________________________________________
SCgContourInfo::SCgContourInfo(const SCgContour* obj)
{
    d = new SCgContourInfoData (obj);
}

QPointF SCgContourInfo::pos() const
{
    return d->mPos;
}

SCgContourInfo::SCgContourInfo(const SCgContourInfo &other): SCgObjectInfo(other)
{

}

SCgContourInfo::SCgContourInfo()
{
    d = new SCgContourInfoData();
}

SCgContourInfo::~SCgContourInfo()
{

}

int SCgContourInfo::objectType() const
{
    return SCgContour::Type;
}

const QVector<QPointF>& SCgContourInfo::points() const
{
    return d->mPoints;
}

QPointF& SCgContourInfo::posRef()
{
    return d->mPos;
}

QVector<QPointF>& SCgContourInfo::pointsRef()
{
    return d->mPoints;
}
