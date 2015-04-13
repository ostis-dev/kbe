/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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

