/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scscodecompleter.h"
#include "QStandardItemModel"
#include <QAbstractItemView>

SCsCodeCompleter::SCsCodeCompleter(QObject *parent) :
    QCompleter(parent)
{
    QStandardItemModel *_mItemModel = new QStandardItemModel(parent);
    setModel(_mItemModel);
    popup()->setIconSize(QSize(16, 16));
}

SCsCodeCompleter::~SCsCodeCompleter()
{
}
