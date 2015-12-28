/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgobject.h"

class SCpOperator : public SCgObject
{
    Q_OBJECT
public:
    explicit SCpOperator(QGraphicsItem * parent);
    virtual ~SCpOperator();

protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QString mOperatorName;
};
