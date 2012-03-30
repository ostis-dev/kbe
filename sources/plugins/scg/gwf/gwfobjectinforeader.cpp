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


#include "gwfobjectinforeader.h"

#include <memory>

#include "../scgobjectsinfo.h"
#include "../scgnode.h"
#include "../scgbus.h"
#include "../scgcontour.h"
#include "../scgpair.h"

GwfObjectInfoReader::GwfObjectInfoReader(bool isOwner):mIsOwner(isOwner)
{
    createTypesMap();
}

GwfObjectInfoReader::GwfObjectInfoReader(const QDomDocument& document, bool isOwner):
                                                        mIsOwner(isOwner)
{
    createTypesMap();
    read(document);
}

GwfObjectInfoReader::~GwfObjectInfoReader()
{
    if (mIsOwner)
        del();
}

void GwfObjectInfoReader::del()
{
    TypeToObjectsMap::iterator it = mObjectsInfo.begin();
    ObjectInfoList::iterator itList;

    for(;it != mObjectsInfo.end(); ++it)
    {
        for(itList = it.value().begin(); itList != it.value().end(); ++itList)
            delete *itList;
        it.value().clear();
    }
    mObjectsInfo.clear();
}

void GwfObjectInfoReader::createTypesMap()
{
    // initialize types mapping

    // nodes
    mGWFType2TypeAlias["node/const/not_define"] = "node/const/not_define";
    mGWFType2TypeAlias["node/const/general_node"] = "node/const/general_node";
    mGWFType2TypeAlias["node/const/predmet"] = "node/const/predmet";
    mGWFType2TypeAlias["node/const/nopredmet"] = "node/const/nopredmet";
    mGWFType2TypeAlias["node/const/symmetry"] = "node/const/symmetry";
    mGWFType2TypeAlias["node/const/asymmetry"] = "node/const/asymmetry";
    mGWFType2TypeAlias["node/const/attribute"] = "node/const/attribute";
    mGWFType2TypeAlias["node/const/relation"] = "node/const/relation";
    mGWFType2TypeAlias["node/const/atom"] = "node/const/atom";
    mGWFType2TypeAlias["node/const/group"] = "node/const/group";

    mGWFType2TypeAlias["node/var/not_define"] = "node/var/not_define";
    mGWFType2TypeAlias["node/var/general_node"] = "node/var/general_node";
    mGWFType2TypeAlias["node/var/predmet"] = "node/var/predmet";
    mGWFType2TypeAlias["node/var/nopredmet"] = "node/var/nopredmet";
    mGWFType2TypeAlias["node/var/symmetry"] = "node/var/symmetry";
    mGWFType2TypeAlias["node/var/asymmetry"] = "node/var/asymmetry";
    mGWFType2TypeAlias["node/var/attribute"] = "node/var/attribute";
    mGWFType2TypeAlias["node/var/relation"] = "node/var/relation";
    mGWFType2TypeAlias["node/var/atom"] = "node/var/atom";
    mGWFType2TypeAlias["node/var/group"] = "node/var/group";

    mGWFType2TypeAlias["node/meta/not_define"] = "node/meta/not_define";
    mGWFType2TypeAlias["node/meta/general_node"] = "node/meta/general_node";
    mGWFType2TypeAlias["node/meta/predmet"] = "node/meta/predmet";
    mGWFType2TypeAlias["node/meta/nopredmet"] = "node/meta/nopredmet";
    mGWFType2TypeAlias["node/meta/symmetry"] = "node/meta/symmetry";
    mGWFType2TypeAlias["node/meta/asymmetry"] = "node/meta/asymmetry";
    mGWFType2TypeAlias["node/meta/attribute"] = "node/meta/attribute";
    mGWFType2TypeAlias["node/meta/relation"] = "node/meta/relation";
    mGWFType2TypeAlias["node/meta/atom"] = "node/meta/atom";
    mGWFType2TypeAlias["node/meta/group"] = "node/meta/group";

    // pairs
    mGWFType2TypeAlias["arc/-/-"] = "pair/-/-/-/orient/accessory";
    mGWFType2TypeAlias["pair/noorient"] = "pair/-/-/-/noorien";
    mGWFType2TypeAlias["pair/orient"] = "pair/-/-/-/orient";

    mGWFType2TypeAlias["arc/const/pos"] = "pair/const/pos/perm/orient/accessory";
    mGWFType2TypeAlias["arc/var/pos"] = "pair/var/pos/perm/orient/accessory";
    mGWFType2TypeAlias["arc/meta/pos"] = "pair/meta/pos/perm/orient/accessory";

    mGWFType2TypeAlias["arc/const/neg"] = "pair/const/neg/perm/orient/accessory";
    mGWFType2TypeAlias["arc/var/neg"] = "pair/var/neg/perm/orient/accessory";
    mGWFType2TypeAlias["arc/meta/neg"] = "pair/meta/neg/perm/orient/accessory";

    mGWFType2TypeAlias["arc/const/fuz"] = "pair/const/fuz/perm/orient/accessory";
    mGWFType2TypeAlias["arc/var/fuz"] = "pair/var/fuz/perm/orient/accessory";
    mGWFType2TypeAlias["arc/meta/fuz"] = "pair/meta/fuz/perm/orient/accessory";

    mGWFType2TypeAlias["arc/const/pos/temp"] = "pair/const/pos/temp/orient/accessory";
    mGWFType2TypeAlias["arc/var/pos/temp"] = "pair/var/pos/temp/orient/accessory";
    mGWFType2TypeAlias["arc/meta/pos/temp"] = "pair/meta/pos/temp/orient/accessory";

    mGWFType2TypeAlias["arc/const/neg/temp"] = "pair/const/neg/temp/orient/accessory";
    mGWFType2TypeAlias["arc/var/neg/temp"] = "pair/var/neg/temp/orient/accessory";
    mGWFType2TypeAlias["arc/meta/neg/temp"] = "pair/meta/neg/temp/orient/accessory";

    mGWFType2TypeAlias["arc/const/fuz/temp"] = "pair/const/fuz/temp/orient/accessory";
    mGWFType2TypeAlias["arc/var/fuz/temp"] = "pair/var/fuz/temp/orient/accessory";
    mGWFType2TypeAlias["arc/meta/fuz/temp"] = "pair/meta/fuz/temp/orient/accessory";

    mGWFType2TypeAlias["pair/const/synonym"] = "pair/const/-/-/noorien";
    mGWFType2TypeAlias["pair/var/noorient"] = "pair/var/-/-/noorien";
    mGWFType2TypeAlias["pair/meta/noorient"] = "pair/meta/-/-/noorien";

    mGWFType2TypeAlias["pair/const/orient"] = "pair/const/-/-/orient";
    mGWFType2TypeAlias["pair/var/orient"] = "pair/var/-/-/orient";
    mGWFType2TypeAlias["pair/meta/orient"] = "pair/meta/-/-/orient";

    //deprecated. For supporting old format.
    mGWFType2TypeAlias["pair/rail/noorient"] = "pair/var/-/-/noorien";
    mGWFType2TypeAlias["pair/rail/orient"] = "pair/var/-/-/orient";
    mGWFType2TypeAlias["pair/rail2/noorient"] = "pair/meta/-/-/noorien";
    mGWFType2TypeAlias["pair/rail2/orient"] = "pair/meta/-/-/orient";
}

