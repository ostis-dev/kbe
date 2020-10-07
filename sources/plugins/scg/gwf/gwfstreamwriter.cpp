/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "gwfstreamwriter.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgbus.h"
#include "scgtextitem.h"

#include <QTextCodec>

GwfStreamWriter::GwfStreamWriter(): QXmlStreamWriter(),
                                    isWritingStarted(false)
{
}

GwfStreamWriter::GwfStreamWriter(QIODevice* device):QXmlStreamWriter(device),
                                                    isWritingStarted(false)
{
}

GwfStreamWriter::GwfStreamWriter(QByteArray* array):QXmlStreamWriter(array),
                                                    isWritingStarted(false)
{
}

GwfStreamWriter::~GwfStreamWriter()
{

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
    writeAttribute("version", "2.0");
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
    writeAttribute("type", obj->typeAlias());
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
    writeAttribute("idtf_pos", QString::number((int)node->idtfPos()));

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
    writeAttribute("content_visibility", node->isContentVisible() ? "true" : "false");
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
    QString type = obj->typeAlias().mid(0,3);
    if(type=="arc")
        writeStartElement(type);
    else
        writeStartElement("pair");
    writeObjectAttributes(obj);
    SCgPair* pair = static_cast<SCgPair*>(obj);
    SCgObject* b = pair->beginObject();
    SCgObject* e = pair->endObject();
    writeAttribute("id_b", QString::number(b->id()));
    writeAttribute("id_e", QString::number(e->id()));

    writePosition(b,"b_x","b_y");
    writePosition(e,"e_x","e_y");

    writeAttribute("dotBBalance", QString::number(pair->beginDot()));
    writeAttribute("dotEBalance", QString::number(pair->endDot()));
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
    if (contour->idtfValue() != NULL) {
        writeAttribute("idtf_pos_x", QString::number((int)contour->idtfPos().x()));
        writeAttribute("idtf_pos_y", QString::number((int)contour->idtfPos().y()));
    }
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
