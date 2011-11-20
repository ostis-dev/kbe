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

#ifndef SCGWINDOW_H
#define SCGWINDOW_H

#include "basewindow.h"
#include "scgscene.h"

#include <QToolBox>
#include <QMap>

class SCgMinimap;
class SCgView;
class ExtendedUndoView;

class QToolBar;
class QLineEdit;
class FindWidget;

class SCgWindow : public BaseWindow
{
Q_OBJECT
public:
    //! Supported Mime-type for paste command.
    static const QString SupportedPasteMimeType;
    /*! @defgroup scaleConstraints Scale Constraints
     *  @{
     */
    static const qreal minScale = 0.20;
    static const qreal maxScale = 9.99;
    /*! @}*/

    /*! Constructor
      */
    explicit SCgWindow(const QString& _windowTitle, QWidget *parent = 0);

    /*! Destructor
      */
    virtual ~SCgWindow();

    /*! Load content from file.
      */
    bool loadFromFile(const QString &fileName, AbstractFileLoader *loader);

    /*! Save content to file.
      */
    bool saveToFile(const QString &fileName, AbstractFileWriter *writer);

    /*! Update window immediately
      */
    void _update();

    /*! Returns specified icon  by name for a SCg toolbar.
      @param iconName   Icon file name.
      */
    QIcon findIcon(const QString &iconName) const;

    //! @return Undo stack for this window
    QUndoStack* undoStack() const;

protected:

    //! @see BaseWindow::icon()
    QIcon icon() const;

    //! @see BaseWindow::activate
    void activate(QMainWindow *window);
    //! @see BaseWindow::deactivate
    void deactivate(QMainWindow *window);

private:
    //! List of scales.
    static const QStringList mScales;

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
    ExtendedUndoView *mUndoView;

    //! Find widget
    FindWidget *mFindWidget;

    /**
     * \defgroup menu Menu
     * @{
     */
//    //! View menu
//    QMenu* mViewMenu;
    //!Edit menu
    QMenu* mEditMenu;
    //! undo action
    QAction* mActionUndo;
    //! Redo action
    QAction* mActionRedo;
    //! Find by identifier action;
    QAction* mActionFind;

//    //! Show/hide minmap;
//    QAction* mActionMinMap;

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
    /*! Slot for a selection mode tool bar button clicked.
      */
    void onSelectMode();
    /*! Slot for a pair creation mode
      */
    void onPairMode();
    /*! Slot for a bus creation mode tool bar button clicked.
      */
    void onBusMode();
    /*! Slot for a contour creation mode tool bar button clicked.
      */
    void onContourMode();
    /*! Slot for the grid alignment tool bar button clicked.
      */
    void onGridAlignment();
    /*! Slot for the vertical alignment tool bar button clicked.
      */
    void onVerticalAlignment();
    /*! Slot for the horizontal alignment tool bar button clicked.
      */
    void onHorizontalAlignment();
    /*! Slot for handling ZoomIn event;
     */
    void onZoomIn();
    /*! Slot for handling ZoomOut event;
     */
    void onZoomOut();
    /*! Slot for setting zoom factor value.
     */
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
};

#endif // SCGWINDOW_H
