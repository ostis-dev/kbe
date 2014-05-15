/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
