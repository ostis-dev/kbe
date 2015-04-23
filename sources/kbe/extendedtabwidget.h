/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QTabWidget>
class QMenu;

class QMdiSubWindow;
class EditorInterface;

class ExtendedTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ExtendedTabWidget(QWidget *parent = 0);
    virtual ~ExtendedTabWidget();

    /*! Closes given window.
     *
     * @param wnd Window that will be closed
     * @return True, if window successfully closed.
     */
    bool onCloseWindow(QWidget* wnd);

    //! @return list with tab widgets;
    QList<QWidget*> subWindowList() const;

    /*! Makes tab active by filename
     * @return If specified tab exists, then returns true; otherwise returns false
     */
    bool activateTab(QString const & fileName);

protected:
    //! Watches for all child widgets (windows).
    bool eventFilter (QObject* watched, QEvent* event);

signals:
    /*! This signal will send when any of tabs before closing(the tab will definitely closed).
     * @param w Widget in closed tab.
     * @return True, if tab will be closed.
     */
    bool tabBeforeClose(QWidget * w);

    /*! Tabs updated signal. Calls when new tab added, or any tab removed.
      */
    void tabsUpdate();

public slots:
    //! Closes all subwindows except active
    void onCloseOtherDocuments();
    //! Closes all subwindows
    void onCloseAllDocuments();
    /*!
     * Closes window at index @p index.
     * If @p index = -1 closes current window.
     * @return True, if tab is closed.
     */
    void onClose(int index = -1);

    /*! Adds new tab.
     * @param window Pointer to editor interface, that added
     * @return Tab index for added @p widget widget.
     */
    int addSubWindow(EditorInterface* window);

public:
/*    //! Adds additional options in default menu
    void addMenu(QMdiSubWindow* wnd);*/

    QString tabTextFor(QWidget* subWindow);
};

