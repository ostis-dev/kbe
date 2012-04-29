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
#include <QDir>

#include "updatewindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("OSTIS");
    a.setOrganizationDomain("ostis.net");
    a.setApplicationName("updater");

    QDir root_dir = a.applicationDirPath();

    if (a.arguments().size() < 2)
        return 0;

    UpdateWindow window(a.arguments().at(1));
    window.setFixedWidth(300);
    window.show();

    //splash.finish(&w);
    return a.exec();
}

