/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgobject.h"

#include <QGraphicsView>

class SCgWindow;
class SCgScene;
class QContextMenuEvent;
class QMenu;
class QKeyEvent;
class QAction;

class SCgView : public QGraphicsView
{
Q_OBJECT
public:

    explicit SCgView(QWidget *parent, SCgWindow *window);
    virtual ~SCgView();

    //! Pointer to SCgScene, that is being visualized by this SCgView
    SCgScene* getSCgScene() const;

    //! Actions, provided by this view.
    QList<QAction*> actions() const;

protected:
    void contextMenuEvent(QContextMenuEvent *event);

    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    /*! Drag and drop events
      */
    void dragEnterEvent(QDragEnterEvent *evt);
    void dragLeaveEvent(QDragLeaveEvent *evt);
    void dragMoveEvent(QDragMoveEvent *evt);
    void dropEvent(QDropEvent *event);

    void wheelEvent(QWheelEvent *event);

private:
    /**
     * \defgroup menu Actions
     * @{
     */
    QAction* mActionChangeType;
    QAction* mActionChangeContent;
    QAction* mActionShowContent;
    QAction* mActionShowAllContent;
    QAction* mActionHideAllContent;
    QAction* mActionDeleteContent;
    QAction* mActionChangeIdtf;
    QAction* mActionDelete;
    QAction* mActionContourDelete;
    QAction* mActionSwapPairOrient;
    //! Copy action
    QAction* mActionCopy;
    //! Cut action
    QAction* mActionCut;
    //! Paste action
    QAction* mActionPaste;
    //! Select All action
    QAction* mActionSelectAll;

    QList<QAction*> mActionsList;
    void createActions();

private slots:
    //! Update state of actions created by createActions() command.
    void updateActionsState(int idx = 0);

    /*! Provides handling SelectAll menu event.
     *
     */
    void selectAllCommand() const;
    /**@}*/

private:
    //! Check if all requirements for changing type of passed objects are fulfilled
    //! Should be checked out before calling SCgView::changeType()
    bool canChangeTypesOfObjects(const SCgObject::SCgObjectList& objectList) const;

    //! Previous mouse position for scrolling by mid mouse button click.
    QPoint mPrevMousePos;
    //! Pointer to context menu
    QMenu *mContextMenu;
    //! Pointer to object for witch one context menu created
    SCgObject *mContextObject;
    SCgWindow *mWindow;

    bool isSceneRectControlled;

signals:
    //! Emitted, when scale factor is changed.
    void scaleChanged(qreal newScaleFactor);
    //! Emitted, when sceneRect, visualized by this view, was changed.
    void sceneRectChanged(const QRectF& newRect);

public slots:

    //! Slot for scale changing. (The string must be smth like this: "123%")
    void setScale(const QString& sc);

    //! Overloaded function. @p scaleFactor must be in range of 0.1 ... 9.99 .
    void setScale(qreal scaleFactor);

    //! Overrides QGraphicsView::setScene().
    void setScene(SCgScene* scene);

private slots:
    //! Delete selected sc.g-elements
    void deleteSelected();

    //! Delete selected contour without child objects
    void deleteJustContour();

    //! Swap sc.g-pair orientation
    void swapPairOrient();

    //! Start dialog for sc.g-element identifier changing
    void changeIdentifier();

    //! Show dialog with available types for currently selected objects
    //! and initiate type changing
    void chooseTypeForSelectedObjects();

    //! Change type of passed objects to newType.
    void changeType(const SCgObject::SCgObjectList& objectList, const QString& newType);

    //! Starts content change dialog
    void changeContent();

    //! Show/hide content of selected element
    void setContentVisible(bool visibility);

    //! Delete content of selected element
    void deleteContent();

    void updateSceneRect(const QRectF& rect);

    //! Edit mode changed slot @see SCgScene::editModeChanged
    void editModeChanged(int mode);
};


