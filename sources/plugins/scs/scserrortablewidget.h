/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


