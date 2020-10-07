/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "interfaces/editorinterface.h"
#include "scgscene.h"

#include <QToolBox>
#include <QMap>

class SCgMinimap;
class SCgView;
class SCgUndoView;

class QToolBar;
class QLineEdit;
class SCgFindWidget;

class SCgWindow : public QWidget,
                  public EditorInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)
public:
    //! Supported Mime-type for paste command.
    static const QString SupportedPasteMimeType;


    /*! Constructor
      */
    explicit SCgWindow(const QString& _windowTitle, QWidget *parent = 0);

    /*! Destructor
      */
    virtual ~SCgWindow();

    //! @copydoc EditorInterface::loadFromFile
    bool loadFromFile(const QString &fileName);

    //! @copydoc EditorInterface::saveToFile
    bool saveToFile(const QString &fileName);

    /*! Update window immediately
      */
    void _update();

    /*! Returns specified icon  by name for a SCg toolbar.
      @param iconName   Icon file name.
      */
    static QIcon findIcon(const QString &iconName);

    //! @return Undo stack for this window
    QUndoStack* undoStack() const;

protected:

    //! @copydoc EditorInterface::icon()
    QIcon icon() const;

    //! @copydoc EditorInterface::activate
    void activate(QMainWindow *window);
    //! @copydoc EditorInterface::deactivate
    void deactivate(QMainWindow *window);
    //! @copydoc EditorInterface::widget
    QWidget* widget();

    //! @copydoc EditorInterface::toolBar
    QToolBar* toolBar();
    //! @copydoc EditorInterface::widgetsForDocks
    QList<QWidget*> widgetsForDocks();
    //! @copydoc EditorInterface::isSaved
    bool isSaved() const;
    //! @copydoc EditorInterface::supportedFormatsExt
    QStringList supportedFormatsExt() const;

private:
    //! List of scales.
    static const QStringList mScales;
public:
    /*! @defgroup scaleConstraints Scale Constraints
     *  @{
     */
    static const qreal minScale;
    static const qreal maxScale;
    /*! @}*/
private:
    //! @see onZoomIn(), onZoomOut()
    static const int mScaleChangeStep;

    void createWidgetsForDocks();

    //! @see BaseWindow::createToolBar()
    void createToolBar();

    /*! Find object.
     *
     * @param ttf Text to find.
     * @param forward Find next or find previous
     */
    void find(const QString &ttf, bool forward, bool checkCurrent = false);

    //! Graphics view
    SCgView *mView;
    SCgScene *mScene;

    typedef QMap<int, QString> IntStringMap;
    IntStringMap mId2TypeAlias;

    typedef QMap<SCgScene::EditMode, QAction*> Mode2ActionMap;
    //! Map for storing mode-action relation
    Mode2ActionMap mMode2Action;

    //! Contents current zoom factor.
    QLineEdit* mZoomFactorLine;

    //! Pointer to minimap object
    SCgMinimap *mMinimap;

    //! Undo view widget
    SCgUndoView *mUndoView;

    //! Find widget
    SCgFindWidget *mFindWidget;

    //! Tool bar
    QToolBar *mToolBar;

    //! Undo stack
    QUndoStack *mUndoStack;

    //! Widgets, which will be placed into dock area of main window.
    QList<QWidget*> mWidgetsForDocks;

    /**
     * \defgroup menu Menu
     * @{
     */
    //!Edit menu
    QMenu* mEditMenu;
    //! undo action
    QAction* mActionUndo;
    //! Redo action
    QAction* mActionRedo;
    //! Find by identifier action;
    QAction* mActionFind;

    /*! Creates all actions, handled by this window.
     * @see createMenu() for adding actions in menu.
     */
    void createActions();

    //! creates specific menus for this window. Called after window activation.
    void createMenu();

    //! Destroys specific menus created by createMenu(). Called after window deactivation.
    void deleteMenu();
    /**@}*/

signals:

private slots:
    //! Slot to handle a selection action
    void onSelectMode();
    //! Slot to handle a pair creation action
    void onPairMode();
    //! Slot to handle a bus creation mode action
    void onBusMode();
    //! Slot to handle a contour creation mode action
    void onContourMode();
    //! Slot to handle a grid alignment action
    void onGridAlignment();
    //! Slot to handle a tuple alignment action
    void onTupleAlignment();
    //! Slot to handle a vertical alignment action
    void onVerticalAlignment();
    //! Slot to handle a horizontal alignment action
    void onHorizontalAlignment();
    //! Slot to handle select input/output action
    void onSelectInputOutput();
    //! Slot to handle select subgraph action
    void onSelectSubgraph();
    //! Slot to hanlde an export image action
    void onExportImage();
    //! Slot to handle a zoom in action
    void onZoomIn();
    //! Slot to handle a zoom out action
    void onZoomOut();
    //! Slot to set zoom factor value.
    void onViewScaleChanged(qreal newScaleValue);

    //! Handle find next button pressed event
    void findNext();

    //! Handle find previous button pressed event
    void findPrevious();

    //! Text in find edit line changed.
    void findTextChanged(const QString &ttf);

    //! Shows find widget
    void showTextSearch();

    /*!
     *Provides handling Cut menu event.
     */
    void cut() const;

     /*!
      *Provides handling Copy menu event.
      */
    void copy() const;

    /*!
     *Provides handling Paste menu event.
     */
    void paste() const;

    //! Delete action handler.
    void deleteSelected();

    void stackCleanStateChanged(bool value);
};

class SCgWindowFactory : public QObject,
                         public EditorFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorFactoryInterface)
public:
    explicit SCgWindowFactory(QObject *parent);
    virtual ~SCgWindowFactory();

    //! @copydoc EditorFactoryInterface::name
    const QString& name() const;
    //! @copydoc EditorFactoryInterface::createInstance
    EditorInterface* createInstance();
    //! @copydoc EditorFactoryInterface::supportedFormatsExt
    QStringList supportedFormatsExt();
    //! @copydoc EditorFactoryInterface::icon
    QIcon icon() const;

};


