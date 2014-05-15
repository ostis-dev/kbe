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

#ifndef SCNWINDOW_H
#define SCNWINDOW_H

#include <QWidget>
#include "interfaces/editorinterface.h"

class SCnEditorScene;
class QGraphicsView;

class SCnWindow : public QWidget,
                  public EditorInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)

public:
    explicit SCnWindow(QWidget *parent = 0);
    virtual ~SCnWindow();

    //! @copydoc EditorInterface::widget
    QWidget* widget();
    //! @copydoc EditorInterface::toolBar
    QToolBar* toolBar();
    //! @copydoc EditorInterface::widgetsForDocks
    QList<QWidget*> widgetsForDocks();
    //! @copydoc EditorInterface::isSaved
    bool isSaved() const;
    //! @copydoc EditorInterface::_update
    void _update();
    //! @copydoc EditorInterface::icon
    QIcon icon() const;
    //! @copydoc EditorInterface::supportedFormatsExt
    QStringList supportedFormatsExt() const;

    //! @copydoc EditorInterface::loadFromFile
    bool loadFromFile(const QString &fileName);
    //! @copydoc EditorInterface::saveToFile
    bool saveToFile(const QString &fileName);

    //! Return icon by name
    static QIcon findIcon(const QString &iconName);

protected:
    //! Saved flag
    bool mIsSaved;
    //! Pointer to editor scene
    SCnEditorScene *mEditorScene;
    //! Pointer to editor view
    QGraphicsView *mEditorView;

signals:

public slots:

};


/*! Factory for scn-windows
  */
class SCnWindowFactory : public QObject,
                         public EditorFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorFactoryInterface)

public:
    explicit SCnWindowFactory(QObject *parent = 0);
    virtual ~SCnWindowFactory();

    //! @copydoc SCnWindowFactory::name
    const QString& name() const;
    //! @copydoc SCnWindowFactory::createInstance
    EditorInterface* createInstance();
    //! @copydoc SCnWindowFactory::supportedFormatsExt
    QStringList supportedFormatsExt();
};

#endif // SCNWINDOW_H
