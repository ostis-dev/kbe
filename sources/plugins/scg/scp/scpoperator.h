/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgobject.h"

class QGraphicsDropShadowEffect;

class SCpOperatorPin;

class SCpOperator : public SCgObject
{
    Q_OBJECT
public:
    explicit SCpOperator(QGraphicsItem * parent);
    virtual ~SCpOperator();

    enum { Type = UserType + 50 };
    int type() const { return Type; }

protected:
    virtual QPainterPath shape() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void positionChanged();
    virtual QPointF cross(QPointF const & from, float dot) const;
    virtual float dotPos(QPointF const & point) const;
    virtual void connectedObjectDelete(SCgObject * object);


    void updateBounds();
    void updatePinPositions();
    inline QPointF calculatePinPosition(int index, bool isInput) const;

protected:
    void addInputPin(SCpOperatorPin * pin);
    void addOutputPin(SCpOperatorPin * pin);

protected:
    QString mOperatorName;
    QRectF mBoundsRect;

    QVector<SCpOperatorPin*> mInputPins;
    QVector<SCpOperatorPin*> mOutputPins;

    QGraphicsDropShadowEffect * mShadowEffect;

};
