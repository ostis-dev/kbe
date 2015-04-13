/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scserrortablewidgetitem.h"


SCsErrorTableWidgetItem::SCsErrorTableWidgetItem(QString description, int line, int charPos)
    : QTableWidgetItem(description,ERROR_TABLE_WIDGET_ITEM_TYPE)
    , mDescription(description)
    , mLine(line)
    , mCharPosition(charPos)
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}
