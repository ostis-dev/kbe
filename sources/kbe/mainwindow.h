/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QMainWindow>
#include <QMap>
#include <QDir>
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
class SettingsDialog;

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
     * Create window by specified type
     * @param type String that represents window type
     * @return If window created, then return pointer to it. Otherwise it returns null.
     */
    EditorInterface* createSubWindowByType(const QString& type);

    /*!
     * Create window for specified fiel extension support
     * @param ext File extension
     * @return If window created, then return pointer to it. Otherwise it returns null.
     */
    EditorInterface* createSubWindowByExt(const QString& ext);

    /*!
     * Generates a key for QSettings.setValue() using given editor type @p editorType
     * @param editorType Type of editor, key value should be generated for.
     * @return A value that should be used as a key for QSettings.setValue() to save editor layout.
     */
    QString getSettingKeyValueForWindow(const QString& editorType) const;

    /*!
     * Saves main window layout including dock widgets and geometry.
     */
    void saveLayout() const;


private:
    Ui::MainWindow *ui;

    ExtendedTabWidget *mTabWidget;
    int mWindowCounter;    // windows counter for untitled windows naming

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
    //! Maps from widget to editor interface
    Widget2EditorInterfaceMap mWidget2EditorInterface;

    //! Last used directory
    QDir mLastDir;

    SettingsDialog * mSettingsDialog;

public slots:
    void onUpdateMenu();
    void updateRecentFileActions();
    void updateWindowTitle();

    void onOpenRecentFile();
    void onFileNew();
    void onFileOpen(QString fileName=QString());
    void onFileSave(QWidget* window = 0);
    void onFileSaveAs(QWidget* window = 0);
    void onFileSaveAll();
    void onFileExportToImage();
    void onFileExit();

    void onViewSettings();

    void onHelpAbout();
    void onHelpAboutQt();
    void onFeedback();
    void onGuide();

    //! Current tab has changed
    void subWindowHasChanged(int index);
    //! tab will definitely be closed
    bool windowWillBeClosed(QWidget* w);

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

