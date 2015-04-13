/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QTableWidgetItem>


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


