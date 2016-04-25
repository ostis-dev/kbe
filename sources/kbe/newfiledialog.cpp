/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "newfiledialog.h"
#include "pluginmanager.h"
#include "interfaces/editorinterface.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QKeyEvent>
#include <QPushButton>

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    QLabel *lab = new QLabel(tr("List of available formats:"));

    mAvailableTypesList = new QListWidget(this);
    mAvailableTypesList->setSelectionMode(QAbstractItemView::SingleSelection);
    mAvailableTypesList->setIconSize(QSize(32, 32));

    QList<EditorFactoryInterface*> factories = PluginManager::instance()->getEditorFactoriesByType().values();
    QList<EditorFactoryInterface*>::iterator it, itEnd = factories.end();

    for (it = factories.begin(); it != itEnd; ++it)
    {
        /// @todo add custom icon and tooltip support.
        QListWidgetItem *itemToAdd = new QListWidgetItem((*it)->icon(), (*it)->name());
        itemToAdd->setData(EditorTypeRole, (*it)->name());
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
