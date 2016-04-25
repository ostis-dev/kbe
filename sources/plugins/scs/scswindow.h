/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "interfaces/editorinterface.h"
#include "scscodeeditor.h"
#include "scssyntaxhighlighter.h"
#include <QWidget>

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

    void activate(QMainWindow *window);

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

};

