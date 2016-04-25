/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "interfaces/plugininterface.h"

#include <QObject>

class SCsPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID "com.OSTIS.kbe.PluginInterface" FILE "scsplugin.json")

public:
    explicit SCsPlugin(QObject *parent = 0);
    virtual ~SCsPlugin();

protected:
    //! @copydoc PluginInterface::name
    const QString& name() const;
    //! @copydoc PluginInterface::version
    const QString& version() const;
    //! @copydoc PluginInterface::interfaces
    const QList<QObject*>& interfaces() const;
    //! @copydoc PluginInterface::initialize
    void initialize();
    //! @copydoc PluginInterface::shutdown
    void shutdown();

    //! @copydoc PluginInterface::settingsWidget
    QWidget * settingsWidget() const;

private:
    //! List of interfaces
    QList<QObject*> mInterfaces;

signals:

public slots:

};


