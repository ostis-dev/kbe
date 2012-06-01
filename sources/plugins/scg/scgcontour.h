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

#ifndef SCGCONTOUR_H
#define SCGCONTOUR_H

#include "scgpointobject.h"

#include <QColor>

class SCgContour : public SCgPointObject
{

public:
    enum { Type = UserType + 5 };

    explicit SCgContour();
    virtual ~SCgContour();

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
    //! Contour shape
    QPainterPath mShape;
    //! Drawable shape
    QPainterPath mShapeDraw;

    //! Background color
    QColor mColorBack;
};

#endif // SCGCONTOUR_H
