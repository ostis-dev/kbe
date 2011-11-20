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

#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QSplashScreen>
#include <QMessageBox>

#include "readwritemanager.h"
#include "config.h"
#include "platform.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("OSTIS");
    a.setOrganizationDomain("ostis.net");
    a.setApplicationName("KBE");

    a.setAttribute(Qt::AA_DontShowIconsInMenus, false);
    QDir root_dir = a.applicationDirPath();
#if KBE_DEBUG_MODE
    QDir tmp(root_dir.absolutePath());
    if(!tmp.cd("media"))
        root_dir.cdUp();
#endif
    Config::pathMedia = root_dir;
    Config::pathMedia.cd("media");
    Config::pathIcons = Config::pathMedia;
    Config::pathIcons.cd("icons");
    Config::pathTranslations = Config::pathMedia;
    Config::pathTranslations.cd("langs");

    // Create splash screen
    //QSplashScreen splash(QPixmap(QFileInfo(QDir(Config::pathMedia), "splash.png").absoluteFilePath()));
    //splash.show();
    //a.processEvents();

    //splash.showMessage("Load Translation", Qt::AlignBottom | Qt::AlignHCenter);

    QTranslator myappTranslator;
    myappTranslator.load("lang_" + QLocale::system().name(), Config::pathTranslations.absolutePath());
    a.installTranslator(&myappTranslator);

    //splash.showMessage(a.tr("Create interface"), Qt::AlignBottom | Qt::AlignHCenter);
    MainWindow::getInstance()->show();

    QList<QString> formats = ReadWriteManager::instance().registeredLoaderExtensions();
    for(int i = 1; i < argc; i++)
    {
        QString arg = a.arguments().at(i);
        if(formats.contains(arg.mid(arg.lastIndexOf('.') + 1)))
            MainWindow::getInstance()->load(arg);
        else
            QMessageBox::information(0, qAppName(),QObject::tr("Error while opening file: \n")+
                            arg + QObject::tr("\n\nUnsupported file format."));
    }

    //splash.finish(&w);
    return a.exec();
}
