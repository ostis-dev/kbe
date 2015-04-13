/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
    */
    explicit SCgTextItem(const QString &str, QGraphicsItem* parent = 0);

    /**
    * @brief Constructor. All parameters are passed to QGraphicsTextItem's constructor
    * @param parent Pointer to the parent graphics item
    */
    explicit SCgTextItem(QGraphicsItem* parent = 0);

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


