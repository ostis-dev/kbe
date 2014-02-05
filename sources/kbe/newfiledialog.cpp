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

#include "newfiledialog.h"
#include "pluginmanager.h"
#include "interfaces/editorinterface.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QListWidget>
#include <QKeyEvent>
#include <QtWidgets/QPushButton>
#include <QPair>

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Select new File"));
    QVBoxLayout *lay = new QVBoxLayout;
    QLabel *lab = new QLabel(tr("List of available formats:"));

    mAvailableTypesList = new QListWidget(this);
    mAvailableTypesList->setSelectionMode(QAbstractItemView::SingleSelection);
    mAvailableTypesList->setIconSize(QSize(32, 32));

    QList<EditorFactoryInterface*> factories = PluginManager::instance()->editorFactoriesByType().values();
    QList<EditorFactoryInterface*>::iterator it, itEnd = factories.end();

    QPair<QListWidgetItem *, QString> pairToolTip;

    for (it = factories.begin(); it != itEnd; ++it)
    {
        /// @todo add custom icon and tooltip support.
        QListWidgetItem *itemToAdd = new QListWidgetItem((*it)->icon(), (*it)->name());
        itemToAdd->setData(EditorTypeRole, (*it)->name());
        itemToAdd->setToolTip((*it)->getDescription());
/*
        pairToolTip.first = itemToAdd;
        pairToolTip.second = "Plug-in for creating and editing " + (*it)->name() + " texts";
        itemToAdd->setToolTip(pairToolTip.second);
*/
        mAvailableTypesList->addItem(itemToAdd);
    }

    QHBoxLayout *buttonLay = new QHBoxLayout;
    QPushButton *butOk = new QPushButton(tr("OK"));

    if (mAvailableTypesList->count() > 0)
        mAvailableTypesList->item(0)->setSelected(true);
    else
        butOk->setEnabled(false);

    QPushButton *butCancel = new QPushButton(tr("Cancel"));

    buttonLay->addWidget(butOk, 1, Qt::AlignRight);
    buttonLay->addWidget(butCancel, 1, Qt::AlignRight);

    lay->addWidget(lab);
    lay->addWidget(mAvailableTypesList);
    lay->addLayout(buttonLay);
    setLayout(lay);

    connect(butOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(mAvailableTypesList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
    connect(butCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

NewFileDialog::~NewFileDialog()
{
}

QString NewFileDialog::selectedEditor() const
{
    return mAvailableTypesList->selectedItems().at(0)->data(EditorTypeRole).toString();
}
