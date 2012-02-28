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


#include "readwritemanager.h"
#include <QRegExp>
#include <QVector>

ReadWriteManager* ReadWriteManager::mInstance = 0;

ReadWriteManager::ReadWriteManager(QObject *parent) :
    QObject(parent)
{
    Q_ASSERT(mInstance == 0);
    mInstance = this;
}

ReadWriteManager::~ReadWriteManager()
{
    unregisterAllFactories();

    Q_ASSERT(mInstance != 0);
    mInstance = 0;
}

ReadWriteManager* ReadWriteManager::instance()
{
    return mInstance;
}


QString ReadWriteManager::extFromFilter(const QString &filter)
{
    //! TODO: use regular expression
    int pos = filter.indexOf("*.");
    Q_ASSERT_X(pos != -1, "ReadWriteManager::extFromFilter", "Can't find begin of extension");
    pos += 2;
    int pos2 = filter.indexOf(")", pos);
    Q_ASSERT_X(pos2 != -1, "ReadWriteManager::extFromFilter", "Can't find end of extension");
    return filter.mid(pos, pos2 - pos).trimmed();
}

void ReadWriteManager::registerFileLoaderFactory(FileLoaderFactoryInterface *factory)
{
    Q_ASSERT_X(factory != 0, "ReadWriteManager::registerFileLoaderFactory", "factory is null");
    QList<QString> ext = factory->extensions();
    for (QList<QString>::iterator it = ext.begin(); it != ext.end(); ++it)
    {
        Q_ASSERT_X(mFileLoaderFactories.find(*it) == mFileLoaderFactories.end(),
                   "ReadWriteManager::registerFileLoaderFactory",
                   "Factory for extension is already registered");
        if (it != ext.begin())
            mFileLoaderFactories[*it] = factory->clone();
        else
            mFileLoaderFactories[*it] = factory;
    }
}

void ReadWriteManager::registerFileWriterFactory(FileWriterFactoryInterface *factory)
{
    Q_ASSERT_X(factory != 0, "ReadWriteManager::registerFileWriterFactory", "Factory is null");
    QList<QString> ext = factory->extensions();
    for (QList<QString>::iterator it = ext.begin(); it != ext.end(); ++it)
    {
        Q_ASSERT_X(mFileWriteFactories.find(*it) == mFileWriteFactories.end(),
                   "ReadWriteManager::registerFileWriterFactory",
                   "Factory for extension is already registered");
        if (it != ext.begin())
            mFileWriteFactories[*it] = factory->clone();
        else
            mFileWriteFactories[*it] = factory;
    }
}

void ReadWriteManager::unregisterAllFactories()
{
    StringFileLoaderFactoryMap::iterator it1 = mFileLoaderFactories.begin();
    for (; it1 != mFileLoaderFactories.end(); ++it1)
        delete it1.value();
    mFileLoaderFactories.clear();

    StringFileWriterFactoryMap::iterator it2 = mFileWriteFactories.begin();
    for (; it2 != mFileWriteFactories.end(); ++it2)
        delete it2.value();
    mFileWriteFactories.clear();
}

FileLoaderInterface* ReadWriteManager::createLoader(const QString &ext)
{
    Q_ASSERT_X(mFileLoaderFactories.find(ext) != mFileLoaderFactories.end(),
               "ReadWriteManager::createLoader",
               "Can't find file extension");
    return mFileLoaderFactories[ext]->createInstance();
}

FileWriterInterface* ReadWriteManager::createWriter(const QString &ext)
{
    Q_ASSERT_X(mFileWriteFactories.find(ext) != mFileWriteFactories.end(),
               "ReadWriteManager::createWriter",
               "Can't find file extension");
    return mFileWriteFactories[ext]->createInstance();
}

QString ReadWriteManager::openFilters() const
{
    return loaderFilters(FileLoaderInterface::LT_Open);
}

QString ReadWriteManager::saveFilters() const
{
    return writerFilters(FileWriterInterface::WT_Save);
}

QString ReadWriteManager::importFilters() const
{
    return loaderFilters(FileLoaderInterface::LT_Import);
}

QString ReadWriteManager::exportFilters() const
{
    return writerFilters(FileWriterInterface::WT_Export);
}

QList<QString> ReadWriteManager::registeredLoaderExtensions() const
{
    return mFileLoaderFactories.keys();
}

QList<QString> ReadWriteManager::registeredWriterExtensions() const
{
    return mFileWriteFactories.keys();
}

QString ReadWriteManager::loaderFilters(FileLoaderInterface::Type type) const
{
    QString filters;
    StringFileLoaderFactoryMap::const_iterator it = mFileLoaderFactories.begin();
    for (; it != mFileLoaderFactories.end(); ++it)
    {
        if (it.value()->type() != type) continue;
        if (!filters.isEmpty())
            filters += "\n";
        filters += QString("%1 (*.%2)").arg(it.value()->formatDescription(it.key())).arg(it.key());
    }
    if (!filters.isEmpty())
        filters += "\n";
    filters += tr("All files (*.*)");

    return filters;
}

QString ReadWriteManager::writerFilters(FileWriterInterface::Type type) const
{
    QString filters;
    StringFileWriterFactoryMap::const_iterator it = mFileWriteFactories.begin();
    for (; it != mFileWriteFactories.end(); ++it)
    {
        if (it.value()->type() != type) continue;
        if (!filters.isEmpty())
            filters += "\n";
        filters += QString("%1 (*.%2)").arg(it.value()->formatDescription(it.key())).arg(it.key());
    }
    if (!filters.isEmpty())
        filters += "\n";
    filters += tr("All files (*.*)");

    return filters;
}
