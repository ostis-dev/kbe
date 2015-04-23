/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "pluginmanager.h"
#include "interfaces/plugininterface.h"
#include "interfaces/editorinterface.h"
#include "config.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QPluginLoader>
#include <QWidget>

PluginManager* PluginManager::mInstance = 0;

PluginManager::PluginManager(QObject * parent) :
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

void PluginManager::initialize(QString const & _dirPath)
{

    //! TODO: reutrn error
    if (!QDir(_dirPath).exists())
        return;

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

void PluginManager::loadPlugin(QString const & path)
{
    qDebug() << "Load plugin: " << path;

    Q_ASSERT(mPluginLoaders.find(path) == mPluginLoaders.end());

    QPluginLoader * loader = new QPluginLoader(path, this);

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

void PluginManager::processLoadPlugin(PluginInterface * pluginInterface)
{
    // iterate all interfaces in plugin and register them in managers
    Q_ASSERT(pluginInterface != 0);

    pluginInterface->initialize();

    QList<QObject*> const & interfaces = pluginInterface->interfaces();
    QObject *_interface;
    foreach(_interface, interfaces)
    {
        EditorFactoryInterface * factory = qobject_cast<EditorFactoryInterface*>(_interface);
        if (factory != 0)
        {
            QString type = factory->name();
            Q_ASSERT(mEditorFactoriesByType.find(type) == mEditorFactoriesByType.end());
            mEditorFactoriesByType[type] = factory;

            QStringList extList = factory->supportedFormatsExt();
            QString ext;
            foreach(ext, extList)
            {
                mSupportedExtensions << ext;
                mEditorFactoriesByExt[ext] = factory;
            }
        }
        else
        {
            // interface can't be handled
            qWarning() << "Can't prosess interface: " << _interface;
        }
    }

    Q_ASSERT(mSettingWidgets.find(pluginInterface->name()) == mSettingWidgets.end());

    QWidget * settings = pluginInterface->settingsWidget();
    if (settings)
        mSettingWidgets[pluginInterface->name()] = settings;

}

QString PluginManager::openFilters() const
{
    QString filters, allFormats;
    tExtensionsSet::const_iterator it;
    for (it = mSupportedExtensions.begin(); it != mSupportedExtensions.end(); ++it)
    {
        if (!filters.isEmpty())
        {
            filters += "\n";
            allFormats += " ";
        }

        filters += QString("%1 format (*.%1)").arg(*it);
        allFormats += QString("*.%1").arg(*it);
    }

    if (!filters.isEmpty())
        filters += "\n";
    filters += tr("All files") + "*.*";

    filters = tr("All supported files") + QString("(%1)\n").arg(allFormats) + filters;

    return filters;
}

QString PluginManager::saveFilters(QStringList const & supExtensions) const
{
    QString filters;
    QStringList::const_iterator it;
    for (it = supExtensions.begin(); it != supExtensions.end(); ++it)
    {
        if (!filters.isEmpty())
            filters += "\n";
        filters += QString("%1 format (*.%1)").arg(*it);
    }

    return filters;
}

EditorInterface* PluginManager::createWindowByType(QString const & type)
{
    // trying to find factory
    tEditorFactoryInterfacesMap::iterator it = mEditorFactoriesByType.find(type);

    Q_ASSERT(it != mEditorFactoriesByType.end());

    return (*it)->createInstance();
}


EditorInterface* PluginManager::createWindowByExt(QString const & ext)
{
    // trying to find factory
    tEditorFactoryInterfacesMap::iterator it = mEditorFactoriesByExt.find(ext);

    Q_ASSERT(it != mEditorFactoriesByExt.end());

    return (*it)->createInstance();
}
