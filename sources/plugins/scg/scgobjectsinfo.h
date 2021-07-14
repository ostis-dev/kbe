/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

/*!
 * This file contains implicitly shared classes for storing SCgObjects information.
 */

#include <QSharedDataPointer>
#include <QColor>
#include <QPointF>

class SCgObjectInfoData;
class SCgNodeInfoData;
class SCgBusInfoData;
class SCgContourInfoData;
class SCgPairInfoData;

class SCgObject;
class SCgBus;
class SCgNode;
class SCgPair;
class SCgContour;

class SCgObjectInfo
{
public:
    explicit SCgObjectInfo(const SCgObject* obj);

    SCgObjectInfo(const SCgObjectInfo &other);

    SCgObjectInfo();

    virtual ~SCgObjectInfo();
    /**
     * \defgroup readAccess Read Access Functions
     * @{
     */

    //! @return object type for this instance. (e.g. SCgNode::Type)
    virtual int objectType() const;

    const QString& typeAlias() const;
    const QString& idtfValue() const;
    QColor shapeColor() const;
    const QString& id() const;
    const QString& parentId() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QString& typeAliasRef();
    QString& idtfValueRef();
    QColor& shapeColorRef();
    QString& idRef();
    QString& parentIdRef();
    /**@}*/
protected:
    QSharedDataPointer<SCgObjectInfoData> d;
};


class SCgNodeInfo: public SCgObjectInfo
{
public:
    explicit SCgNodeInfo(const SCgNode* obj);

    SCgNodeInfo(const SCgNodeInfo &other);

    SCgNodeInfo();

    virtual ~SCgNodeInfo();

    /**
     * \defgroup readAccess Read Access Functions
     * @{
     */
    virtual int objectType() const;

    QPointF pos() const;
    bool haveBus() const;
    int contentType() const;
    const QString& contentMimeType() const;
    bool contentVisible() const;
    const QString& contentFilename() const;
    const QVariant& contentData() const;
    int idtfPos() const;
    QString scsId() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QPointF& posRef();
    bool& haveBusRef();
    int& contentTypeRef();
    QString& contentMimeTypeRef();
    bool& contentVisibleRef();
    QString& contentFilenameRef();
    QVariant& contentDataRef();
    int& idtfPosRef();
    QString& scsIdRef();
    /**@}*/

private:
    QSharedDataPointer<SCgNodeInfoData> d;
};


class SCgPairInfo: public SCgObjectInfo
{
public:
    explicit SCgPairInfo(const SCgPair* obj);

    SCgPairInfo(const SCgPairInfo &other);

    SCgPairInfo();

    virtual ~SCgPairInfo();

    /**
     * \defgroup readAccess Read Access Functions
     * @{
     */
    virtual int objectType() const;

    const QVector<QPointF>& points() const;
    const QString& beginObjectId() const;
    const QString& endObjectId() const;
    double beginDot() const;
    double endDot() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QVector<QPointF>& pointsRef();
    QString& beginObjectIdRef();
    QString& endObjectIdRef();
    double& beginDotRef();
    double& endDotRef();
    /**@}*/

private:
    QSharedDataPointer<SCgPairInfoData> d;
};



class SCgContourInfo: public SCgObjectInfo
{
public:
    explicit SCgContourInfo(const SCgContour* obj);

    SCgContourInfo(const SCgContourInfo &other);

    SCgContourInfo();

    virtual ~SCgContourInfo();

    /**
     * \defgroup readAccess Read Access Functions
     * @{
     */
    virtual int objectType() const;

    QPointF pos() const;
    const QVector<QPointF>& points() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QVector<QPointF>& pointsRef();
    QPointF& posRef();
    /**@}*/

private:
    QSharedDataPointer<SCgContourInfoData> d;

};



class SCgBusInfo: public SCgObjectInfo
{
public:
    explicit SCgBusInfo(const SCgBus* obj);

    SCgBusInfo(const SCgBusInfo &other);

    SCgBusInfo();
    virtual ~SCgBusInfo();

    /**
     * \defgroup readAccess Read Access Functions
     * @{
     */
    virtual int objectType() const;

    const QVector<QPointF>& points() const;
    const QString& ownerId() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QVector<QPointF>& pointsRef();
    QString& ownerIdRef();
    /**@}*/

private:
    QSharedDataPointer<SCgBusInfoData> d;

};

