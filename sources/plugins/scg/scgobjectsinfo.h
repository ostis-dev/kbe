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

#ifndef SCGOBJECTINFO_H_
#define SCGOBJECTINFO_H_

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
    int idtfSize() const;
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
    int& idtfSizeRef();
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

    const QVector<QPointF>& points() const;
    /**@}*/

    /**
     * \defgroup r_wFunctions Read/Write Access Functions
     * Causes deep data copy
     * @{
     */
    QVector<QPointF>& pointsRef();
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

#endif /* SCGOBJECTINFO_H_ */
