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

#include "scgplugin.h"
#include "scgwindow.h"

#include "scgcontentfactory.h"
#include "scgcontentimage.h"
#include "scgcontentnumeric.h"
#include "scgcontentstring.h"

#include "scglayoutmanager.h"
#include "arrangers/scgarrangergrid.h"
#include "arrangers/scgarrangerhorizontal.h"
#include "arrangers/scgarrangertuple.h"
#include "arrangers/scgarrangervertical.h"
#include "arrangers/scgarrangerenergybased.h"

#include <QTranslator>
#include <QApplication>
#include <QLocale>

#include <unistd.h>

Q_EXPORT_PLUGIN2(scg, SCgPlugin)

SCgPlugin::SCgPlugin(QObject *parent) :
    QObject(parent),
    mTranslator(0)
{
    mTranslator = new QTranslator(this);
    bool res = mTranslator->load(":/scg/media/translations/scg_" + QLocale::system().name() + ".qm");
}

SCgPlugin::~SCgPlugin()
{
    delete mTranslator;
}

const QString& SCgPlugin::name() const
{
    static QString name = "scg";
    return name;
}

const QString& SCgPlugin::version() const
{
    static QString version = "0.2.0";
    return version;
}

const QList<QObject*>& SCgPlugin::interfaces() const
{
    return mInterfaces;
}

void SCgPlugin::initialize()
{
    Q_ASSERT_X(mEventListener != 0, "SCgPlugin::initialize", "mEventListener has null pointer");
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(0));
    mInterfaces.push_back(new SCgWindowFactory(this));

    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(10));
    SCgContentFactory::registerFactory("string", new SCgContentStringFactory);
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(20));
    SCgContentFactory::registerFactory("image", new SCgContentImageFactory);
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(30));
    SCgContentFactory::registerFactory("numeric", new SCgContentNumericFactory);
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(40));
    //SCgContentFactory::registerFactory("video", new SCgContentVideoFactory);

    SCgLayoutManager::instance().addArranger(new SCgGridArranger(this));
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(50));
    SCgLayoutManager::instance().addArranger(new SCgVerticalArranger(this));
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(60));
    SCgLayoutManager::instance().addArranger(new SCgHorizontalArranger(this));
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(70));
    SCgLayoutManager::instance().addArranger(new SCgTupleArranger(this));
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(80));
    SCgLayoutManager::instance().addArranger(new SCgEnergyBasedArranger(this));
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(90));

    qApp->installTranslator(mTranslator);
    mEventListener->processEvent(PluginEventListener::PluginLoadingProgress, QVariant(100));
}

void SCgPlugin::shutdown()
{
    QObject *interface = 0;
    foreach(interface, mInterfaces)
        delete interface;

    mInterfaces.clear();

    qApp->removeTranslator(mTranslator);
}
