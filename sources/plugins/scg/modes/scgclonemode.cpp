/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgclonemode.h"
#include "scgcontour.h"
#include "gwf/gwfobjectinforeader.h"
#include "gwf/gwfstreamwriter.h"
#include "scgtemplateobjectbuilder.h"

#include <QDomDocument>
#include <QGraphicsView>
#include <QDebug>

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
    qDebug() << "copy command 1";

    if (!mInsertedObjectGroup)
    {
        qDebug() << "copy command any went wrong";
        mScene->setEditMode(mScene->previousMode());
        return;
    }

    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;

    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);

    qDebug() << "copy command";
    mScene->cloneCommand(mInsertedObjectGroup->childItems(), parent);

    clean();
}

void SCgCloneMode::activate()
{
    qDebug() << "copy command activated";
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
