/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
    typedef QMap<QString, QPluginLoader*> tPluginLoadersMap;
    typedef QSet<QString> tExtensionsSet;
    typedef QMap<QString, EditorFactoryInterface*> tEditorFactoryInterfacesMap;
    typedef QMap<QString, QWidget*> tSettingWidgetsMap;

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
    QString saveFilters(QStringList const & supExtensions) const;

    //! Return set of supported file extensions
    tExtensionsSet const & getSupportedFilesExt() const { return mSupportedExtensions; }
    //! Return map of registered editor factories by types
    tEditorFactoryInterfacesMap const & getEditorFactoriesByType() const { return mEditorFactoriesByType; }
    //! Return map of registered editor factories by file extensions
    tEditorFactoryInterfacesMap const & getEditorFactoriesByExt() const { return mEditorFactoriesByExt; }
    //! Return map of registered settings widgets
    tSettingWidgetsMap const & getSettingWidgets() const { return mSettingWidgets; }

    /*! Create editor for specified window type
      * @param type String that represents window type
      * @return If window created, then return pointer to it; otherwise returns null.
      */
    EditorInterface * createWindowByType(QString const & type);

    /*! Create editor for specified file extension
     * @param ext File extension
     * @return If window created, then return pointer to it; otherwise returns null.
     */
    EditorInterface * createWindowByExt(QString const & ext);

protected:
    /*! Load plugin with specified \p path
      * @param path Path to plugin
      */
    void loadPlugin(QString const & path);

    /*! Process loaded plugin interface. Get all
      * possible interfaces from it and register them in managers.
      * @param pluginInterface Pointer to plugin interface
      */
    void processLoadPlugin(PluginInterface * pluginInterface);


protected:
    //! Map of used plugin loaders
    tPluginLoadersMap mPluginLoaders;
    //! List of supported extensions
    tExtensionsSet mSupportedExtensions;
    //! Registered factories by types
    tEditorFactoryInterfacesMap mEditorFactoriesByType;
    //! Registered factories by extinsions
    tEditorFactoryInterfacesMap mEditorFactoriesByExt;
    //! Pointer to all settings widgets by names
    tSettingWidgetsMap mSettingWidgets;

signals:

public slots:

};

