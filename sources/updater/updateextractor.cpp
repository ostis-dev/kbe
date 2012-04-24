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

#include "updateextractor.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>

#include <zzip/lib.h>

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
    QFileInfo di(directory);
    if (!di.isDir())
        return false;

    QDir _d(".");
    if (di.exists())
        _d.rmdir(directory);

    _d.mkpath(directory);

    // open archive
    ZZIP_DIR *dir = zzip_opendir(archive.toStdString().c_str());
    if (dir != 0)
    {
        QStringList files;
        // collect all files
        ZZIP_DIRENT dirent;
        while (zzip_dir_read(dir, &dirent))
            files << dirent.d_name;



        zzip_closedir(dir);
    }
}
