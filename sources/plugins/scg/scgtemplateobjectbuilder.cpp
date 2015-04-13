/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgtemplateobjectbuilder.h"
#include "scgdefaultobjectbuilder.h"

#include "scgobject.h"
#include "scgnode.h"
#include "scgbus.h"

TemplateSCgObjectsBuilder::TemplateSCgObjectsBuilder(QGraphicsScene* scene) :
        AbstractSCgObjectBuilder()
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

