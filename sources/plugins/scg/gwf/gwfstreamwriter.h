/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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

    void createTypesMap();
};

