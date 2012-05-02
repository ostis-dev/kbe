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

#include <QTranslator>
#include <QApplication>
#include <QLocale>

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
    mInterfaces.push_back(new SCgWindowFactory(this));

    SCgContentFactory::registerFactory("string", new SCgContentStringFactory);
    SCgContentFactory::registerFactory("image", new SCgContentImageFactory);
    SCgContentFactory::registerFactory("numeric", new SCgContentNumericFactory);
    //SCgContentFactory::registerFactory("video", new SCgContentVideoFactory);

    SCgLayoutManager::instance().addArranger(new SCgGridArranger(this));
    SCgLayoutManager::instance().addArranger(new SCgVerticalArranger(this));
    SCgLayoutManager::instance().addArranger(new SCgHorizontalArranger(this));
    SCgLayoutManager::instance().addArranger(new SCgTupleArranger(this));

    qApp->installTranslator(mTranslator);
}

void SCgPlugin::shutdown()
{
    QObject *interface = 0;
    foreach(interface, mInterfaces)
        delete interface;

    mInterfaces.clear();

    qApp->removeTranslator(mTranslator);
}
