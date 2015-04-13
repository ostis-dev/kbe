/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QAbstractItemModel>
#include <QIcon>

class QUndoStack;
class QItemSelectionModel;

/*! Model, provided connection with QUndoStack.
 * Most part of this class is taken from Qt sources (qundomodel.cpp)
 */
class SCgUndoViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SCgUndoViewModel(QObject *parent = 0);

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


