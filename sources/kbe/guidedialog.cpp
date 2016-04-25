/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "guidedialog.h"
#include "config.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QSettings>
#include <QPushButton>

GuideDialog::GuideDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    QTextBrowser *browser = new QTextBrowser(this);
    browser->setSource(QUrl("qrc:/media/startup/index.html"));

    vlayout->addWidget(browser);

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    QCheckBox *showCheckBox = new QCheckBox(tr("Show on startup"), this);
    QPushButton *closeButton = new QPushButton(tr("Close"), this);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(showCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showStateChanged(int)));

    QSettings settings;
    showCheckBox->setChecked(settings.value(Config::settingsShowStartupDialog).toBool());

    hlayout->addWidget(showCheckBox);
    hlayout->addWidget(closeButton);

    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    setFixedSize(575, 500);
}

GuideDialog::~GuideDialog()
{
}

void GuideDialog::showStateChanged(int state)
{
    QSettings settings;
    settings.setValue(Config::settingsShowStartupDialog, QVariant(state == Qt::Checked));
}
