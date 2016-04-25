/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontentfactory.h"

QMap<QString, SCgContentFactory*> SCgContentFactory::mFactories = QMap<QString, SCgContentFactory*>();

QMap<QString, SCgContentFactory::MimeAndSCgTypes> SCgContentFactory::ext2MIME = QMap<QString, SCgContentFactory::MimeAndSCgTypes>();

SCgContentFactory::SCgContentFactory(QObject *parent) :
    QObject(parent)
{    
}

void SCgContentFactory::registerFactory(QString format, SCgContentFactory *factory)
{
    Q_ASSERT(!mFactories.contains(format));
    QMap<QString, MimeAndSCgTypes> tmpMap = factory->supportedExtentions();
    QMap<QString, MimeAndSCgTypes>::const_iterator it = tmpMap.begin();
    for (; it != tmpMap.end(); ++it)
        ext2MIME[it.key()] = it.value();
    mFactories[format] = factory;
}

void SCgContentFactory::unregisterFactory(QString format, SCgContentFactory *factory)
{
    Q_ASSERT(mFactories.contains(format));
    QMap<QString, MimeAndSCgTypes> tmpMap = factory->supportedExtentions();
    QMap<QString, MimeAndSCgTypes>::const_iterator it = tmpMap.begin();
    for (; it != tmpMap.end(); ++it)
        ext2MIME.remove(it.key());
    mFactories.remove(format);
}

QList<QString> SCgContentFactory::supportedFormats()
{
    return mFactories.keys();
}

QMap<QString, SCgContentFactory::MimeAndSCgTypes> SCgContentFactory::registeredExtentions2MIME() {
    return ext2MIME;
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
