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

#ifndef SCGPLUGIN_H
#define SCGPLUGIN_H

#include <QObject>
#include "interfaces/plugininterface.h"

class QTranslator;

class SCgPlugin : public QObject,
                  public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    explicit SCgPlugin(QObject *parent = 0);
    virtual ~SCgPlugin();

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

private:
    QList<QObject*> mInterfaces;

    //! Pointer to plugin translator
    QTranslator *mTranslator;

signals:

public slots:

};

#endif // SCGPLUGIN_H
