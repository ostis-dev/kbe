/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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

SCgPlugin::SCgPlugin(QObject *parent)
    : QObject(parent)
    , mTranslator(0)
{
    mTranslator = new QTranslator(this);
    mTranslator->load(":/scg/media/translations/scg_" + QLocale::system().name() + ".qm");
}

SCgPlugin::~SCgPlugin()
{
    delete mTranslator;
}

QString const & SCgPlugin::name() const
{
    static QString name = "scg";
    return name;
}

QString const & SCgPlugin::version() const
{
    static QString version = "0.2.0";
    return version;
}

QList<QObject*> const & SCgPlugin::interfaces() const
{
    return mInterfaces;
}

void SCgPlugin::initialize()
{
    mInterfaces.push_back(new SCgWindowFactory(this));

    SCgContentFactory::registerFactory("string", new SCgContentStringFactory);
    SCgContentFactory::registerFactory("image", new SCgContentImageFactory);
    SCgContentFactory::registerFactory("numeric", new SCgContentNumericFactory);

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

QWidget * SCgPlugin::settingsWidget() const
{
    return 0;
}
