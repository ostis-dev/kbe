/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "config.h"

QDir Config::pathPlugins = QDir("");

const QString Config::settingsApplicationRoot = "/kbe";

const QString Config::settingsRecentFileList = Config::settingsApplicationRoot + "/RecentFileList";
const QString Config::settingsDocksGeometry = Config::settingsApplicationRoot +"/DockWindowsGeometry";
const QString Config::settingsMainWindowGeometry = Config::settingsApplicationRoot +"/MainWindowGeometry";
const QString Config::settingsShowStartupDialog = Config::settingsApplicationRoot +"/StartupDialog/Show";
