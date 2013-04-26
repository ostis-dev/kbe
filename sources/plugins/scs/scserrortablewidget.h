#ifndef SCSERRORTABLEWIDGET_H
#define SCSERRORTABLEWIDGET_H

#include <QTableWidget>

#define ERROR_TABLE_WIDGET_ITEM_COLUMN 0


class SCsErrorTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit SCsErrorTableWidget(QWidget *parent = 0);
	void addError(QString &description, int line, int charPos);
	void clear();
    void resizeEvent(QResizeEvent *event);
    void show();
signals:
    void errorAt(int line,int charPos);
private slots:
    void doubleClickAtCell(int row, int col);

};

#endif // SCSERRORTABLEWIDGET_H
