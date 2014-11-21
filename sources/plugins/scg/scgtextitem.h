/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef SCGTEXTITEM_H
#define SCGTEXTITEM_H

#include <QGraphicsTextItem>

/**
* @brief Class represents a graphics item for object's identifier
*/
class SCgTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    //! Object type
    enum { Type = UserType + 8 };

    /**
    * @brief Constructor. All parameters are passed to QGraphicsTextItem's constructor
    * @param str    String that contains
    * @param parent Pointer to the parent graphics item
    * @param scene  Pointer to the graphics scene that contains current item
    */
    explicit SCgTextItem(const QString &str, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    /**
    * @brief Constructor. All parameters are passed to QGraphicsTextItem's constructor
    * @param parent Pointer to the parent graphics item
    * @param scene  Pointer to the graphics scene that contains current item
    */
    explicit SCgTextItem(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    //! Destructor
    virtual ~SCgTextItem();

    //! @copydoc QGraphicsItem::paint
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! @copydoc QGraphicsItem::boundingRect
    QRectF boundingRect() const;

    //! @copydoc QGraphicsItem::itemChange
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //! Return a type of graphics item as integer
    virtual int type() const { return Type; }

    virtual void setTextPos(const QPointF &pos);
    QPointF textPos() const;

    virtual void setPlainText(const QString &text);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setPos(const QPointF &pos);
    void setPos(qreal x, qreal y);
    QPointF pos() const;
};

#endif // SCGTEXTITEM_H
