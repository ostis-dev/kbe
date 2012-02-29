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


#ifndef ABSTRACTSCGOBJECTBUILDER_H_
#define ABSTRACTSCGOBJECTBUILDER_H_

#include <QList>
#include <QMap>
#include <QStringList>

class QGraphicsScene;
class SCgObject;
class SCgObjectInfo;

//! Interface for building scene representation from map of SCgObjectInfo structures.
class AbstractSCgObjectBuilder
{
public:
    //! NOTE: @param scene is not used in this context.
    AbstractSCgObjectBuilder(QGraphicsScene* scene);
    virtual ~AbstractSCgObjectBuilder();

    typedef QList<SCgObjectInfo*>       ObjectInfoList;
    //! Maps object type with list of objects of this type.
    typedef QMap<int, ObjectInfoList>   TypeToObjectsMap;

    /*!
     * @return If errors occur while building return true.
     */
    virtual bool hasErrors() const = 0;

    /*!
     * @return list with occurred errors.
     */
    virtual const QStringList& errorList()const = 0;

    //! @return built objects.
    //! NOTE: should be called after buildObjects();
    virtual QList<SCgObject*> objects()const = 0;

    /*! Run build process for given map with objects (@see TypeToObjectsMap).
     * All created objects are automaticaly added on the scene.
     * @param objects specifies objects for building.
     * @return List of built objects.
     */
    virtual void buildObjects(const TypeToObjectsMap& objects) = 0;
};

#endif /* ABSTRACTSCGOBJECTBUILDER_H_ */
