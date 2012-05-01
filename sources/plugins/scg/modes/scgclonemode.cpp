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

#include "scgclonemode.h"
#include "scgcontour.h"
#include "gwf/gwfobjectinforeader.h"
#include "gwf/gwfstreamwriter.h"
#include "scgtemplateobjectbuilder.h"

#include <QDomDocument>
#include <QGraphicsView>

SCgCloneMode::SCgCloneMode(SCgScene *scene) :
    SCgInsertMode(scene)
{
}

SCgCloneMode::~SCgCloneMode()
{
    clean();
}

void SCgCloneMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgMode::mousePress(event);

    if (!mInsertedObjectGroup)
    {
        mScene->setEditMode(mScene->previousMode());
        return;
    }

    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;

    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);

    mScene->cloneCommand(mInsertedObjectGroup->childItems(), parent);

    clean();
}

void SCgCloneMode::activate()
{
    clean();

    QList<QGraphicsItem*> list = mScene->selectedItems();

    QByteArray clonedData;
    GwfStreamWriter writer(&clonedData);
    ////////////////////////////////////
    writer.startWriting();

    if (list.isEmpty())
        return;

    foreach (QGraphicsItem *item, list)
        if(SCgObject::isSCgObjectType(item->type()) )
            writer.writeObject(static_cast<SCgObject*>(item));

    writer.finishWriting();
    QDomDocument document;

    if (!document.setContent(clonedData))
        return;

    // Read document
    GwfObjectInfoReader reader;
    if (! reader.read(document))
        return;

    //Place objects to scene
    TemplateSCgObjectsBuilder objectBuilder(mScene);
    objectBuilder.buildObjects(reader.objectsInfo());

    QList<SCgObject*> objList = objectBuilder.objects();
    QList<QGraphicsItem*> withoutChilds;

    foreach(QGraphicsItem* obj, objList)
        if (!obj->parentItem())
            withoutChilds.append(obj);

    if(!withoutChilds.empty())
    {
        mInsertedObjectGroup = mScene->createItemGroup(withoutChilds);

        QGraphicsView* v = mScene->views().at(0);
        QPointF p = v->mapToScene(v->mapFromGlobal(QCursor::pos()));

        mInsertedObjectGroup->setPos(p);
        mInsertedObjectGroup->setOpacity(0.5);
    }
}

void SCgCloneMode::deactivate()
{
    SCgInsertMode::deactivate();
}
