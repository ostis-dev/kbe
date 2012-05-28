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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "extendedtabwidget.h"
#include "interfaces/editorinterface.h"

namespace Ui {
    class MainWindow;
}

class QSignalMapper;
class QUndoGroup;
class QGraphicsBlurEffect;
class QKeyEvent;
class EditorInterface;
class SCgWindow;

class MainWindow : public QMainWindow,
                   public EditorObserverInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorObserverInterface)

public:
    static MainWindow* getInstance();
    static void Destroy()
    {
        if(mInstance)
            delete mInstance;
        mInstance = 0;
    }

private:
    static MainWindow *mInstance;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    /*! Get active sub window
      @return Pointer to active sub window
      */
    EditorInterface *activeChild();

    /*! Load file with @p fileName
      */
    void load(const QString fileName);

    /*! Drag and drop events
     */
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

protected:
    void changeEvent(QEvent *event);
    void showEvent(QShowEvent *event);

    //! creates actions and configure them
    void createActions();

    /*! Creates tool bars. It creates file tool bar and edit toolbar.
      */
    void createToolBars();

    //! @copydoc EditorObserverInterface::updateEvent
    void updateEvent(EditorInterface *editor, EditEvents event);

private:
    /*! Gets icon by name
      */
    QIcon getIcon(const QString &name) const;

    /*! Saves window into specified file given by @p name with extension @p ext (without leading dot).
     * @return true if saved correctly
     */
    bool saveWindow(EditorInterface* window, QString& name, const QString& ext);
    /*! Check saved state of all subwindows
     * @return true if all subwinows are saved
     */
    bool checkSubWindowSavedState();

    /*!
     * Fabric method for creating subWindow.
     * @param ext File format extension
     * @return created window.
     */
    EditorInterface* createSubWindow(const QString& ext);

private:
    Ui::MainWindow *ui;

    ExtendedTabWidget *mTabWidget;
    int windowCounter;    // windows counter for untitled windows naming

    //! Active window
    EditorInterface* mLastActiveWindow;

    //! Tool bar for working with files
    QToolBar *mToolBarFile;
    //! Tool bar for edit functions
    QToolBar *mToolBarEdit;

    //! Blur effect
    QGraphicsBlurEffect *mBlurEffect;

    //! Maximum size of list with recently opened files.
    enum { MaxRecentFiles = 5 };
    //! Actions for opening recent files.
    QAction* recentFileActs[MaxRecentFiles];
    //! Separator in main menu for recently files.
    QAction *separatorAct;

    //! Contains all dockWidgets. Maps from objectName to DockWidget with this objectName. @see updateDockWidgets(bool).
    QMap<QString, QDockWidget*> mDockWidgets;

    /*! Holds window states for all types of BaseWindow.
     * Key - BaseWindow::objectName(). Value - window state returned by saveState() function.
     * @see QMainWindow::saveState(), @see QMainWindow::restoreState().
     */
    QMap<QString, QByteArray> mStates;


    typedef QMap<QWidget*, EditorInterface*> Widget2EditorInterfaceMap;
    /*! Map to convert widget to editor interface
      */
    Widget2EditorInterfaceMap mWidget2EditorInterface;

public slots:
    void updateMenu();
    void updateSpecificViewMenu();
    void updateRecentFileActions();
    void updateWindowTitle();

    void openRecentFile();
    void fileNew();
    void fileOpen();
    void fileSave(QWidget* window = 0);
    void fileSaveAs(QWidget* window = 0);
    void fileSaveAll();
    void fileExportToImage();
    void fileExit();

    void helpAbout();
    void helpAboutQt();
    void feedback();
    void guide();

    //! Current tab has changed
    void subWindowHasChanged(int index);
    //! tab will definitely be closed
    void windowWillBeClosed(QWidget* w);

    /*! Updates state of dockWidgets for current active window (@see mLastActiveWindow).
     * This slot keep in touch with all widgets, returned by mLastActiveWindow->widgetsForDocks() (@see BaseWindow::widgetsForDocks()).
     * If there is no corresponding dockWidget in the MainWindoW::mDockWidgets map for any widget from widgetsForDocks(), then the new dockWidget will be created.
     * objectName() will be set to objectName() of corresponding widget.
     * Newly created DockWidget wil be added into mDockWidgets map (key - objectName()).
     *
     * Slot also
     *
     * @param hide True, if all widgets should be hidden.
     */
    void updateDockWidgets(bool hide);

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
