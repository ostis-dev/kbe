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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QMap>
#include <QSet>
#include <QStringList>
#include "interfaces/plugininterface.h"

class QPluginLoader;
class EditorInterface;
class EditorFactoryInterface;

class PluginManager : public QObject, public PluginEventListener
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    virtual ~PluginManager();

    static PluginManager* instance();

private:
    static PluginManager *mInstance;

public:
    typedef QMap<QString, QPluginLoader*> tPluginLoadersMap;
    typedef QSet<QString> tExtensionsSet;
    typedef QMap<QString, EditorFactoryInterface*> tEditorFactoryInterfacesMap;

public:

    /*! Initialize plugin manager and all available plugins
      * @param _dirPath Path to directory that contains plugins
      */
    void initialize(const QString &_dirPath);
    //! Unload all plugins and de-initialize plugin manager
    void shutdown();

    /*! Consturct string that contains filters for open dialog
      * and return it
      */
    QString openFilters() const;

    /*! Construct string that contains filters for save dialog
      * based on list of file extensions
      * @param supExtensions List of sopperted file extensions
      */
    QString saveFilters(const QStringList &supExtensions) const;

    //! Return set of supported file extensions
    const tExtensionsSet& supportedFilesExt() const;

    //! Return map of registered editor factories by types
    const tEditorFactoryInterfacesMap& editorFactoriesByType() const;
    //! Return map of registered editor factories by file extensions
    const tEditorFactoryInterfacesMap& editorFactoriesByExt() const;

    /*! Create editor for specified window type
      * @param type String that represents window type
      * @return If window created, then return pointer to it; otherwise returns null.
      */
    EditorInterface* createWindowByType(const QString &type);

    /*! Create editor for specified file extension
     * @param ext File extension
     * @return If window created, then return pointer to it; otherwise returns null.
     */
    EditorInterface* createWindowByExt(const QString &ext);

    void processEvent(PluginEvents event, const QVariant userData);
protected:
    /*! Load plugin with specified \p path
      * @param path Path to plugin
      */
    void loadPlugin(const QString &path);

    /*! Process loaded plugin interface. Get all
      * possible interfaces from it and register them in managers.
      * @param pluginInterface Pointer to plugin interface
      */
    void processLoadPlugin(PluginInterface *pluginInterface);


protected:
    //! Map of used plugin loaders
    tPluginLoadersMap mPluginLoaders;
    //! List of supported extensions
    tExtensionsSet mSupportedExtensions;
    //! Registered factories by types
    tEditorFactoryInterfacesMap mEditorFactoriesByType;
    //! Registered factories by extinsions
    tEditorFactoryInterfacesMap mEditorFactoriesByExt;

signals:
    //! Emit when new plugin loading started
    void pluginLoadingStarted();
    //! Emit when plugin loading percentage changed
    void pluginLoadingProgressChanged(const quint8 percentage);
    //! Emit when plugin loading finshed
    void pluginLoadingFinished();
    //! Emit when total progress changed
    void loadingProgressChanged(const quint8 percentage);
public slots:

};

#endif // PLUGINMANAGER_H
