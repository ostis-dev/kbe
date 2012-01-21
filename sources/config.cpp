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

#include "config.h"

QDir Config::pathMedia = QDir("");
QDir Config::pathIcons = QDir("");
QDir Config::pathTranslations = QDir("");

QString Config::settingsRecentFileList = "";
QString Config::settingsDocksGeometry = "";
QString Config::settingsMainWindowGeometry = "";

QMap<QString, QString> Config::ext2MIME = QMap<QString, QString>();


void Config::initSettings() {
    settingsRecentFileList = "RecentFileList";
    settingsDocksGeometry = "DockWindowsGeometry";

    settingsMainWindowGeometry = "MainWindowGeometry";

    //text
    ext2MIME["txt"] = "text/plain";
    //images
    ext2MIME["ico"] = "image/x-icon";
    ext2MIME["png"] = "image/png";
    ext2MIME["bmp"] = "image/bmp";
    ext2MIME["gif"] = "image/gif";
    ext2MIME["jpeg"] = "image/jpeg";
    ext2MIME["jpg"] = "image/jpeg";
    ext2MIME["jpe"] = "image/jpeg";
    ext2MIME["svg"] = "image/svg+xml";
    ext2MIME["tiff"] = "image/tiff";
    ext2MIME["tif"] = "image/tiff";
    ext2MIME["mng"] = "image/x-jng";
    ext2MIME["pbm"] = "image/pbm";
    ext2MIME["pgm"] = "image/x-pgm";
    ext2MIME["ppm"] = "image/x-ppm";
    ext2MIME["xbm"] = "image/x-xbm";
    ext2MIME["xpm"] = "image/x-xpixmap";
    //application
    ext2MIME["swf"] = "application/x-shockwave-flash";

}
