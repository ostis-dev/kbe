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

#ifndef SCSWINDOW_H
#define SCSWINDOW_H

#include "interfaces/editorinterface.h"
#include "scscodeeditor.h"
#include "scssyntaxhighlighter.h"
#include <QtWidgets/QWidget>

class SCsFindWidget;
class SCsErrorTableWidget;

class EditorInterface;

class SCsWindow : public QWidget,
        public EditorInterface

{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)

public:
    explicit SCsWindow(const QString& _windowTitle, QWidget *parent = 0);
    ~SCsWindow();

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

private:
    SCsCodeEditor *mEditor;
    SCsSyntaxHighlighter *mHighlighter;
    SCsFindWidget *mFindWidget;
    SCsErrorTableWidget *mErrorTable;
    bool mIsSaved;

private slots:
    //! Content text changed slot
    void textChanged();
    void findNext();

    //! Handle find previous button pressed event
    void findPrevious();

    //! Text in find edit line changed.
    void findTextChanged(const QString &ttf);

    void showTextSearch();
    void onEscapePressed();
};

class SCsWindowFactory : public QObject,
        public EditorFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorFactoryInterface)

public:
    explicit SCsWindowFactory(QObject *parent = 0);
    virtual ~SCsWindowFactory();

    //! @copydoc EditorFactoryInterface::name
    const QString& name() const;
    //! @copydoc EditorFactoryInterface::createInstance
    EditorInterface* createInstance();
    //! @copydoc EditorFactoryInterface::supportedFormatsExt
    QStringList supportedFormatsExt();
    //! @copydoc EditorFactoryInterface::icon
    QIcon icon() const;

    QWidget* createNewParametersTab();

    QString getDescription() const;

};
#endif // SCSWINDOW_H
