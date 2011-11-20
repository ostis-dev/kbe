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

#include "scgcontentfactory.h"

QMap<QString, SCgContentFactory*> SCgContentFactory::mFactories = QMap<QString, SCgContentFactory*>();

SCgContentFactory::SCgContentFactory(QObject *parent) :
    QObject(parent)
{
}

void SCgContentFactory::registerFactory(QString format, SCgContentFactory *factory)
{
    Q_ASSERT(!mFactories.contains(format));
    mFactories[format] = factory;
}

void SCgContentFactory::unregisterFactory(QString format, SCgContentFactory *factory)
{
    Q_ASSERT(mFactories.contains(format));
    mFactories.remove(format);
}

QList<QString> SCgContentFactory::supportedFormats()
{
    return mFactories.keys();
}

SCgContentViewer* SCgContentFactory::createViewer(QString format)
{
    Q_ASSERT(mFactories.contains(format));
    return mFactories[format]->createViewerInstance();
}

SCgContentDialog* SCgContentFactory::createDialog(QString format, SCgNode *node)
{
    Q_ASSERT(mFactories.contains(format));
    return mFactories[format]->createDialogInstance(node);
}
