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

#include "extendedundoviewmodel.h"

#include <QUndoStack>
#include <QItemSelectionModel>
#include <QBrush>

ExtendedUndoViewModel::ExtendedUndoViewModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_stack = 0;
    m_sel_model = new QItemSelectionModel(this, this);
    connect(m_sel_model, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(setStackCurrentIndex(QModelIndex)));
    m_emty_label = tr("<empty>");
}

QItemSelectionModel *ExtendedUndoViewModel::selectionModel() const
{
    return m_sel_model;
}

QUndoStack *ExtendedUndoViewModel::stack() const
{
    return m_stack;
}

void ExtendedUndoViewModel::setStack(QUndoStack *stack)
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

void ExtendedUndoViewModel::stackDestroyed(QObject *obj)
{
    if (obj != m_stack)
        return;
    m_stack = 0;

    stackChanged();
}

void ExtendedUndoViewModel::stackChanged()
{
    reset();
    m_sel_model->setCurrentIndex(selectedIndex(), QItemSelectionModel::ClearAndSelect);
}

void ExtendedUndoViewModel::setStackCurrentIndex(const QModelIndex &index)
{
    if (m_stack == 0)
        return;

    if (index == selectedIndex())
        return;

    if (index.column() != 0)
        return;

    m_stack->setIndex(index.row());
}

QModelIndex ExtendedUndoViewModel::selectedIndex() const
{
    return m_stack == 0 ? QModelIndex() : createIndex(m_stack->index(), 0);
}

QModelIndex ExtendedUndoViewModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex ExtendedUndoViewModel::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int ExtendedUndoViewModel::rowCount(const QModelIndex &parent) const
{
    if (m_stack == 0)
        return 0;

    if (parent.isValid())
        return 0;

    return m_stack->count() + 1;
}

int ExtendedUndoViewModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant ExtendedUndoViewModel::data(const QModelIndex &index, int role) const
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

QString ExtendedUndoViewModel::emptyLabel() const
{
    return m_emty_label;
}

void ExtendedUndoViewModel::setEmptyLabel(const QString &label)
{
    m_emty_label = label;
    stackChanged();
}

void ExtendedUndoViewModel::setCleanIcon(const QIcon &icon)
{
    m_clean_icon = icon;
    stackChanged();
}

QIcon ExtendedUndoViewModel::cleanIcon() const
{
    return m_clean_icon;
}
