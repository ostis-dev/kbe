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

#include "updateextractor.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QProcess>

UpdateExtractor::UpdateExtractor(QObject *parent) :
    QObject(parent)
{
}

UpdateExtractor::~UpdateExtractor()
{
}

bool UpdateExtractor::extract(const QString &archive, const QString &directory)
{
    QFileInfo fi(archive);

    if (!fi.exists())
        return false;

    // create output directory if it doesn't exist
    QDir _d;
    if (_d.exists(directory))
        _d.rmdir(directory);
    else _d.mkdir(directory);

    QProcess proc;

#ifdef Q_WS_X11
    return proc.execute("unzip", QStringList() << "-o" << archive  << QString("-d %1").arg(directory)) == 0;
#endif

#ifdef Q_WS_WIN
    return proc.execute("7za.exe", QStringList() << "-y" << "x" << QString("-o%1").arg(directory) << archive) == 0;
#endif

}
