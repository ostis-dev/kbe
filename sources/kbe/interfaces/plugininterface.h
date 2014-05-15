/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.OSTIS.kbe.PluginInterface/1.0")

#endif // PLUGIN_H
