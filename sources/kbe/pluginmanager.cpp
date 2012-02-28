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

#include "pluginmanager.h"
#include "interfaces/plugininterface.h"
#include "interfaces/fileloaderinterface.h"
#include "interfaces/filewriterinterface.h"
#include "readwritemanager.h"
#include "config.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QPluginLoader>

PluginManager* PluginManager::mInstance = 0;

PluginManager::PluginManager(QObject *parent) :
    QObject(parent)
{
    Q_ASSERT(mInstance == 0);
    mInstance = this;
}

PluginManager::~PluginManager()
{
    Q_ASSERT(mInstance != 0);
    mInstance = 0;
}

PluginManager* PluginManager::instance()
{
    return mInstance;
}

void PluginManager::initialize(const QString &_dirPath)
{

    //! TODO: reutrn error
    if (!QDir(_dirPath).exists()) return;

    QDir pluginsDir(_dirPath);

    QDirIterator dirIt(_dirPath, QDirIterator::Subdirectories);

    while (dirIt.hasNext())
    {
        QString fileName = dirIt.next();
        QFileInfo fionfo(fileName);

        // skip non file objetcs
        if (!fionfo.isFile()) continue;

        try
        {
            loadPlugin(fileName);
        }catch (...)
        {
            qDebug() << "Can't load plugin from " << pluginsDir.absoluteFilePath(fileName);
        }
    }
}

void PluginManager::shutdown()
{

}

void PluginManager::loadPlugin(const QString &path)
{
    qDebug() << "Load plugin: " << path;

    Q_ASSERT(mPluginLoaders.find(path) == mPluginLoaders.end());

    QPluginLoader *loader = new QPluginLoader(path, this);

    if (!loader->load())
    {
        qDebug() << loader->errorString();
        qDebug() << QString("Can't load plugin '%1'").arg(path);
    }

    // process instances
    PluginInterface *plugInterface = qobject_cast<PluginInterface*>(loader->instance());
    if (plugInterface != 0)
    {
        mPluginLoaders[path] = loader;
        processLoadPlugin(plugInterface);
    }else
    {
        delete loader;
        qDebug() << QString("There are no plugin interface in '%1'").arg(path);
    }

}

void PluginManager::processLoadPlugin(PluginInterface *pluginInterface)
{
    // iterate all interfaces in plugin and register them in managers
    Q_ASSERT(pluginInterface != 0);

    pluginInterface->initialize(Config::pathMedia.absolutePath());

    const QList<QObject*> &interfaces = pluginInterface->interfaces();
    QObject *_interface;
    foreach(_interface, interfaces)
    {
        // components factory
        FileLoaderFactoryInterface *fileLoaderFactory = qobject_cast<FileLoaderFactoryInterface*>(_interface);
        if (fileLoaderFactory != 0)
        {
            ReadWriteManager::instance()->registerFileLoaderFactory(fileLoaderFactory);
            continue;
        }

        FileWriterFactoryInterface *fileWriterFactory = qobject_cast<FileWriterFactoryInterface*>(_interface);
        if (fileWriterFactory != 0)
        {
            ReadWriteManager::instance()->registerFileWriterFactory(fileWriterFactory);
            continue;
        }

        // interface can't be handled
        qWarning() << "Can't prosess interface: " << _interface;
    }
}
