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

#ifndef GWFSTREAMWRITER_H_
#define GWFSTREAMWRITER_H_

#include <QXmlStreamWriter>
#include <QVector>
#include <QPointF>
#include <QMap>

class SCgObject;
class SCgNode;

//! Class for writing data in gwf format.
/*! NOTE: First of all you have to specify device for storing information \
    @see GwfStreamWriter::GwfStreamWriter(QIODevice* device),\
    @see GwfStreamWriter::GwfStreamWriter(QByteArray* array),\
    @see GwfStreamWriter::setDevice(QIODevice* device).
    Next step is to write header information needed for gwf-format.\
    @see  GwfStreamWriter::startWriting(const char* encoding = "UTF-8").
    After writing all objects by GwfStreamWriter::writeObject(SCgObject *object) \
    You have to finish writing by calling GwfStreamWriterfinishWriting().
*/
class GwfStreamWriter: private QXmlStreamWriter
{

public:
    GwfStreamWriter();
    explicit GwfStreamWriter(QIODevice* device);
    explicit GwfStreamWriter(QByteArray* array);
    virtual ~GwfStreamWriter();

    //! Sets up current writing device. @see QXmlStreamWriter::setDevice
    void setDevice(QIODevice* device);

    /*! Writes start element for GWF-document.
     * @param encoding Encoding, for writer
     */
    void startWriting(const char* encoding = "UTF-8");

    //! Finishes writing GWF-document.
    void finishWriting();

    //! Analyzes type of object and writes it to specified device;
    void writeObject(SCgObject *object);

private:
    bool isWritingStarted;
    /*! Save sc.g-node.
      @param node Element of sc.g-node type.
      */
    void writeNode(SCgObject *node);

    /*! Save sc.g-pair.
      @param node Element of sc.g-pair.
      */
    void writePair(SCgObject *node);

    /*! Save sc.g-bus.
      @param obj Element of sc.g-bus.
      */
    void writeBus(SCgObject *obj);

    /*! Save sc.g-contour.
      @param obj Element of sc.g-contour.
      */
    void writeContour(SCgObject *obj);

    /*! Save sc.g-Object attributes.
      @param obj Element of sc.g-object.
      */
    void writeObjectAttributes(SCgObject *obj);

    /*! Save point position.
      @param obj Element of sc.g-object.
      @param x Name of attribute x-positions.
      @param y Name of attribute y-positions.
      */
    void writePosition(SCgObject *obj,const QString& x, const QString& y);

    /*! Save points array.
      @param points Vector of points
      */
    void writePoints(const QVector<QPointF>& points);

    /*! Save text attribute.
      @param obj Element of sc.g-object.
      */
    void writeText(SCgObject *obj);

    /*! Save content in node.
      @param node Element of sc.g-node type.
      */
    void writeContent(SCgNode *node);

    typedef QMap<QString, QString> GWFType2TypeAliasMap;
    //! Map for mapping gwf types to types alias
    GWFType2TypeAliasMap mTypeAlias2GWFType;

    void createTypesMap();
};

#endif /* GWFSTREAMWRITER_H_ */
