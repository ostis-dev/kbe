/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "pluginmanager.h"
#include "config.h"
#include "platform.h"
#include "mainwindow.h"
#include "guidedialog.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QSplashScreen>
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


    // Create splash screen
    //QSplashScreen splash(QPixmap(QFileInfo(QDir(Config::pathMedia), "splash.png").absoluteFilePath()));
    //splash.show();
    //a.processEvents();

    //splash.showMessage("Load Translation", Qt::AlignBottom | Qt::AlignHCenter);

    QTranslator myappTranslator;
    myappTranslator.load(":/media/translations/lang_" + QLocale::system().name() + ".qm");
    a.installTranslator(&myappTranslator);

    //splash.showMessage(a.tr("Create interface"), Qt::AlignBottom | Qt::AlignHCenter);
    MainWindow::getInstance()->show();

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

    //splash.finish(&w);
    return a.exec();
}
