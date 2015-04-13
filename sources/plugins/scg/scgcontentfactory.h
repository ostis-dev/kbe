/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>

#include <QMap>
#include <QPair>
#include "scgcontent.h"

class SCgContentViewer;
class SCgContentDialog;
class SCgNode;

class SCgContentFactory : public QObject
{
Q_OBJECT
public:
    typedef QPair<QString, SCgContent::ContType> MimeAndSCgTypes;

    explicit SCgContentFactory(QObject *parent = 0);
    virtual ~SCgContentFactory(){}

    /*! Creates an instance of content viewer
      */
    virtual SCgContentViewer* createViewerInstance() = 0;

    /*! Creates an instance of content change dialog

        \param node sc.g-node we create dialog for.
      */
    virtual SCgContentDialog* createDialogInstance(SCgNode *node) = 0;

    /**
    * @brief Get map contained file's extentions mapped to MIME and SCg types
    */
    virtual QMap<QString, MimeAndSCgTypes> supportedExtentions()= 0;

    /* static functions for factory registration */
    /*! Registers factory for a specified content format
      */
    static void registerFactory(QString format, SCgContentFactory *factory);

    /*! Unregisters factory for a specified content format
      */
    static void unregisterFactory(QString format, SCgContentFactory *factory);

    /*! Get list of supported formats
      */
    static QList<QString> supportedFormats();

    /*! Get map of supported extensions with it's MIME and SCg types
    */
    static QMap<QString, MimeAndSCgTypes> registeredExtentions2MIME();

    /*! Create scg content viewer instance.
        \param  format  content format.

        \return SCg content viewer instance.
      */
    static SCgContentViewer* createViewer(QString format);

    /*! Create scg content dialog instance.
        \param format   content format.
        \param node sc.g-node we create dialog for.

        \return SCg content dialog instance.
      */
    static SCgContentDialog* createDialog(QString format, SCgNode *node);

private:
    //! Map of registered factories (format, factory)
    static QMap<QString, SCgContentFactory*> mFactories;

    //! Map contains MIME and SCg type for each supported extension
    static QMap<QString, MimeAndSCgTypes> ext2MIME;

signals:

public slots:

};
