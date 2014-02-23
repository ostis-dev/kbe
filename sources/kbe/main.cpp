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

#include "pluginmanager.h"
#include "config.h"
#include "platform.h"
#include "mainwindow.h"
#include "guidedialog.h"
#include "splashscreen.h"

#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("OSTIS");
    a.setOrganizationDomain("ostis.net");
    a.setApplicationName("KBE");

    a.setAttribute(Qt::AA_DontShowIconsInMenus, false);
    QDir root_dir = a.applicationDirPath();

    //#if KBE_DEBUG_MODE
    //    root_dir.cdUp();
    //#endif
    Config::pathPlugins = root_dir;
    Config::pathPlugins.cd("plugins");
    new PluginManager();

    // Create splash screen
    SplashScreen splash(QPixmap(QFileInfo(QDir(root_dir), "splash.png").absoluteFilePath()));
    QObject::connect(PluginManager::instance(), SIGNAL(loadingProgressChanged(quint8)), &splash, SLOT(setProgressAll(quint8)));
    QObject::connect(PluginManager::instance(), SIGNAL(pluginLoadingProgressChanged(quint8)), &splash, SLOT(setPluginProgress(quint8)));
    splash.show();
    a.processEvents();

    splash.showMessage("Load Translation", Qt::AlignBottom | Qt::AlignHCenter);

    QTranslator myappTranslator;
    myappTranslator.load(":/media/translations/lang_" + QLocale::system().name() + ".qm");
    a.installTranslator(&myappTranslator);

    splash.showMessage(a.tr("Create interface"), Qt::AlignBottom | Qt::AlignHCenter);

    a.processEvents();

    for(int i = 1; i < argc; i++)
    {
        QString arg = a.arguments().at(i);
        MainWindow::getInstance()->load(arg);
    }

    QSettings settings;
    // check if startup dialog property exist
    if (!settings.contains(Config::settingsShowStartupDialog))
        settings.setValue(Config::settingsShowStartupDialog, QVariant(true));

    MainWindow::getInstance()->updateWindowTitle();

    // show startup dialog
//    if (settings.value(SETTINGS_STARTUP_DIALOG_SHOW).toBool())
//    {
//        GuideDialog startDialog(MainWindow::getInstance());
//        startDialog.exec();
//    }

    MainWindow::getInstance()->show();
    splash.finish(MainWindow::getInstance());
    return a.exec();
}
