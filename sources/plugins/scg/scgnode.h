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

#ifndef SCGNODE_H
#define SCGNODE_H

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
    /*! Type for qgraphicsitem_cast
      */
    int type() const { return Type; }

    explicit SCgNode(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgNode();

private:
    //! Type information update
    void updateType();

protected:
    QRectF boundingRect() const;
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
    void setTypeAlias(const QString &typeAlias);

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

#endif // SCGNODE_H
