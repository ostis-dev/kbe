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
#include "m4scpwindow.h"

#include <QDir>
#include <QTranslator>
#include <QApplication>
#include <QLocale>

Q_EXPORT_PLUGIN2(m4scp, M4SCpPlugin)

M4SCpPlugin::M4SCpPlugin(QObject *parent) :
    QObject(parent),
    mTranslator(0)
{
    mTranslator = new QTranslator(this);
    mTranslator->load(":/m4scp/media/translations/m4scp_" + QLocale::system().name());
}

M4SCpPlugin::~M4SCpPlugin()
{
    delete mTranslator;
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

void M4SCpPlugin::initialize()
{
    M4SCpSyntax::initialize();

    mInterfaces.push_back(new M4SCpWindowFactory(this));

    qApp->installTranslator(mTranslator);
}

void M4SCpPlugin::shutdown()
{
    QObject *obj = 0;
    foreach(obj, mInterfaces)
        delete obj;

    mInterfaces.clear();

    qApp->removeTranslator(mTranslator);
}
