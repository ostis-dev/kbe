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


#ifndef DEFAULTSCGOBJECTBUILDER_H_
#define DEFAULTSCGOBJECTBUILDER_H_

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

#endif /* DEFAULTSCGOBJECTBUILDER_H_ */
