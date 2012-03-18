#include "SCgCloneModeEventHandler.h"
#include "../scgcontour.h"
#include "../gwf/gwfobjectinforeader.h"
#include "../gwf/gwfstreamwriter.h"
#include "../scgtemplateobjectbuilder.h"

#include <QDomDocument>
#include <QGraphicsView>

SCgCloneModeEventHandler::SCgCloneModeEventHandler(SCgScene *scene) :
    SCgInsertModeEventHandler(scene)
{
}

SCgCloneModeEventHandler::~SCgCloneModeEventHandler() {
    clean();
}

void SCgCloneModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mousePress(event);
    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;
    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);
    mScene->cloneCommand(mInsertedObjectGroup->childItems(), parent);
    clean();
}

void SCgCloneModeEventHandler::activate() {
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

void SCgCloneModeEventHandler::deactivate() {
    SCgInsertModeEventHandler::deactivate();
}
