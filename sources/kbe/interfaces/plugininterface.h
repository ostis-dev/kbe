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

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#include <QVariant>

class PluginEventListener
{
public:
    enum PluginEvents
    {
        PluginLoadingStarted,
        PluginLoadingProgress,
        PluginLoadingFinished
    };

    /*! Process specific event
    * @param event Event type
    * @param userData Data which received with event
    */
    virtual void processEvent(PluginEvents event, const QVariant userData = QVariant()) = 0;
};

class PluginInterface
{
public:
    virtual ~PluginInterface() {}

    //! Returns plugin name
    virtual const QString& name() const = 0;

    //! Returns plugin version
    virtual const QString& version() const = 0;

    /*! Return list of all interfaces that realized in that plugin
      * @attention All interfaces need to be a QObject, and created with plugin interface as a parent object
      */
    virtual const QList<QObject*>& interfaces() const = 0;

    /*! Initialize plugin
      */
    virtual void initialize() = 0;

    //! Shutdown plugin
    virtual void shutdown() = 0;

    //! Set event listener to @p listener
    void setListener(PluginEventListener *listener) { mEventListener = listener; }

    //! Get pointer to event listener
    PluginEventListener* listener() const { return mEventListener; }
protected:
    PluginEventListener *mEventListener;
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.OSTIS.kbe.PluginInterface/1.0")

#endif // PLUGIN_H
