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

#include "scgtemplateobjectbuilder.h"
#include "scgdefaultobjectbuilder.h"

#include "scgobject.h"
#include "scgnode.h"
#include "scgbus.h"

TemplateSCgObjectsBuilder::TemplateSCgObjectsBuilder(QGraphicsScene* scene) :
        AbstractSCgObjectBuilder(scene)
{
    mDecoratedBuilder = new DefaultSCgObjectBuilder(scene);
}

TemplateSCgObjectsBuilder::~TemplateSCgObjectsBuilder()
{
    delete mDecoratedBuilder;
}

void TemplateSCgObjectsBuilder::buildObjects(const TypeToObjectsMap& objects)
{
    mDecoratedBuilder->buildObjects(objects);
    QList<SCgObject*> l = mDecoratedBuilder->objects();

    foreach(SCgObject* obj, l)
        if(! obj->parentItem())
            obj->setDead(true);

    QRectF bounds;

    foreach(SCgObject* obj, l)
        bounds = bounds.united(obj->sceneBoundingRect());

    foreach(SCgObject* obj, l)
    {
        if(! obj->parentItem())
                obj->setPos(obj->scenePos() - bounds.topLeft());
    }

    foreach(SCgObject* obj, l)
    {
        if( obj->type() == QGraphicsItem::UserType + 3 )      // type SCgPair
            obj->positionChanged();
    }
}

QList<SCgObject*> TemplateSCgObjectsBuilder::objects()const
{
    return mDecoratedBuilder->objects();
}

bool TemplateSCgObjectsBuilder::hasErrors() const
{
    return mDecoratedBuilder->hasErrors();
}

const QStringList& TemplateSCgObjectsBuilder::errorList()const
{
    return mDecoratedBuilder->errorList();
}

