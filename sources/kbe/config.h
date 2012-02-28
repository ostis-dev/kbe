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

#ifndef CONFIG_H
#define CONFIG_H

#include <QDir>
#include <QString>

class Config
{
public:
    //! path to media
    static QDir pathMedia;
    //! path to icons
    static QDir pathIcons;
    //! path to translations
    static QDir pathTranslations;
    //! path to plugins
    static QDir pathPlugins;

    /*! @defgroup settingNames Names For Saving Application Parameters
     *  @note Used with QSettings.
     *  @{
     */

    //! Setting name for recent file list.
    static const QString settingsRecentFileList;
    static const QString settingsDocksGeometry;
    static const QString settingsMainWindowGeometry;
    /*! @}*/
};

#endif // CONFIG_H