bool GwfObjectInfoReader::read(const QDomDocument& document)
{
    if (mIsOwner)
        del();
    mLastError.clear();

    QDomElement root = document.documentElement();

    if (root.tagName() != "GWF")
    {
        mLastError = QString(QObject::tr("Given document has unsupported format %1").arg(root.tagName()));
        return false;
    }
    else
        if (root.hasAttribute("version") && root.attribute("version") != "1.6")
        {
            mLastError = QString(QObject::tr("Version %1 of GWF files not supported.\n"
                                        "Just version 1.6 supported.")).arg(root.attribute("version"));
            return false;
        }

    // get static sector
    QDomElement staticSector = root.firstChildElement("staticSector");

    // parse nodes
    QDomElement element = staticSector.firstChildElement("node");
    while (!element.isNull())
    {
        if (!parseNode(element))
            return false;

        element = element.nextSiblingElement("node");
    }

    // parse arcs
    element = staticSector.firstChildElement("arc");
    while (!element.isNull())
    {
        if (!parsePair(element))
            return false;

        element = element.nextSiblingElement("arc");
    }

    // parse pairs
    element = staticSector.firstChildElement("pair");
    while (!element.isNull())
    {
        if (!parsePair(element))
            return false;

        element = element.nextSiblingElement("pair");
    }

    // parse bus
    element = staticSector.firstChildElement("bus");
    while (!element.isNull())
    {
        if (!parseBus(element))
            return false;

        element = element.nextSiblingElement("bus");
    }

    // parse contour
    element = staticSector.firstChildElement("contour");
    while (!element.isNull())
    {
        if (!parseContour(element))
            return false;

        element = element.nextSiblingElement("contour");
    }
    return true;
}

