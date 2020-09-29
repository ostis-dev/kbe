/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgobject.h"
#include "scgcontent.h"


class SCgBus;
class SCgContentViewer;

class SCgNode : public SCgObject, public SCgContent
{
	Q_OBJECT
friend class SCgBus;

public:
    enum { Type = UserType + 2 };
    typedef enum
    {
        BottomRight = 0,
        BottomLeft,
        TopLeft,
        TopRight,
        Left,
        Right
    } IdentifierPosition;

    /*! Type for qgraphicsitem_cast
      */
    int type() const { return Type; }

    explicit SCgNode(QGraphicsItem *parent = 0);

	void setIdtfValue(const QString &idtf);

    void setIdtfPos(IdentifierPosition pos);
    IdentifierPosition idtfPos() const;

	QRectF boundingRect() const;

    virtual ~SCgNode();

private:
    //! Type information update
    void updateType();

protected:
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintStruct(QPainter *painter);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void del(QList<SCgObject*> &delList);

public:
    /*! Sets content to a node
      @param    format  String that designate content format. For example: string, numeric, image and etc.
      @param    data    Object that contains content data.
      @param    fileName    Name of file, that sets used to get content.
      @param    cType   Content type: int, real, string, binary
      */
    void setContent(const QString& mimeType, const QVariant& data, const QString& fileName, SCgContent::ContType cType);

    void objectDelete(SCgObject *object);
    void positionChanged();


    QPointF cross(const QPointF &from, float dot) const;
    float dotPos(const QPointF &point) const;
public:

    // ----- Type ----
    void setTypeAlias(const QString &typeAlias);

    //! Returns structure type of this node
    SCgAlphabet::SCgNodeStructType structType() const;


    // ------ Contents ------
    /*! Shows content
      @see SCgNode::hideContent(), SCgNode::isContentVisible()
      */
    void showContent();

    /*! Hides content
      @see SCgNode::showContent(), SCgNode::isContentVisible()
      */
    void hideContent();

    /*! Check if content visible.
      \return if content visible, then return true, else - false.

      @see SCgNode::showContent(), SCgNode::hideContent()
      */
    bool isContentVisible() const;

    /*! Get contend data

        \return Content data.

        @see SCgNode::setContentData()
      */
    bool isContentData() const;

    /*! Check if node have bus
        \return If node have bus, then return true, else - false.
      */
    SCgBus* bus() const;

    //! Update (repaint) connected objects
    void updateConnected();

protected:
    /*! Set scg-bus.
        \param bus  Pointer to scg-bus.
      */
    void setBus(SCgBus *bus);

    /*! Restore object after deletion
      @see SCgObject::undel(*scene)
      */
    virtual void undel(SCgScene *scene);

    /*! Updates content viewer
      */
    void updateContentViewer();

private:
    QSizeF mSize;

    SCgAlphabet::SCgNodeStructType mStructType;

    /*! Content visibility flag
      */
    bool mIsContentVisible;

    /*! Content viewer
     *  This is a widget for displaying content.
      */
    SCgContentViewer *mContentViewer;

    /*! Pointer to bus
      */
    SCgBus* mBus;

signals:

    void contentChanged();

public slots:

};

