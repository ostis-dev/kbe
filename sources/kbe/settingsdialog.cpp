/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "settingsdialog.h"
#include "pluginmanager.h"

#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget * parent)
    : QDialog(parent)
    , mGeneralTab(0)
{
    setWindowTitle(tr("Settings"));

    mTabWidget = new QTabWidget();
    mTabWidget->setMinimumWidth(800);
    mTabWidget->setMinimumHeight(450);

    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(mButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mTabWidget);
    mainLayout->addWidget(mButtonBox);

    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog()
{

}

void SettingsDialog::createGeneralTab()
{
    mGeneralTab = new QWidget(this);
}

void SettingsDialog::initialize()
{
    createGeneralTab();
    mTabWidget->addTab(mGeneralTab, tr("General"));

    PluginManager::tSettingWidgetsMap const & widgets = PluginManager::instance()->getSettingWidgets();
    PluginManager::tSettingWidgetsMap::const_iterator it = widgets.begin();
    for (; it != widgets.end(); ++it)
        mTabWidget->addTab(it.value(), it.key());
}
