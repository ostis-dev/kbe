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

#ifndef SCGVIEW_H
#define SCGVIEW_H

#include <QGraphicsView>

class SCgWindow;
class SCgObject;
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
    void setScale(int sc);

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

    /*! Change type of context element.
      * @param action Pointer to action that assigned to specified sc.g-element type
      */
    void changeType(QAction *action);

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

#endif // SCGVIEW_H
