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

#ifndef M4SCPWINDOW_H
#define M4SCPWINDOW_H

#include "interfaces/editorinterface.h"

#include <QWidget>

class M4SCpCodeEditor;
class M4SCpSyntaxHighlighter;
class QIcon;

class M4SCpWindow : public QWidget,
                    public EditorInterface

{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)
public:
    explicit M4SCpWindow(const QString& _windowTitle, QWidget *parent = 0);
    ~M4SCpWindow();

    //! @copydoc EditorInterface::widget
    QWidget* widget();
    //! @copydoc EditorInterface::toolBar
    QToolBar* toolBar();
    //! @copydoc EditorInterface::widgetsForDocks
    QList<QWidget*> widgetsForDocks();
    //! @copydoc EditorInterface::supportedFormatsExt
    QStringList supportedFormatsExt() const;
    //! @copydoc EditorInterface::isSaved
    bool isSaved() const;

    /*! Load content from file.
      @param fileName   Name of file.

      @return If file loaded, then return true, else - false.
      */
    bool loadFromFile(const QString &fileName);

    /*! Save content to file.
      @param fileName   Name of file.

      @return If file saved, then return true, else - false.
      */

    bool saveToFile(const QString &fileName);

    /*! Update window imideately
      */
    void _update();

    /*! Get icon specified for window type
      */
    QIcon icon() const;

    static QIcon findIcon(const QString &iconName);

    /*!
      */
    void printFile();
    /*!
      */
    void printPreviewFile();
    /*!
      */
    void exportFileToPDF(const QString &fileName);

private:

    M4SCpCodeEditor *mEditor;
    M4SCpSyntaxHighlighter *mHighlighter;
    bool mIsSaved;

private slots:
    //! Slot that recieve content changing
    void textChanged();
    void printPreview(QPrinter *printer);
};

class M4SCpWindowFactory : public QObject,
                           public EditorFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorFactoryInterface)

public:
    explicit M4SCpWindowFactory(QObject *parent = 0);
    virtual ~M4SCpWindowFactory();

    //! @copydoc EditorFactoryInterface::name
    const QString& name() const;
    //! @copydoc EditorFactoryInterface::createInstance
    EditorInterface* createInstance();
    //! @copydoc EditorFactoryInterface::supportedFormatsExt
    QStringList supportedFormatsExt();
};

#endif // M4SCPWINDOW_H
