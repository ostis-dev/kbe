/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgundoviewmodel.h"

#include <QUndoStack>
#include <QItemSelectionModel>
#include <QBrush>

SCgUndoViewModel::SCgUndoViewModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_stack = 0;
    m_sel_model = new QItemSelectionModel(this, this);
    connect(m_sel_model, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(setStackCurrentIndex(QModelIndex)));
    m_emty_label = tr("<empty>");
}

QItemSelectionModel *SCgUndoViewModel::selectionModel() const
{
    return m_sel_model;
}

QUndoStack *SCgUndoViewModel::stack() const
{
    return m_stack;
}

void SCgUndoViewModel::setStack(QUndoStack *stack)
{
    if (m_stack == stack)
        return;

    if (m_stack != 0)
    {
        disconnect(m_stack, SIGNAL(cleanChanged(bool)), this, SLOT(stackChanged()));
        disconnect(m_stack, SIGNAL(indexChanged(int)), this, SLOT(stackChanged()));
        disconnect(m_stack, SIGNAL(destroyed(QObject*)), this, SLOT(stackDestroyed(QObject*)));
    }
    m_stack = stack;
    if (m_stack != 0)
    {
        connect(m_stack, SIGNAL(cleanChanged(bool)), this, SLOT(stackChanged()));
        connect(m_stack, SIGNAL(indexChanged(int)), this, SLOT(stackChanged()));
        connect(m_stack, SIGNAL(destroyed(QObject*)), this, SLOT(stackDestroyed(QObject*)));
    }

    stackChanged();
}

void SCgUndoViewModel::stackDestroyed(QObject *obj)
{
    if (obj != m_stack)
        return;
    m_stack = 0;

    stackChanged();
}

void SCgUndoViewModel::stackChanged()
{
    beginResetModel();
    endResetModel();
    m_sel_model->setCurrentIndex(selectedIndex(), QItemSelectionModel::ClearAndSelect);
}

void SCgUndoViewModel::setStackCurrentIndex(const QModelIndex &index)
{
    if (m_stack == 0)
        return;

    if (index == selectedIndex())
        return;

    if (index.column() != 0)
        return;

    m_stack->setIndex(index.row());
}

QModelIndex SCgUndoViewModel::selectedIndex() const
{
    return m_stack == 0 ? QModelIndex() : createIndex(m_stack->index(), 0);
}

QModelIndex SCgUndoViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (m_stack == 0)
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    if (column != 0)
        return QModelIndex();

    if (row < 0 || row > m_stack->count())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex SCgUndoViewModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int SCgUndoViewModel::rowCount(const QModelIndex &parent) const
{
    if (m_stack == 0)
        return 0;

    if (parent.isValid())
        return 0;

    return m_stack->count() + 1;
}

int SCgUndoViewModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant SCgUndoViewModel::data(const QModelIndex &index, int role) const
{
    if (m_stack == 0)
        return QVariant();

    if (index.column() != 0)
        return QVariant();

    if (index.row() < 0 || index.row() > m_stack->count())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
            return m_emty_label;
        return m_stack->text(index.row() - 1);
    } else if (role == Qt::DecorationRole)
    {
        if (index.row() == m_stack->cleanIndex() && !m_clean_icon.isNull())
            return m_clean_icon;
        return QVariant();
    } else if (role == Qt::ForegroundRole && selectedIndex().isValid() && selectedIndex().row() < index.row())
    {
        return QBrush(Qt::gray);
    }

    return QVariant();
}

QString SCgUndoViewModel::emptyLabel() const
{
    return m_emty_label;
}

void SCgUndoViewModel::setEmptyLabel(const QString &label)
{
    m_emty_label = label;
    stackChanged();
}

void SCgUndoViewModel::setCleanIcon(const QIcon &icon)
{
    m_clean_icon = icon;
    stackChanged();
}

QIcon SCgUndoViewModel::cleanIcon() const
{
    return m_clean_icon;
}
