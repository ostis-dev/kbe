/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
    AbstractSCgObjectBuilder();
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


