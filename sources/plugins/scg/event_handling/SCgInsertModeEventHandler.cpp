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

#include "SCgInsertModeEventHandler.h"
#include "../scgcontour.h"
#include "../gwf/gwfobjectinforeader.h"
#include "../scgtemplateobjectbuilder.h"
#include "../scgwindow.h"
#include <QDomDocument>
#include <QGraphicsView>
#include <QApplication>
#include <QClipboard>

SCgInsertModeEventHandler::SCgInsertModeEventHandler(SCgScene* parent):
    SCgEventHandler(parent),
    mInsertedObjectGroup(0)
{
}

SCgInsertModeEventHandler::~SCgInsertModeEventHandler()
{
    clean();
}

void SCgInsertModeEventHandler::mousePress(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mousePress(event);
    SCgObject* underMouseObj = mScene->objectAt(event->scenePos());
    SCgContour* parent = 0;
    if (underMouseObj && underMouseObj->type() == SCgContour::Type)
        parent = static_cast<SCgContour*>(underMouseObj);
    mScene->pasteCommand(mInsertedObjectGroup->childItems(), parent);
    clean();
}

void SCgInsertModeEventHandler::mouseMove(QGraphicsSceneMouseEvent *event)
{
    SCgEventHandler::mouseMove(event);
    if (mInsertedObjectGroup)
        mInsertedObjectGroup->setPos(event->scenePos());
}

void SCgInsertModeEventHandler::keyPress(QKeyEvent *event)
{
    SCgEventHandler::keyPress(event);
    if(event->key() == Qt::Key_Escape)
    {
        clean();
        mScene->setEditMode(mScene->previousMode());
        event->accept();
    }
}

void SCgInsertModeEventHandler::clean()
{
    SCgEventHandler::clean();
    if (mInsertedObjectGroup)
    {
        delete mInsertedObjectGroup;
        mInsertedObjectGroup = 0;
    }
}

void SCgInsertModeEventHandler::activate() {
    if (mInsertedObjectGroup)
    {
        delete mInsertedObjectGroup;
        mInsertedObjectGroup = 0;
    }

    const QMimeData* data = QApplication::clipboard()->mimeData();
    if(data->hasFormat(SCgWindow::SupportedPasteMimeType))
    {
        QDomDocument document;

        if (!document.setContent(data->data(SCgWindow::SupportedPasteMimeType)))
            return;

        // Read document
        GwfObjectInfoReader reader;
        if (! reader.read(document))
            return;

        //Place objects to scene
        TemplateSCgObjectsBuilder objectBuilder(mScene);
        objectBuilder.buildObjects(reader.objectsInfo());

        QList<SCgObject*> list = objectBuilder.objects();
        QList<QGraphicsItem*> withoutChilds;
        foreach(SCgObject* obj, list)
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
    else mScene->setEditMode(mScene->previousMode());


}

void SCgInsertModeEventHandler::deactivate() {
    clean();
}
