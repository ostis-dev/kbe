/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpoperator.h"

#include <QLinearGradient>

#define PADDING     5

SCpOperator::SCpOperator(QGraphicsItem * parent)
    : SCgObject(parent)
    , mOperatorName(tr("Base SCp operator"))
{
}

SCpOperator::~SCpOperator()
{
}

QRectF SCpOperator::boundingRect() const
{
    float const width = PADDING * 2 + 300;
    float const height = PADDING * 2 + 70;
    float const width2 = width / 2.f;
    float const height2 = height / 2.f;

    return QRectF(-width2, -height2, width2, height2);
}

void SCpOperator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRoundRect(rect, 10, 10);
}
