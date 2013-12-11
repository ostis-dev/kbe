#include "scsobjectinforeader.h"
#include "../scg/gwf/parser/scsparserast.h"
#include "scgobjectsinfo.h"
#include "scgnode.h"
#include "scgpair.h"
#include <memory>
#include <QList>
#include <QStringList>
#include <QDebug>

ScsObjectInfoReader::ScsObjectInfoReader()
{

}

ScsObjectInfoReader::~ScsObjectInfoReader()
{

}

bool ScsObjectInfoReader::read(QString fileName)
{
    mFileName = fileName;
    //create parser
    ScsParserAST parser;
    //build AST
    parser.buildTree(mFileName);
    //run parser
    if(!parser.parse(&stringFirstLevelInfo))
        return false;

    if(!stringFirstLevelInfo.isEmpty())
    {
        for(int i=0; i<stringFirstLevelInfo.size(); i++)
        {
            QStringList temp = stringFirstLevelInfo[i];
            if(!parseNodes(temp))
                return false;

            if(!parsePairs(temp))
                return false;
        }
    }


    return true;
}

bool ScsObjectInfoReader::parseNodes(QStringList temp)
{
    //check if 1 and 3 element is nodes
    int counter;
    if(!checkIdAndType(temp[0]) && !checkIdAndType(temp[2]))
        counter = 2;
    else
        counter = 1;

    for(int i=0; i<counter; i++)
    {
        std::auto_ptr<SCgNodeInfo> nodeInfo(new SCgNodeInfo());
        SCgObjectInfo *info = nodeInfo.get();

        //id to idtf structure
        id2Idtf idIdtf;

        //getting type and idtf after antlr-parser generated string
        QString typeString, idtfString, inputString;
        if(i == 0)
            inputString = temp[0];
        else
            inputString = temp[2];
        if(!getIdAndType(&typeString,&idtfString,inputString))
        {
            info->typeAliasRef() = "node/const/general";
            info->idtfValueRef() = idtfString;
            idIdtf.idtf = idtfString;
        }
        else
        {
            //temporary solution (Needs type to alias map)
            //info->typeAliasRef() = typeString;
            info->typeAliasRef() = "node/const/general";
            info->idtfValueRef() = idtfString;
            idIdtf.idtf = idtfString;
        }

        //id
        info->idRef() = QString::number(idElement);
        idIdtf.id = idElement;
        idElement++;

        //parent contour
        info->parentIdRef() = "0";

        //position on scg graphical window
        nodeInfo->posRef().rx() = qrand() % 600;
        nodeInfo->posRef().ry() = qrand() % 600;

        //idtf position
        nodeInfo->idtfPosRef() = 0;

        //content type
        nodeInfo->contentTypeRef() = 0;

        //mime
        nodeInfo->contentMimeTypeRef() = "";

        //visible
        nodeInfo->contentVisibleRef() = false;

        if(!structContains(info->idtfValueRef()))
        {
            listIdIdtf.append(idIdtf);
            mObjectsInfo[SCgNode::Type].append(nodeInfo.release());
        }
    }
    return true;
}

bool ScsObjectInfoReader::parsePairs(QStringList temp)
{    
    std::auto_ptr<SCgPairInfo> pairInfo(new SCgPairInfo());
    SCgObjectInfo *info = pairInfo.get();

    id2Idtf idIdtf;

    //getting type and idtf after antlr-parser generated string
    QString typeString, idtfString;

    if(!getIdAndType(&typeString,&idtfString,temp[1]))
    {
        //temporary solution (Needs type to alias map)
        //info->typeAliasRef() = typeString;
        info->typeAliasRef() = "pair/const/pos/perm/orient/accessory";
        info->idtfValueRef() = idtfString;
        idIdtf.idtf = idtfString;
    }
    else
    {
        //temporary solution (Needs type to alias map)
        if(typeString == "sc_arc_common")
            info->typeAliasRef() = "pair/const/-/-/orient";
        else
            info->typeAliasRef() = "pair/const/pos/perm/orient/accessory";
        info->idtfValueRef() = idtfString;
        idIdtf.idtf = idtfString;
    }

    //id
    info->idRef() = QString::number(idElement);
    idIdtf.id = idElement;
    idElement++;

    //parent contour
    info->parentIdRef() = "0";

    //begin and end
    QStringList beginEnd = getPairBeginEnd(temp);
    pairInfo->beginObjectIdRef() = beginEnd[0];
    pairInfo->endObjectIdRef() = beginEnd[1];

    //touch position
    pairInfo->beginDotRef() = 0;
    pairInfo->endDotRef() = 0.5;

    //points (null)
    pairInfo->pointsRef().push_back(QPointF());
    pairInfo->pointsRef().push_back(QPointF());

    listIdIdtf.append(idIdtf);

    mObjectsInfo[SCgPair::Type].append(pairInfo.release());

    return true;
}

bool ScsObjectInfoReader::getIdAndType(QString *type, QString *idtf, QString str)
{
    if(str.contains("#"))
    {
        int i=0;
        while(str[i]!='#')
        {
            type->append(str[i]);
            i++;
        }
        i++;
        for(i;i<str.length();i++)
            idtf->append(str[i]);
        return true;
    }
    else
    {
        for(int i=0; i<str.length(); i++)
            idtf->append(str[i]);
        return false;
    }

}

bool ScsObjectInfoReader::checkIdAndType(QString str)
{
    if(str.contains("#"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QStringList ScsObjectInfoReader::getPairBeginEnd(QStringList str)
{
    QStringList beginEnd;
    QString type1, idtf1, type2, idtf2, begin, end;
    getIdAndType(&type1,&idtf1,str[0]);
    getIdAndType(&type2,&idtf2,str[2]);

    for(int i=0; i<listIdIdtf.size(); i++)
    {
        if(listIdIdtf[i].idtf == idtf1)
            begin = QString::number(listIdIdtf[i].id);
        if(listIdIdtf[i].idtf == idtf2)
            end = QString::number(listIdIdtf[i].id);
    }

    beginEnd.append(begin);
    beginEnd.append(end);

    return beginEnd;
}

bool ScsObjectInfoReader::structContains(QString str)
{
    for(int i=0; i<listIdIdtf.size(); i++)
    {
        if(listIdIdtf[i].idtf == str)
            return true;
    }
    return false;
}
