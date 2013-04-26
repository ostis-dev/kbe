#ifndef SCSERRORTABLEWIDGETITEM_H
#define SCSERRORTABLEWIDGETITEM_H

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

#endif // SCSERRORTABLEWIDGETITEM_H
