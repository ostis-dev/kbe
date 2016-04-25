/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgabstractobjectbuilder.h"

//! @see DefaultObjectBuilder
class TemplateSCgObjectsBuilder: public AbstractSCgObjectBuilder
{
public:
    TemplateSCgObjectsBuilder(QGraphicsScene* scene);
    virtual ~TemplateSCgObjectsBuilder();

    void buildObjects(const TypeToObjectsMap& objects);

    QList<SCgObject*> objects()const;

    bool hasErrors() const;

    const QStringList& errorList()const;

protected:
    AbstractSCgObjectBuilder* mDecoratedBuilder;
};


