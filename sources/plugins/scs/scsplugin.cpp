/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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

QWidget * SCsPlugin::settingsWidget() const
{
    return 0;
}
