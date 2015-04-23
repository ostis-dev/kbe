/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include "interfaces/plugininterface.h"

class QTranslator;

class SCgPlugin : public QObject,
                  public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID "com.OSTIS.kbe.PluginInterface" FILE "scgplugin.json")

public:
    explicit SCgPlugin(QObject *parent = 0);
    virtual ~SCgPlugin();

protected:
    //! @copydoc PluginInterface::name
    QString const & name() const;
    //! @copydoc PluginInterface::version
    QString const & version() const;
    //! @copydoc PluginInterface::interfaces
    QList<QObject*> const & interfaces() const;
    //! @copydoc PluginInterface::initialize
    void initialize();
    //! @copydoc PluginInterface::shutdown
    void shutdown();
    //! @copydoc PluginInterface::settingsWidget
    QWidget * settingsWidget() const;

private:
    QList<QObject*> mInterfaces;

    //! Pointer to plugin translator
    QTranslator *mTranslator;

signals:

public slots:

};


