/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef CONFIG_H
#define CONFIG_H

#include <QDir>
#include <QString>

class Config
{
public:
    //! path to plugins
    static QDir pathPlugins;

    /*! @defgroup settingNames Names For Saving Application Parameters
     *  @note Used with QSettings.
     *  @{
     */

    //! Application root setting name
    static const QString settingsApplicationRoot;
    //! Key name for storing recent file list.
    static const QString settingsRecentFileList;
    //! Root setting key name for Dock Geometries.
    static const QString settingsDocksGeometry;
    //! Key for storing main window geometry
    static const QString settingsMainWindowGeometry;
    //! Key for saving value indicating whether the guide dialog appears on startupt.
    static const QString settingsShowStartupDialog;
    /*! @}*/
};

#endif // CONFIG_H