bool GwfObjectInfoReader::parseObject(const QDomElement &element, SCgObjectInfo* info)
{
    if(info->objectType() == SCgPair::Type || info->objectType() == SCgNode::Type)
    {
        QString& type = info->typeAliasRef();
        if (getAttributeString(element, "type", type))
        {
            if (!mGWFType2TypeAlias.contains(type))
            {
                errorUnknownElementType(element.tagName(), type);
                return false;
            }else
                type = mGWFType2TypeAlias[type];
        }
        else
            return false;
    }

    if (!getAttributeString(element, "id", info->idRef()))
        return false;

    if (!getAttributeString(element, "parent", info->parentIdRef()))
        return false;

    if (!getAttributeString(element, "idtf", info->idtfValueRef()))
        return false;

    return true;
}

bool GwfObjectInfoReader::parseNode(const QDomElement &element)
{
    std::auto_ptr<SCgNodeInfo> nodeInfo(new SCgNodeInfo());

    if(!parseObject(element,nodeInfo.get()))
        return false;

    qreal& x = nodeInfo->posRef().rx();
    qreal& y = nodeInfo->posRef().ry();
    if (!getAttributeDouble(element, "x", x) || !getAttributeDouble(element, "y", y))
        return false;

    // get content element
    QDomElement contEl = element.firstChildElement("content");
    if (contEl.isNull())
    {
        errorHaventContent(element.tagName());
        return false;
    }

    // get content type
    int& cType = nodeInfo->contentTypeRef();
    if (!getAttributeInt(contEl, "type", cType))
        return false;

    // get mime type
    if (!getAttributeString(contEl, "mime_type", nodeInfo->contentMimeTypeRef()))
        return false;

    // set content to nodeInfo
    if (cType > 0 && cType < 5)
    {
        if (cType == 1 || cType == 2 || cType == 3)
            nodeInfo->contentDataRef() = QVariant(contEl.firstChild().nodeValue());
        else if (cType == 4)
        {
            // get file name
            getAttributeString(contEl, "file_name", nodeInfo->contentFilenameRef());
            QString cData = contEl.firstChild().nodeValue();
            QByteArray arr = QByteArray::fromBase64(cData.toLocal8Bit());
            nodeInfo->contentDataRef() = QVariant(arr);
        }else
        {
            mLastError = QObject::tr("Content type '%1' doesn't supported for now").arg(cType);
            return false;
        }
    }else if (cType != 0)
    {
        mLastError = QObject::tr("Unknown content type '%1'").arg(cType);
        return false;
    }

    mObjectsInfo[SCgNode::Type].append(nodeInfo.release());
    return true;
}

