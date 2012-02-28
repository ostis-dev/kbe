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

#include "m4scpplugin.h"
#include "m4scpsyntax.h"
#include "m4scpfileloader.h"
#include "m4scpfilewriter.h"

#include <QDir>

Q_EXPORT_PLUGIN2(m4scp, M4SCpPlugin)

QString M4SCpPlugin::mMediaPath = QString();

M4SCpPlugin::M4SCpPlugin(QObject *parent) :
    QObject(parent)
{
}

M4SCpPlugin::~M4SCpPlugin()
{
}

const QString& M4SCpPlugin::name() const
{
    static QString name = "m4scp";
    return name;
}

const QString& M4SCpPlugin::version() const
{
    static QString version = "0.1.0";
    return version;
}

const QList<QObject*>& M4SCpPlugin::interfaces() const
{
    return mInterfaces;
}

void M4SCpPlugin::initialize(const QString &mediaPath)
{
    M4SCpSyntax::initialize();

    QDir dir = mediaPath;
    dir.cd("m4scp");
    mMediaPath = dir.absolutePath();

    mInterfaces.push_back(new M4SCpFileLoaderFactory(this));
    mInterfaces.push_back(new M4SCpFileWriterFactory(this));
}

void M4SCpPlugin::shutdown()
{

}

QString M4SCpPlugin::mediaPath()
{
    return mMediaPath;
}
