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
#include "gwfstreamwriter.h"
#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgcontour.h"
#include "../scgbus.h"

#include <QTextCodec>

GwfStreamWriter::GwfStreamWriter(): QXmlStreamWriter(),
                                    isWritingStarted(false)
{
    createTypesMap();
}

GwfStreamWriter::GwfStreamWriter(QIODevice* device):QXmlStreamWriter(device),
                                                    isWritingStarted(false)
{
    createTypesMap();
}

GwfStreamWriter::GwfStreamWriter(QByteArray* array):QXmlStreamWriter(array),
                                                    isWritingStarted(false)
{
    createTypesMap();
}

GwfStreamWriter::~GwfStreamWriter()
{

}

void GwfStreamWriter::createTypesMap()
{
    // nodes
    mTypeAlias2GWFType["node/const/not_define"] = "node/const/not_define";
    mTypeAlias2GWFType["node/const/general_node"] = "node/const/general_node";
    mTypeAlias2GWFType["node/const/predmet"] = "node/const/predmet";
    mTypeAlias2GWFType["node/const/nopredmet"] = "node/const/nopredmet";
    mTypeAlias2GWFType["node/const/symmetry"] = "node/const/symmetry";
    mTypeAlias2GWFType["node/const/asymmetry"] = "node/const/asymmetry";
    mTypeAlias2GWFType["node/const/attribute"] = "node/const/attribute";
    mTypeAlias2GWFType["node/const/relation"] = "node/const/relation";
    mTypeAlias2GWFType["node/const/atom"] = "node/const/atom";
    mTypeAlias2GWFType["node/const/group"] = "node/const/group";

    mTypeAlias2GWFType["node/var/not_define"] = "node/var/not_define";
    mTypeAlias2GWFType["node/var/general_node"] = "node/var/general_node";
    mTypeAlias2GWFType["node/var/predmet"] = "node/var/predmet";
    mTypeAlias2GWFType["node/var/nopredmet"] = "node/var/nopredmet";
    mTypeAlias2GWFType["node/var/symmetry"] = "node/var/symmetry";
    mTypeAlias2GWFType["node/var/asymmetry"] = "node/var/asymmetry";
    mTypeAlias2GWFType["node/var/attribute"] = "node/var/attribute";
    mTypeAlias2GWFType["node/var/relation"] = "node/var/relation";
    mTypeAlias2GWFType["node/var/atom"] = "node/var/atom";
    mTypeAlias2GWFType["node/var/group"] = "node/var/group";

    mTypeAlias2GWFType["node/meta/not_define"] = "node/meta/not_define";
    mTypeAlias2GWFType["node/meta/general_node"] = "node/meta/general_node";
    mTypeAlias2GWFType["node/meta/predmet"] = "node/meta/predmet";
    mTypeAlias2GWFType["node/meta/nopredmet"] = "node/meta/nopredmet";
    mTypeAlias2GWFType["node/meta/symmetry"] = "node/meta/symmetry";
    mTypeAlias2GWFType["node/meta/asymmetry"] = "node/meta/asymmetry";
    mTypeAlias2GWFType["node/meta/attribute"] = "node/meta/attribute";
    mTypeAlias2GWFType["node/meta/relation"] = "node/meta/relation";
    mTypeAlias2GWFType["node/meta/atom"] = "node/meta/atom";
    mTypeAlias2GWFType["node/meta/group"] = "node/meta/group";

    // pairs
    mTypeAlias2GWFType["pair/-/-/-/orient/accessory"] = "arc/-/-";
    mTypeAlias2GWFType["pair/-/-/-/noorien"] = "pair/noorient";
    mTypeAlias2GWFType["pair/-/-/-/orient"] = "pair/orient";

    mTypeAlias2GWFType["pair/const/pos/perm/orient/accessory"] = "arc/const/pos";
    mTypeAlias2GWFType["pair/var/pos/perm/orient/accessory"] = "arc/var/pos";
    mTypeAlias2GWFType["pair/meta/pos/perm/orient/accessory"] = "arc/meta/pos";

    mTypeAlias2GWFType["pair/const/neg/perm/orient/accessory"] = "arc/const/neg";
    mTypeAlias2GWFType["pair/var/neg/perm/orient/accessory"] = "arc/var/neg";
    mTypeAlias2GWFType["pair/meta/neg/perm/orient/accessory"] = "arc/meta/neg";

    mTypeAlias2GWFType["pair/const/fuz/perm/orient/accessory"] = "arc/const/fuz" ;
    mTypeAlias2GWFType["pair/var/fuz/perm/orient/accessory"] = "arc/var/fuz";
    mTypeAlias2GWFType["pair/meta/fuz/perm/orient/accessory"] = "arc/meta/fuz";

    mTypeAlias2GWFType["pair/const/pos/temp/orient/accessory"] = "arc/const/pos/temp";
    mTypeAlias2GWFType["pair/var/pos/temp/orient/accessory"] = "arc/var/pos/temp";
    mTypeAlias2GWFType["pair/meta/pos/temp/orient/accessory"] = "arc/meta/pos/temp";

    mTypeAlias2GWFType["pair/const/neg/temp/orient/accessory"] = "arc/const/neg/temp";
    mTypeAlias2GWFType["pair/var/neg/temp/orient/accessory"] = "arc/var/neg/temp";
    mTypeAlias2GWFType["pair/meta/neg/temp/orient/accessory"] = "arc/meta/neg/temp";

    mTypeAlias2GWFType["pair/const/fuz/temp/orient/accessory"] = "arc/const/fuz/temp";
    mTypeAlias2GWFType["pair/var/fuz/temp/orient/accessory"] = "arc/var/fuz/temp";
    mTypeAlias2GWFType["pair/meta/fuz/temp/orient/accessory"] = "arc/meta/fuz/temp";


    mTypeAlias2GWFType["pair/const/-/-/noorien"] = "pair/const/synonym";
    mTypeAlias2GWFType["pair/var/-/-/noorien"] = "pair/var/noorient";
    mTypeAlias2GWFType["pair/meta/-/-/noorien"] = "pair/meta/noorient";

    mTypeAlias2GWFType["pair/const/-/-/orient"] = "pair/const/orient";
    mTypeAlias2GWFType["pair/var/-/-/orient"] = "pair/var/orient";
    mTypeAlias2GWFType["pair/meta/-/-/orient"] = "pair/meta/orient";
}