bool GwfObjectInfoReader::parsePair(const QDomElement &element)
{
    std::auto_ptr<SCgPairInfo> pairInfo(new SCgPairInfo());

    if(!parseObject(element,pairInfo.get()))
        return false;

    if (!getAttributeString(element, "id_b", pairInfo->beginObjectIdRef()) ||
        !getAttributeString(element, "id_e", pairInfo->endObjectIdRef()))
        return false;

    if (!getAttributeDouble(element, "dotBBalance", pairInfo->beginDotRef()) ||
        !getAttributeDouble(element, "dotEBalance", pairInfo->endDotRef()))
        return false;

    pairInfo->pointsRef().push_back(QPointF());
    if (!getElementPoints(element, pairInfo->pointsRef()))
        return false;
    pairInfo->pointsRef().push_back(QPointF());

    mObjectsInfo[SCgPair::Type].append(pairInfo.release());
    return true;
}

bool GwfObjectInfoReader::parseBus(const QDomElement &element)
{
    std::auto_ptr<SCgBusInfo> busInfo(new SCgBusInfo());

    if(!parseObject(element,busInfo.get()))
        return false;

    if (!getAttributeString(element, "owner", busInfo->ownerIdRef()))
        return false;

    double bx, by;
    if (!getAttributeDouble(element, "b_x", bx) || !getAttributeDouble(element, "b_y", by))
        return false;
    double ex, ey;
    if (!getAttributeDouble(element, "e_x", ex) || !getAttributeDouble(element, "e_y", ey))
        return false;

    busInfo->pointsRef().append(QPointF(bx, by));

    if (!getElementPoints(element, busInfo->pointsRef()))
        return false;

    busInfo->pointsRef().append(QPointF(ex, ey));

    mObjectsInfo[SCgBus::Type].append(busInfo.release());
    return true;
}

bool GwfObjectInfoReader::parseContour(const QDomElement &element)
{
    std::auto_ptr<SCgContourInfo> contourInfo(new SCgContourInfo());

    if(!parseObject(element,contourInfo.get()))
        return false;

    if (!getElementPoints(element, contourInfo->pointsRef()))
        return false;

    mObjectsInfo[SCgContour::Type].append(contourInfo.release());
    return true;
}

bool GwfObjectInfoReader::getAttributeString(const QDomElement &element, QString attribute, QString &result)
{
    if (element.hasAttribute(attribute))
    {
        result = element.attribute(attribute);
        return true;
    }

    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getAttributeDouble(const QDomElement &element, QString attribute, double &result)
{
    if (element.hasAttribute(attribute))
    {
        bool res;
        result = element.attribute(attribute).toDouble(&res);

        if (!res) return false;

        return true;
    }

    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getAttributeInt(const QDomElement &element, QString attribute, int &result)
{
    if (element.hasAttribute(attribute))
    {
        bool res;
        result = element.attribute(attribute).toInt(&res);

        if (!res) return false;

        return true;
    }
    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getElementPoints(const QDomElement &element, QVector<QPointF> &result)
{
    QDomElement points = element.firstChildElement("points");
    if (points.isNull())
    {
        mLastError = QObject::tr("There are no points data for element '%1'").arg(element.tagName());
        return false;
    }

    QDomElement point = points.firstChildElement("point");
    while (!point.isNull())
    {
        double x, y;
        if (!getAttributeDouble(point, "x", x) || !getAttributeDouble(point, "y", y))
            return false;
        result.push_back(QPointF(x, y));
        point = point.nextSiblingElement("point");
    }

    return true;
}

void GwfObjectInfoReader::errorHaventAttribute(QString element, QString attribute)
{
    mLastError = QObject::tr("'%1' element haven't '%2' attribute").arg(element).arg(attribute);
}

void GwfObjectInfoReader::errorFloatParse(QString element, QString attribute)
{
    mLastError = QObject::tr("invalid float value in attribute '%1' of element '%2'").arg(attribute).arg(element);
}

void GwfObjectInfoReader::errorHaventContent(QString element)
{
    mLastError = QObject::tr("node element '%1' haven't content tag").arg(element);
}

void GwfObjectInfoReader::errorUnknownElementType(QString element, QString type)
{
    mLastError = QObject::tr("type '%1' is unknown for element '%2'").arg(type).arg(element);
}
