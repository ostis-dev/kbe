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
#include "config.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QSettings>
#include <QPushButton>
#include <QDebug>
#include <QDesktopServices>
#include <QString>
#include <QApplication>

GuideDialog::GuideDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Welcome to KBE 3.1"));

    QVBoxLayout *vlayout = new QVBoxLayout(this);

    browser = new QTextBrowser(this);
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

    setFixedSize(875, 500);

    connect(browser, SIGNAL(anchorClicked(QUrl)), this, SLOT(openRef(QUrl)));
}

GuideDialog::~GuideDialog()
{
}

void GuideDialog::showStateChanged(int state)
{
    QSettings settings;
    settings.setValue(Config::settingsShowStartupDialog, QVariant(state == Qt::Checked));
}

void GuideDialog::openRef(QUrl url)
{
    QString urlString = url.toString();
    QString urlStringRigth = urlString;
    urlString.resize(4);

    if (urlString != "http")
    {        
        QString pathDir = QApplication::applicationDirPath();
        int i = pathDir.lastIndexOf("kbe");
        pathDir.resize(i + 4);
        pathDir += "sources/kbe/";
        urlStringRigth.remove(0,5);
        pathDir += urlStringRigth;
        QDesktopServices::openUrl(QUrl(pathDir));
    }
    else
        QDesktopServices::openUrl(url);

    browser->setSource(QUrl("qrc:/media/startup/index.html"));
}