void GwfStreamWriter::setDevice(QIODevice* device)
{
    QXmlStreamWriter::setDevice(device);
}

void GwfStreamWriter::startWriting(const char* encoding)
{
    QTextCodec *codec = QTextCodec::codecForName(encoding);
    setCodec(codec);
    setAutoFormatting(true);
    writeStartDocument();
    writeStartElement("GWF");
    writeAttribute("version", "1.6");
    writeStartElement("staticSector");
    isWritingStarted = true;
}

void GwfStreamWriter::finishWriting()
{
    Q_ASSERT(isWritingStarted);

    writeEndElement(); /*staticSector*/
    writeEndElement(); /*GWF*/
    writeEndDocument();
}

void GwfStreamWriter::writeObject(SCgObject *object)
{
    Q_ASSERT(isWritingStarted);

    switch (object->type())
    {
    case SCgNode::Type:
        writeNode(object);
        break;
    case SCgPair::Type:
        writePair(object);
        break;
    case SCgBus::Type:
        writeBus(object);
        break;
    case SCgContour::Type:
        writeContour(object);
        break;
    }
}

void GwfStreamWriter::writeObjectAttributes(SCgObject *obj)
{
    writeAttribute("type", mTypeAlias2GWFType[obj->typeAlias()]);
    writeAttribute("idtf", obj->idtfValue());
    writeAttribute("shapeColor", QString::number(obj->color().value()));
    writeAttribute("id", QString::number( obj->id() ));
    writeAttribute("parent", QString::number( obj->parentId() ));
    writeText(obj);
}

void GwfStreamWriter::writeNode( SCgObject *obj)
{
    writeStartElement("node");
    writeObjectAttributes(obj);
    writePosition(obj, "x", "y");

    SCgNode *node = static_cast<SCgNode*>(obj);

    writeAttribute("haveBus", node->bus() ? "true" : "false");

    writeContent(node);

    writeEndElement();//node
}

