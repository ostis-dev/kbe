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

#ifndef SCSERRORTABLEWIDGETITEM_H
#define SCSERRORTABLEWIDGETITEM_H

#include <QtWidgets/QTableWidgetItem>


#define ERROR_TABLE_WIDGET_ITEM_TYPE QTableWidgetItem::UserType + 1


class SCsErrorTableWidgetItem : public QTableWidgetItem
{
public:
    SCsErrorTableWidgetItem(QString description, int line, int charPos);
    inline QString description() { return mDescription; }
    inline int line() { return mLine; }
    inline int charPosition() { return mCharPosition; }

private:
    QString mDescription;
    int mLine;
    int mCharPosition;
};

#endif // SCSERRORTABLEWIDGETITEM_H
