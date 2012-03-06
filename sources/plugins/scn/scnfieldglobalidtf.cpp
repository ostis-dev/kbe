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

#include "scnfieldglobalidtf.h"

#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>

SCnFieldGlobalIdtf::SCnFieldGlobalIdtf(QObject *parent) :
    SCnFieldItem(parent)
{
    mFont = QFont("Arial", 14);
    mFont.setBold(true);
    mFont.setItalic(true);
}

SCnFieldGlobalIdtf::~SCnFieldGlobalIdtf()
{

}

qreal SCnFieldGlobalIdtf::childsOffset() const
{
    QFontMetrics fm(mFont);
    return fm.boundingRect(mValue).height() + 10;
}

QRectF SCnFieldGlobalIdtf::boundingRect() const
{
    QFontMetrics fm(mFont);
    QRectF textRect = fm.boundingRect(mValue);

    QRectF childRect = childrenBoundingRect();

    return textRect.united(childRect).adjusted(-10, -10, 20, 20);
}

void SCnFieldGlobalIdtf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCnFieldItem::paint(painter, option, widget);

    // draw value
    painter->setPen(QColor(0, 0, 0, 200));

    painter->setFont(mFont);
    painter->drawText(5, 5, mValue);
}

