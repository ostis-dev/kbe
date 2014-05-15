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

#include "scnplugin.h"
#include "scnwindow.h"

Q_EXPORT_PLUGIN2(scn, SCnPlugin)

SCnPlugin::SCnPlugin(QObject *parent) :
    QObject(parent)
{
}

SCnPlugin::~SCnPlugin()
{
}

const QString& SCnPlugin::name() const
{
    static QString name = "scn";
    return name;
}

const QString& SCnPlugin::version() const
{
    static QString version = "0.1.0";
    return version;
}

const QList<QObject*>& SCnPlugin::interfaces() const
{
    return mInterfaces;
}

void SCnPlugin::initialize()
{
    mInterfaces.push_back(new SCnWindowFactory(this));
}

void SCnPlugin::shutdown()
{

    QObject *interface = 0;
    foreach(interface, mInterfaces)
        delete interface;
    mInterfaces.clear();
}
