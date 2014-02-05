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

#include "scsplugin.h"
#include "scswindow.h"

#include <QDir>

SCsPlugin::SCsPlugin(QObject *parent) :
    QObject(parent)
{
}

SCsPlugin::~SCsPlugin()
{
}

const QString& SCsPlugin::name() const
{
    static QString name = "scs";
    return name;
}

const QString& SCsPlugin::version() const
{
    static QString version = "0.1.0";
    return version;
}

const QList<QObject*>& SCsPlugin::interfaces() const
{
    return mInterfaces;
}

void SCsPlugin::initialize()
{
    mInterfaces.push_back(new SCsWindowFactory(this));
}

void SCsPlugin::shutdown()
{
    QObject *obj = 0;
    foreach(obj, mInterfaces)
        delete obj;

    mInterfaces.clear();
}
