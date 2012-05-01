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

#include "guidedialog.h"

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
    showCheckBox->setChecked(settings.value(SETTINGS_STARTUP_DIALOG_SHOW).toBool());

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
    settings.setValue(SETTINGS_STARTUP_DIALOG_SHOW, QVariant(state == Qt::Checked));
}
