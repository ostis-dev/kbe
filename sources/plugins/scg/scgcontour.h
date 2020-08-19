/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgpointobject.h"

#include <QColor>

class SCgContour : public SCgPointObject
{

public:
    enum { Type = UserType + 5 };

    explicit SCgContour();
    virtual ~SCgContour();

    void setTypeAlias(const QString &typeAlias);
    void updateType();

    /*! Set background color
      @param color BAckground color
      */
    void setColorBack(const QColor &color);

    /*! Get background color
      @return Background color
      */
    QColor colorBack() const;

    /*! Updates contour data.
      */
    void positionChanged();

    //! Minimizes size and leaves only 4 points:
    void minimize();

    /*! Get 4 points of minimized contour
      @return Minimized contour points
      */
    PointFVector minimizedPoints() const;

    //! @see SCgPointObject::updateShape;
    void updateShape();

    //! @attention  points must be in local coordinates
    void setPoints(const PointFVector &points);

    //! @see QGraphicsItem::shape()
    QPainterPath shape() const;

protected:
    //! @see QGraphicsItem::boundingRect()
    QRectF boundingRect() const;

    //! @see QGraphicsItem::contains
    bool contains(const QPointF &point) const;

    /*! @see QGraphicsItem::paint
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! @see SCgPointObject::createPointItem()
    SCgPointGraphicsItem* createPointItem(int pointIndex);

public:
    int type() const { return Type; }

    /*! @see SCgObject::objectDelete
      */
    void objectDelete(SCgObject *object);

    QPointF cross(const QPointF &from, float dot) const;
    float dotPos(const QPointF &point) const;

    //! @see SCgObject::updateConnected();
    void updateConnected();

    //! @see SCgObject::del()
    void del(QList<SCgObject*> &delList);

    //! @see SCgPointObject::changePointPosition(int pointIndex, const QPointF& newPos)
    void changePointPosition(int pointIndex, const QPointF& newPos);

protected:
    //! Corner radius for drawing shape
    static qreal CornerRadius;

    //! Distance from border to content for minimized contour:
    static qreal BorderDistance;

    //! Contour shape
    QPainterPath mShape;

    //! Drawable shape
    QPainterPath mShapeDraw;

    //! Background color
    QColor mColorBack;
};
