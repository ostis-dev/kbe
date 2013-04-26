#include "scserrortablewidgetitem.h"


SCsErrorTableWidgetItem::SCsErrorTableWidgetItem(QString description, int line, int charPos)
    : QTableWidgetItem(description,ERROR_TABLE_WIDGET_ITEM_TYPE)
    , mDescription(description)
    , mLine(line)
    , mCharPosition(charPos)
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}
