/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "gwfobjectinforeader.h"

#include <memory>

#include "scgobjectsinfo.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgcontour.h"
#include "scgpair.h"

GwfObjectInfoReader::GwfObjectInfoReader(bool isOwner) :
    mIsOwner(isOwner),
    mVersion(qMakePair(0, 0))
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
    mGWFType2TypeAlias["node/-/-/not_define"] = "node/-/-/not_define";

    //const perm
    mGWFType2TypeAlias["node/const/perm/general"] = "node/const/perm/general";
    mGWFType2TypeAlias["node/const/perm/terminal"] = "node/const/perm/terminal";
    mGWFType2TypeAlias["node/const/perm/struct"] = "node/const/perm/struct";
    mGWFType2TypeAlias["node/const/perm/tuple"] = "node/const/perm/tuple";
    mGWFType2TypeAlias["node/const/perm/role"] = "node/const/perm/role";
    mGWFType2TypeAlias["node/const/perm/relation"] = "node/const/perm/relation";
    mGWFType2TypeAlias["node/const/perm/group"] = "node/const/perm/group";
    mGWFType2TypeAlias["node/const/perm/super_group"] = "node/const/perm/super_group";

    //var perm
    mGWFType2TypeAlias["node/var/perm/general"] = "node/var/perm/general";
    mGWFType2TypeAlias["node/var/perm/terminal"] = "node/var/perm/terminal";
    mGWFType2TypeAlias["node/var/perm/struct"] = "node/var/perm/struct";
    mGWFType2TypeAlias["node/var/perm/tuple"] = "node/var/perm/tuple";
    mGWFType2TypeAlias["node/var/perm/role"] = "node/var/perm/role";
    mGWFType2TypeAlias["node/var/perm/relation"] = "node/var/perm/relation";
    mGWFType2TypeAlias["node/var/perm/group"] = "node/var/perm/group";
    mGWFType2TypeAlias["node/var/perm/super_group"] = "node/var/perm/super_group";

    //meta perm
    mGWFType2TypeAlias["node/meta/perm/general"] = "node/meta/perm/general";
    mGWFType2TypeAlias["node/meta/perm/terminal"] = "node/meta/perm/terminal";
    mGWFType2TypeAlias["node/meta/perm/struct"] = "node/meta/perm/struct";
    mGWFType2TypeAlias["node/meta/perm/tuple"] = "node/meta/perm/tuple";
    mGWFType2TypeAlias["node/meta/perm/role"] = "node/meta/perm/role";
    mGWFType2TypeAlias["node/meta/perm/relation"] = "node/meta/perm/relation";
    mGWFType2TypeAlias["node/meta/perm/group"] = "node/meta/perm/group";
    mGWFType2TypeAlias["node/meta/perm/super_group"] = "node/meta/perm/super_group";

    //const temp
    mGWFType2TypeAlias["node/const/temp/general"] = "node/const/temp/general";
    mGWFType2TypeAlias["node/const/temp/terminal"] = "node/const/temp/terminal";
    mGWFType2TypeAlias["node/const/temp/struct"] = "node/const/temp/struct";
    mGWFType2TypeAlias["node/const/temp/tuple"] = "node/const/temp/tuple";
    mGWFType2TypeAlias["node/const/temp/role"] = "node/const/temp/role";
    mGWFType2TypeAlias["node/const/temp/relation"] = "node/const/temp/relation";
    mGWFType2TypeAlias["node/const/temp/group"] = "node/const/temp/group";
    mGWFType2TypeAlias["node/const/temp/super_group"] = "node/const/temp/super_group";

    //var temp
    mGWFType2TypeAlias["node/var/temp/general"] = "node/var/temp/general";
    mGWFType2TypeAlias["node/var/temp/terminal"] = "node/var/temp/terminal";
    mGWFType2TypeAlias["node/var/temp/struct"] = "node/var/temp/struct";
    mGWFType2TypeAlias["node/var/temp/tuple"] = "node/var/temp/tuple";
    mGWFType2TypeAlias["node/var/temp/role"] = "node/var/temp/role";
    mGWFType2TypeAlias["node/var/temp/relation"] = "node/var/temp/relation";
    mGWFType2TypeAlias["node/var/temp/group"] = "node/var/temp/group";
    mGWFType2TypeAlias["node/var/temp/super_group"] = "node/var/temp/super_group";

    //meta temp
    mGWFType2TypeAlias["node/meta/temp/general"] = "node/meta/temp/general";
    mGWFType2TypeAlias["node/meta/temp/terminal"] = "node/meta/temp/terminal";
    mGWFType2TypeAlias["node/meta/temp/struct"] = "node/meta/temp/struct";
    mGWFType2TypeAlias["node/meta/temp/tuple"] = "node/meta/temp/tuple";
    mGWFType2TypeAlias["node/meta/temp/role"] = "node/meta/temp/role";
    mGWFType2TypeAlias["node/meta/temp/relation"] = "node/meta/temp/relation";
    mGWFType2TypeAlias["node/meta/temp/group"] = "node/meta/temp/group";
    mGWFType2TypeAlias["node/meta/temp/super_group"] = "node/meta/temp/super_group";

    // pairs
    mGWFType2TypeAlias["pair/-/-/-/noorient"] = "pair/-/-/-/noorient";
    mGWFType2TypeAlias["pair/-/-/-/orient"] = "pair/-/-/-/orient";

    //const
    mGWFType2TypeAlias["pair/const/-/perm/noorien"] = "pair/const/-/perm/noorien";
    mGWFType2TypeAlias["pair/const/-/perm/orient"] = "pair/const/-/perm/orient";
    mGWFType2TypeAlias["pair/const/-/temp/noorien"] = "pair/const/-/temp/noorien";
    mGWFType2TypeAlias["pair/const/-/temp/orient"] = "pair/const/-/temp/orient";
    mGWFType2TypeAlias["pair/const/pos/perm/orient/membership"] = "pair/const/pos/perm/orient/membership";
    mGWFType2TypeAlias["pair/const/neg/perm/orient/membership"] = "pair/const/neg/perm/orient/membership";
    mGWFType2TypeAlias["pair/const/fuz/perm/orient/membership"] = "pair/const/fuz/perm/orient/membership";
    mGWFType2TypeAlias["pair/const/pos/temp/orient/membership"] = "pair/const/pos/temp/orient/membership";
    mGWFType2TypeAlias["pair/const/neg/temp/orient/membership"] = "pair/const/neg/temp/orient/membership";
    mGWFType2TypeAlias["pair/const/fuz/temp/orient/membership"] = "pair/const/fuz/temp/orient/membership";

    //var
    mGWFType2TypeAlias["pair/var/-/perm/noorien"] = "pair/var/-/perm/noorien";
    mGWFType2TypeAlias["pair/var/-/perm/orient"] = "pair/var/-/perm/orient";
    mGWFType2TypeAlias["pair/var/-/temp/noorien"] = "pair/var/-/temp/noorien";
    mGWFType2TypeAlias["pair/var/-/temp/orient"] = "pair/var/-/temp/orient";
    mGWFType2TypeAlias["pair/var/pos/perm/orient/membership"] = "pair/var/pos/perm/orient/membership";
    mGWFType2TypeAlias["pair/var/neg/perm/orient/membership"] = "pair/var/neg/perm/orient/membership";
    mGWFType2TypeAlias["pair/var/fuz/perm/orient/membership"] = "pair/var/fuz/perm/orient/membership";
    mGWFType2TypeAlias["pair/var/pos/temp/orient/membership"] = "pair/var/pos/temp/orient/membership";
    mGWFType2TypeAlias["pair/var/neg/temp/orient/membership"] = "pair/var/neg/temp/orient/membership";
    mGWFType2TypeAlias["pair/var/fuz/temp/orient/membership"] = "pair/var/fuz/temp/orient/membership";

    //meta
    mGWFType2TypeAlias["pair/meta/-/perm/noorien"] = "pair/meta/-/perm/noorien";
    mGWFType2TypeAlias["pair/meta/-/perm/orient"] = "pair/meta/-/perm/orient";
    mGWFType2TypeAlias["pair/meta/-/temp/noorien"] = "pair/meta/-/temp/noorien";
    mGWFType2TypeAlias["pair/meta/-/temp/orient"] = "pair/meta/-/temp/orient";
    mGWFType2TypeAlias["pair/meta/pos/perm/orient/membership"] = "pair/meta/pos/perm/orient/membership";
    mGWFType2TypeAlias["pair/meta/neg/perm/orient/membership"] = "pair/meta/neg/perm/orient/membership";
    mGWFType2TypeAlias["pair/meta/fuz/perm/orient/membership"] = "pair/meta/fuz/perm/orient/membership";
    mGWFType2TypeAlias["pair/meta/pos/temp/orient/membership"] = "pair/meta/pos/temp/orient/membership";
    mGWFType2TypeAlias["pair/meta/neg/temp/orient/membership"] = "pair/meta/neg/temp/orient/membership";
    mGWFType2TypeAlias["pair/meta/fuz/temp/orient/membership"] = "pair/meta/fuz/temp/orient/membership";

    // contour
    mGWFType2TypeAlias["contour/const/perm"] = "contour/const/perm";
    mGWFType2TypeAlias["contour/var/perm"] = "contour/var/perm";
    mGWFType2TypeAlias["contour/const/temp"] = "contour/const/temp";
    mGWFType2TypeAlias["contour/var/temp"] = "contour/var/temp";

    //deprecated. For supporting old format.
    // nodes
    mGWFType2TypeAlias["node/-/not_define"] = "node/-/-/not_define";

    mGWFType2TypeAlias["node/const/not_define"] = "node/-/-/not_define";
    mGWFType2TypeAlias["node/const/general_node"] = "node/const/perm/general";
    mGWFType2TypeAlias["node/const/predmet"] = "node/const/perm/general";
    mGWFType2TypeAlias["node/const/terminal"] = "node/const/perm/terminal";
    mGWFType2TypeAlias["node/const/nopredmet"] = "node/const/perm/struct";
    mGWFType2TypeAlias["node/const/symmetry"] = "node/const/perm/tuple";
    mGWFType2TypeAlias["node/const/asymmetry"] = "node/const/perm/tuple";
    mGWFType2TypeAlias["node/const/attribute"] = "node/const/perm/role";
    mGWFType2TypeAlias["node/const/relation"] = "node/const/perm/relation";
    mGWFType2TypeAlias["node/const/atom"] = "node/const/perm/group";
    mGWFType2TypeAlias["node/const/group"] = "node/const/perm/group";

    mGWFType2TypeAlias["node/var/not_define"] = "node/-/-/not_define";
    mGWFType2TypeAlias["node/var/general_node"] = "node/var/perm/general";
    mGWFType2TypeAlias["node/var/predmet"] = "node/var/perm/general";
    mGWFType2TypeAlias["node/var/terminal"] = "node/var/perm/terminal";
    mGWFType2TypeAlias["node/var/nopredmet"] = "node/var/perm/struct";
    mGWFType2TypeAlias["node/var/symmetry"] = "node/var/perm/tuple";
    mGWFType2TypeAlias["node/var/asymmetry"] = "node/var/perm/tuple";
    mGWFType2TypeAlias["node/var/attribute"] = "node/var/perm/role";
    mGWFType2TypeAlias["node/var/relation"] = "node/var/perm/relation";
    mGWFType2TypeAlias["node/var/atom"] = "node/var/perm/group";
    mGWFType2TypeAlias["node/var/group"] = "node/var/perm/group";

    mGWFType2TypeAlias["node/meta/not_define"] = "node/-/-/not_define";
    mGWFType2TypeAlias["node/meta/general_node"] = "node/var/perm/general";
    mGWFType2TypeAlias["node/meta/predmet"] = "node/var/perm/abstract";
    mGWFType2TypeAlias["node/meta/nopredmet"] = "node/var/perm/struct";
    mGWFType2TypeAlias["node/meta/symmetry"] = "node/var/perm/tuple";
    mGWFType2TypeAlias["node/meta/asymmetry"] = "node/var/perm/tuple";
    mGWFType2TypeAlias["node/meta/attribute"] = "node/var/perm/role";
    mGWFType2TypeAlias["node/meta/relation"] = "node/var/perm/relation";
    mGWFType2TypeAlias["node/meta/atom"] = "node/var/perm/group";
    mGWFType2TypeAlias["node/meta/group"] = "node/var/perm/group";

    // pairs
    mGWFType2TypeAlias["arc/-/-"] = "pair/-/-/-/orient/membership";
    mGWFType2TypeAlias["pair/noorient"] = "pair/-/-/-/noorient";
    mGWFType2TypeAlias["pair/orient"] = "pair/-/-/-/orient";

    mGWFType2TypeAlias["arc/const/pos"] = "pair/const/pos/perm/orient/membership";
    mGWFType2TypeAlias["arc/var/pos"] = "pair/var/pos/perm/orient/membership";
    mGWFType2TypeAlias["arc/meta/pos"] = "pair/var/pos/perm/orient/membership";

    mGWFType2TypeAlias["arc/const/neg"] = "pair/const/neg/perm/orient/membership";
    mGWFType2TypeAlias["arc/var/neg"] = "pair/var/neg/perm/orient/membership";
    mGWFType2TypeAlias["arc/meta/neg"] = "pair/var/neg/perm/orient/membership";

    mGWFType2TypeAlias["arc/const/fuz"] = "pair/const/fuz/perm/orient/membership";
    mGWFType2TypeAlias["arc/var/fuz"] = "pair/var/fuz/perm/orient/membership";
    mGWFType2TypeAlias["arc/meta/fuz"] = "pair/var/fuz/perm/orient/membership";

    mGWFType2TypeAlias["arc/const/pos/temp"] = "pair/const/pos/temp/orient/membership";
    mGWFType2TypeAlias["arc/var/pos/temp"] = "pair/var/pos/temp/orient/membership";
    mGWFType2TypeAlias["arc/meta/pos/temp"] = "pair/var/pos/temp/orient/membership";

    mGWFType2TypeAlias["arc/const/neg/temp"] = "pair/const/neg/temp/orient/membership";
    mGWFType2TypeAlias["arc/var/neg/temp"] = "pair/var/neg/temp/orient/membership";
    mGWFType2TypeAlias["arc/meta/neg/temp"] = "pair/var/neg/temp/orient/membership";

    mGWFType2TypeAlias["arc/const/fuz/temp"] = "pair/const/fuz/temp/orient/membership";
    mGWFType2TypeAlias["arc/var/fuz/temp"] = "pair/var/fuz/temp/orient/membership";
    mGWFType2TypeAlias["arc/meta/fuz/temp"] = "pair/var/fuz/temp/orient/membership";

    mGWFType2TypeAlias["pair/const/synonym"] = "pair/const/-/perm/noorien";
    mGWFType2TypeAlias["pair/var/noorient"] = "pair/var/-/perm/noorien";
    mGWFType2TypeAlias["pair/meta/noorient"] = "pair/var/-/perm/noorien";

    mGWFType2TypeAlias["pair/const/orient"] = "pair/const/-/perm/orient";
    mGWFType2TypeAlias["pair/var/orient"] = "pair/var/-/perm/orient";
    mGWFType2TypeAlias["pair/meta/orient"] = "pair/var/-/perm/orient";

    mGWFType2TypeAlias["pair/rail/noorient"] = "pair/var/-/perm/noorien";
    mGWFType2TypeAlias["pair/rail/orient"] = "pair/var/-/perm/orient";
    mGWFType2TypeAlias["pair/rail2/noorient"] = "pair/var/-/perm/noorien";
    mGWFType2TypeAlias["pair/rail2/orient"] = "pair/var/-/perm/orient";
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
    {
        QStringList v_list = root.attribute("version").split(".");
        mVersion.first = v_list.first().toInt();
        mVersion.second = v_list.last().toInt();
        if (mVersion != qMakePair(1, 6) && mVersion != qMakePair(2, 0))
        {
            mLastError = QString(QObject::tr("Version %1 of GWF files not supported.\n"
                                        "Just 1.6 and 2.0 versions supported.")).arg(root.attribute("version"));
            return false;
        }
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
    if(info->objectType() == SCgPair::Type || info->objectType() == SCgNode::Type || info->objectType() == SCgContour::Type)
    {
        QString& type = info->typeAliasRef();
        if (getAttributeString(element, "type", type))
        {
            //this condition is necessary for compatibility with old formats
            if (type == "" && info->objectType() == SCgContour::Type) {
                type = "contour/const/perm";
            }
            if (!mGWFType2TypeAlias.contains(type))
            {
                errorUnknownElementType(element.tagName(), type);
                return false;
            }else {
                type = mGWFType2TypeAlias[type];
            }
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

    if(!parseObject(element, nodeInfo.get()))
        return false;

    qreal& x = nodeInfo->posRef().rx();
    qreal& y = nodeInfo->posRef().ry();
    if (!getAttributeDouble(element, "x", x) || !getAttributeDouble(element, "y", y))
        return false;


    // get identifier position
    int& idtfPos = nodeInfo->idtfPosRef();
    if (!getAttributeInt(element, "idtf_pos", idtfPos))
        idtfPos = 0;

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

    // in old versions format, there wasn't content_visibility attribute, so we need to check if it exists
    if (contEl.hasAttribute("content_visibility") && !getAttributeBool(contEl, "content_visibility", nodeInfo->contentVisibleRef()))
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

    if(!parseObject(element, contourInfo.get()))
        return false;

    if (!getElementPoints(element, contourInfo->pointsRef()))
        return false;

        qreal& idtfPosX = contourInfo->posRef().rx();
        qreal& idtfPosY = contourInfo->posRef().ry();
        if (!getAttributeDouble(element, "idtf_pos_x", idtfPosX))
            idtfPosX = 0;
        if (!getAttributeDouble(element, "idtf_pos_y", idtfPosY))
            idtfPosY = 0;

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

bool GwfObjectInfoReader::getAttributeBool(const QDomElement &element, QString attribute, bool &result)
{
    QString strResult;
    if (!getAttributeString(element, attribute, strResult))
        return false;
    else
        if (strResult == "false")
            result = false;
        else if (strResult == "true")
            result = true;
        else
        {
            errorBoolParse(element.tagName(), attribute);
            return false;
        }
    return true;
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

void GwfObjectInfoReader::errorBoolParse(QString element, QString attribute)
{
    mLastError = QObject::tr("invalid bollean value in attribute '%1' of element '%2'").arg(attribute).arg(element);
}

void GwfObjectInfoReader::errorHaventContent(QString element)
{
    mLastError = QObject::tr("node element '%1' haven't content tag").arg(element);
}

void GwfObjectInfoReader::errorUnknownElementType(QString element, QString type)
{
    mLastError = QObject::tr("type '%1' is unknown for element '%2'").arg(type).arg(element);
}
