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

class QPluginLoader;
class PluginInterface;
class EditorInterface;
class EditorFactoryInterface;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    virtual ~PluginManager();

    static PluginManager* instance();

private:
    static PluginManager *mInstance;

public:
<<<<<<< HEAD
=======
    typedef QMap<QString, QPluginLoader*> tPluginLoadersMap;
    typedef QSet<QString> tExtensionsSet;
    typedef QMap<QString, EditorFactoryInterface*> tEditorFactoryInterfacesMap;

public:
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417

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

<<<<<<< HEAD
    //! Return list of supported file extensions
    const QSet<QString>& supportedFilesExt() const;

    /*! Create editor for specified file extension
      * @param ext File extension
      * @return Return pointer to created window
      */
    EditorInterface* createWindow(const QString &ext);
=======
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
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417

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

<<<<<<< HEAD
protected:
    //! Map of used plugin loaders
    QMap<QString, QPluginLoader*> mPluginLoaders;
    //! List of supported extensions
    QSet<QString> mSupportedExtensions;
    //! Registered factories
    QMap<QString, EditorFactoryInterface*> mEditorFactories;
=======

protected:
    //! Map of used plugin loaders
    tPluginLoadersMap mPluginLoaders;
    //! List of supported extensions
    tExtensionsSet mSupportedExtensions;
    //! Registered factories by types
    tEditorFactoryInterfacesMap mEditorFactoriesByType;
    //! REgistered factories by extinsions
    tEditorFactoryInterfacesMap mEditorFactoriesByExt;
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417

signals:

public slots:

};

#endif // PLUGINMANAGER_H
