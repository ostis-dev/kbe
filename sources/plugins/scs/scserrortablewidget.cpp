/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scserrortablewidget.h"
#include "scserrortablewidgetitem.h"

#include <QHeaderView>
#include <QResizeEvent>


#define ROW_HEIGHT 20


SCsErrorTableWidget::SCsErrorTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doubleClickAtCell(int,int)));
	setRowCount(0);
	setColumnCount(2);

    QHeaderView *header = new QHeaderView(Qt::Horizontal);
    this->setHorizontalHeader(header);

    setMinimumWidth(200);

    hide();
}

void SCsErrorTableWidget::doubleClickAtCell(int row, int col)
{
    if(item(row,0)->type() != ERROR_TABLE_WIDGET_ITEM_TYPE)
        return;

    Q_UNUSED(col);

    SCsErrorTableWidgetItem *item = (SCsErrorTableWidgetItem*) this->item(row,ERROR_TABLE_WIDGET_ITEM_COLUMN);

    Q_CHECK_PTR(item);

    emit errorAt(item->line(), item->charPosition());
}



void SCsErrorTableWidget::addError(QString &description, int line, int charPos)
{
	if(description.isEmpty() || line < 0)
		return;

	int row = rowCount();

    setRowCount(row+1);

    setItem(row, 0, new SCsErrorTableWidgetItem(description, line, charPos));
	QTableWidgetItem *item = new QTableWidgetItem(QString::number(line));
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    setItem(row, 1, item);

	setRowHeight(row,ROW_HEIGHT);

}

void SCsErrorTableWidget::clear()
{
	QTableWidget::clear();
	setRowCount(0);
}


void SCsErrorTableWidget::show()
{
    QTableWidget::show();
    QStringList headerLabel;
    headerLabel << tr("Error description") << tr("Line");
    setHorizontalHeaderLabels(headerLabel);

}

void SCsErrorTableWidget::resizeEvent(QResizeEvent *event)
{
	int width = event->size().width();
	horizontalHeader()->resizeSection(0,width-50);
	horizontalHeader()->resizeSection(1,50);
}
