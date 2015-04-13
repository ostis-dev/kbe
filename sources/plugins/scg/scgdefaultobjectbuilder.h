/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgabstractobjectbuilder.h"

class SCgNodeInfo;
class SCgPairInfo;
class SCgBusInfo;
class SCgContourInfo;

//! @see AbstractSCgObjectBuilder.
//! Simple create and place objects to scene.
class DefaultSCgObjectBuilder: public AbstractSCgObjectBuilder
{
public:
    DefaultSCgObjectBuilder(QGraphicsScene* scene);
    virtual ~DefaultSCgObjectBuilder();

    void buildObjects(const TypeToObjectsMap& objects);

    QList<SCgObject*> objects()const
    {
        return mId2SCgObj.values();
    }

    bool hasErrors() const
    {
        return !mErrors.empty();
    }

    const QStringList& errorList()const
    {
        return mErrors;
    }

protected:
    typedef QMap<QString, SCgObject*> Id2SCgObjMap;
    //! Map for elements id mapping
    Id2SCgObjMap mId2SCgObj;

    typedef QMap<QString, QString> ParentChildMap;
    //! Map for store parent-child  relationship
    ParentChildMap mParentChild;

    /*! Sets up some object info (typeAlias, Idtf), store mapping information
     * and adding object to scene.
     * @param obj Processing object
     * @param info Object attributes
     */
    void setObjectInfo(SCgObject* obj, SCgObjectInfo* info);

    void buildNode(SCgNodeInfo* info);
    void buildPair(SCgPairInfo* info);
    void buildBus(SCgBusInfo* info);
    void buildContour(SCgContourInfo* info);

    QStringList mErrors;
    QGraphicsScene* mScene;
};


