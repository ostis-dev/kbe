/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

/*!
 * This file contains description of classes which you don't need to use directly.
 * Don't include this file. Use scgcontentinfo.h instead.
 */

#include "scgobject.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgpair.h"
#include "scgcontour.h"

#include <QSharedData>

class SCgObject;
class SCgNode;
class SCgPair;
class SCgContour;
class SCgBus;

/*! Class for storing SCgObject attributes.
 */
class SCgObjectInfoData: public QSharedData
{
    friend class SCgObjectInfo;
    friend class SCgNodeInfoData;
    friend class SCgBusInfoData;
    friend class SCgPairInfoData;
    friend class SCgContourInfoData;

public:
    explicit SCgObjectInfoData(const SCgObject* obj);
    SCgObjectInfoData(const SCgObjectInfoData &other);
    SCgObjectInfoData();
    virtual ~SCgObjectInfoData();

private:
    QString mTypeAlias;
    QString mIdtfValue;
    QColor mShapeColor;
    QString mId;
    QString mParentId;
};


/*! Class for storing SCgNode attributes.
 */
class SCgNodeInfoData:public QSharedData
{
    friend class SCgNodeInfo;

public:
    explicit SCgNodeInfoData(const SCgNode* obj);
    SCgNodeInfoData(const SCgNodeInfoData &other);
    SCgNodeInfoData();
    virtual ~SCgNodeInfoData();

private:
    QPointF mPos;
    bool mHaveBus;
    int mContentType;
    QString mContentMimeType;
    bool mContentVisible;
    QString mContentFilename;
    QVariant mContentData;
    int mIdtfPos;
    QString scsId;
};


/*! Class for storing SCgPair attributes.
 */
class SCgPairInfoData:public QSharedData
{
    friend class SCgPairInfo;
public:
    explicit SCgPairInfoData(const SCgPair* obj);

    SCgPairInfoData(const SCgPairInfoData &other);

    SCgPairInfoData();
    virtual ~SCgPairInfoData();

private:
    QVector<QPointF> mPoints;

    QString mBeginObjectId;
    QString mEndObjectId;
    double mBeginDot;
    double mEndDot;
};


/*! Class for storing SCgContour attributes.
 */
class SCgContourInfoData:public QSharedData
{
    friend class SCgContourInfo;
public:
    explicit SCgContourInfoData(const SCgContour* obj);

    SCgContourInfoData(const SCgContourInfoData &other);

    SCgContourInfoData();
    virtual ~SCgContourInfoData();
private:
    QPointF mPos;
    QVector<QPointF> mPoints;
};


/*! Class for storing SCgBus attributes.
 */
class SCgBusInfoData:public QSharedData
{
    friend class SCgBusInfo;
public:
    explicit SCgBusInfoData(const SCgBus* obj);

    SCgBusInfoData(const SCgBusInfoData &other);

    SCgBusInfoData();

    virtual ~SCgBusInfoData();
private:
    QVector<QPointF> mPoints;
    QString mOwnerId;

};