void GwfStreamWriter::writeContent(SCgNode *node)
{
    writeStartElement("content");

    int cType = node->contentType();
    QString mimeType = node->contentMimeType();

    writeAttribute("type",QString::number(cType));
    writeAttribute("mime_type", node->contentMimeType());
    writeAttribute("file_name", node->contentFileName());

    switch(cType)
    {
        case 1:
        case 2:
        case 3:
        {
            writeCDATA((node->contentData()).toString());
            break;
        }
        case 4:
        {
            QByteArray arr = node->contentData().toByteArray().toBase64();
            writeCDATA(arr);
            break;
        }
    }

    writeEndElement();//content
}

void GwfStreamWriter::writePair(SCgObject *obj)
{
    QString type = mTypeAlias2GWFType[obj->typeAlias()].mid(0,3);
    if(type=="arc")
        writeStartElement(type);
    else
        writeStartElement("pair");
    writeObjectAttributes(obj);
    SCgPair* pair = static_cast<SCgPair*>(obj);
    SCgObject* b = pair->getBeginObject();
    SCgObject* e = pair->getEndObject();
    writeAttribute("id_b", QString::number(b->id()));
    writeAttribute("id_e", QString::number(e->id()));

    writePosition(b,"b_x","b_y");
    writePosition(e,"e_x","e_y");

    writeAttribute("dotBBalance", QString::number(pair->getBeginDot()));
    writeAttribute("dotEBalance", QString::number(pair->getEndDot()));
    QVector<QPointF> points = pair->scenePoints();
    points.pop_back();
    points.pop_front();
    writePoints(points);
    writeEndElement();
}

void GwfStreamWriter::writeBus(SCgObject *obj)
{
    writeStartElement("bus");
    writeObjectAttributes(obj);
    SCgBus* bus = static_cast<SCgBus*>(obj);

    writeAttribute("owner", QString::number(bus->owner()->id()));

    QVector<QPointF> points = bus->scenePoints();
    writeAttribute("b_x", QString::number(points.first().x()));
    writeAttribute("b_y", QString::number(points.first().y()));
    writeAttribute("e_x", QString::number(points.last().x()));
    writeAttribute("e_y", QString::number(points.last().y()));

    // do not save begin and end points
    points.pop_back();
    points.pop_front();
    writePoints(points);

    writeEndElement();
}

void GwfStreamWriter::writeContour(SCgObject *obj)
{
    writeStartElement("contour");
    writeObjectAttributes(obj);
    SCgContour* contour = static_cast<SCgContour*>(obj);

    QVector<QPointF> points(contour->scenePoints());
    writePoints(points);

    writeEndElement();
}

void GwfStreamWriter::writePosition(SCgObject *obj,const QString& x, const QString& y)
{
    QPointF globPos = obj->scenePos();

    writeAttribute(x, QString::number(globPos.x()));
    writeAttribute(y, QString::number(globPos.y()));
}

void GwfStreamWriter::writePoints(const QVector<QPointF>& points)
{
    writeStartElement("points");

    foreach(const QPointF& point,points)
    {
        writeStartElement("point");
        writeAttribute("x", QString::number(point.x()));
        writeAttribute("y", QString::number(point.y()));
        writeEndElement();
    }
    writeEndElement();
}

void GwfStreamWriter::writeText(SCgObject *obj)
{
    if(obj->textItem())
    {
        writeAttribute("left", QString::number(obj->textItem()->boundingRect().left()));
        writeAttribute("top", QString::number(obj->textItem()->boundingRect().top()));
        writeAttribute("right", QString::number(obj->textItem()->boundingRect().right()));
        writeAttribute("bottom", QString::number(obj->textItem()->boundingRect().bottom()));

        writeAttribute("textColor", QString::number(obj->textItem()->defaultTextColor().value()));
        writeAttribute("text_angle", QString::number(obj->textItem()->rotation()));

        writeAttribute("text_font", obj->textItem()->font().family());
        writeAttribute("font_size", QString::number(obj->textItem()->font().pointSize()));
    }
}
