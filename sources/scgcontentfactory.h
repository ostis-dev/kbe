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

#ifndef SCGCONTENTFACTORY_H
#define SCGCONTENTFACTORY_H

#include <QObject>

#include <QMap>

class SCgContentViewer;
class SCgContentDialog;
class SCgNode;

class SCgContentFactory : public QObject
{
Q_OBJECT
public:
    explicit SCgContentFactory(QObject *parent = 0);
    virtual ~SCgContentFactory(){}

    /*! Creates an instance of content viewer
      */
    virtual SCgContentViewer* createViewerInstance() = 0;

    /*! Creates an instance of content change dialog

        \param node SCg-node we create dialog for.
      */
    virtual SCgContentDialog* createDialogInstance(SCgNode *node) = 0;


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

    /*! Create scg content viewer instance.
        \param  format  content format.

        \return SCg content viewer instance.
      */
    static SCgContentViewer* createViewer(QString format);

    /*! Create scg content dialog instance.
        \param format   content format.
        \param node SCg-node we create dialog for.

        \return SCg content dialog instance.
      */
    static SCgContentDialog* createDialog(QString format, SCgNode *node);

private:
    //! Map of registered factories (format, factory)
    static QMap<QString, SCgContentFactory*> mFactories;

signals:

public slots:

};

#endif // SCGCONTENTFACTORY_H
