/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QtPlugin>

class PluginInterface
{
public:
    virtual ~PluginInterface() {}

    //! Returns plugin name
    virtual const QString & name() const = 0;

    //! Returns plugin version
    virtual const QString & version() const = 0;

    /*! Return list of all interfaces that realized in that plugin
     * @attention All interfaces need to be a QObject, and created with plugin interface as a parent object
     */
    virtual const QList<QObject*> & interfaces() const = 0;

    //! Return settings widget for a plugin
    virtual QWidget * settingsWidget() const = 0;

    //! Initialize plugin
    virtual void initialize() = 0;

    //! Shutdown plugin
    virtual void shutdown() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.OSTIS.kbe.PluginInterface")

