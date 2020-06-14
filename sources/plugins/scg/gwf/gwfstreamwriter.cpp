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
    mTypeAlias2GWFType["node/-/not_define"] = "node/-/not_define";

    mTypeAlias2GWFType["node/const/general"] = "node/const/general_node";
    mTypeAlias2GWFType["node/const/terminal"] = "node/const/terminal";
    mTypeAlias2GWFType["node/const/struct"] = "node/const/nopredmet";
    mTypeAlias2GWFType["node/const/symmetry"] = "node/const/symmetry";
    mTypeAlias2GWFType["node/const/tuple"] = "node/const/asymmetry";
    mTypeAlias2GWFType["node/const/role"] = "node/const/attribute";
    mTypeAlias2GWFType["node/const/relation"] = "node/const/relation";
    mTypeAlias2GWFType["node/const/atom"] = "node/const/atom";
    mTypeAlias2GWFType["node/const/group"] = "node/const/group";

    mTypeAlias2GWFType["node/var/not_define"] = "node/var/not_define";
    mTypeAlias2GWFType["node/var/general"] = "node/var/general_node";
    mTypeAlias2GWFType["node/var/terminal"] = "node/var/terminal";
    mTypeAlias2GWFType["node/var/struct"] = "node/var/nopredmet";
    mTypeAlias2GWFType["node/var/tuple"] = "node/var/symmetry";
    mTypeAlias2GWFType["node/var/asymmetry"] = "node/var/asymmetry";
    mTypeAlias2GWFType["node/var/role"] = "node/var/attribute";
    mTypeAlias2GWFType["node/var/relation"] = "node/var/relation";
    mTypeAlias2GWFType["node/var/atom"] = "node/var/atom";
    mTypeAlias2GWFType["node/var/group"] = "node/var/group";

    mTypeAlias2GWFType["node/meta/not_define"] = "node/meta/not_define";
    mTypeAlias2GWFType["node/meta/general"] = "node/meta/general_node";
    mTypeAlias2GWFType["node/meta/abstract"] = "node/meta/predmet";
    mTypeAlias2GWFType["node/meta/nopredmet"] = "node/meta/nopredmet";
    mTypeAlias2GWFType["node/meta/tuple"] = "node/meta/symmetry";
    mTypeAlias2GWFType["node/meta/asymmetry"] = "node/meta/asymmetry";
    mTypeAlias2GWFType["node/meta/role"] = "node/meta/attribute";
    mTypeAlias2GWFType["node/meta/relation"] = "node/meta/relation";
    mTypeAlias2GWFType["node/meta/atom"] = "node/meta/atom";
    mTypeAlias2GWFType["node/meta/group"] = "node/meta/group";

    // pairs
    mTypeAlias2GWFType["pair/-/-/-/orient/accessory"] = "arc/-/-";
    mTypeAlias2GWFType["pair/-/-/-/noorient"] = "pair/noorient";
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
    QString type = mTypeAlias2GWFType[obj->typeAlias()].mid(0,3);
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
