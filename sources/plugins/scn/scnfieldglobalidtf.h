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

#ifndef SCNFIELDGLOBALIDTF_H
#define SCNFIELDGLOBALIDTF_H

#include "scnfielditem.h"

#include <QFont>

class SCnFieldGlobalIdtf : public SCnFieldItem
{
    Q_OBJECT
public:
    explicit SCnFieldGlobalIdtf(QObject *parent = 0);
    virtual ~SCnFieldGlobalIdtf();

    enum { Type = UserType + 1 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! @copydoc SCnFieldItem::isSubitemsPossible
    bool isSubitemsPossible() const { return true; }
    //! @copydoc SCnFieldItem::canBeRoot
    bool canBeRoot() const {return true; }
    //! @copydoc SCnFieldItem::canBeAtZeroLevel
    bool canBeAtZeroLevel() const { return true; }
    //! @copydoc SCnFieldItem::childsOffset
    qreal childsOffset() const;

private:
    //! Used font
    QFont mFont;

signals:

public slots:

};

#endif // SCNFIELDGLOBALIDTF_H
