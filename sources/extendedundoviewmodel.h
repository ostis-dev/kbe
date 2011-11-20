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

#ifndef EXTENDEDUNDOVIEWMODEL_H_
#define EXTENDEDUNDOVIEWMODEL_H_

#include <QAbstractItemModel>
#include <QIcon>

class QUndoStack;
class QItemSelectionModel;

/*! Model, provided connection with QUndoStack.
 * Most part of this class is taken from Qt sources (qundomodel.cpp)
 */
class ExtendedUndoViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ExtendedUndoViewModel(QObject *parent = 0);

    QUndoStack *stack() const;

    virtual QModelIndex index(int row, int column,
                const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QModelIndex selectedIndex() const;
    QItemSelectionModel *selectionModel() const;

    QString emptyLabel() const;
    void setEmptyLabel(const QString &label);

    void setCleanIcon(const QIcon &icon);
    QIcon cleanIcon() const;

public slots:
    void setStack(QUndoStack *stack);

private slots:
    void stackChanged();
    void stackDestroyed(QObject *obj);
    void setStackCurrentIndex(const QModelIndex &index);

private:
    QUndoStack *m_stack;
    QItemSelectionModel *m_sel_model;
    QString m_emty_label;
    QIcon m_clean_icon;
};

#endif /* EXTENDEDUNDOVIEWMODEL_H_ */
