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


#ifndef EXTENDEDMDIAREA_H_
#define EXTENDEDMDIAREA_H_

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
    bool closeWindow(QWidget* wnd);

    //!@return list with tab widgets;
    QList<QWidget*> subWindowList() const;

protected:
    //! Watches for all child widgets (windows).
    bool eventFilter (QObject* watched, QEvent* event);

signals:
    /*! This signal will send when any of tabs before closing(the tab will definitely closed).
     * @param w Widget in closed tab.
     */
    void tabBeforeClose(QWidget* w);

    /*! Tabs updated signal. Calls when new tab added, or any tab removed.
      */
    void tabsUpdate();

public slots:
    //! Closes all subwindows except active
    void closeOtherDocuments();
    //! Closes all subwindows
    void closeAllDocuments();
    /*!
     * Closes window at index @p index.
     * If @p index = -1 closes current window.
     * @return True, if tab is closed.
     */
    void close(int index = -1);

    /*! Adds new tab.
     * @param window Pointer to editor interface, that added
     * @return Tab index for added @p widget widget.
     */
    int addSubWindow(EditorInterface* window);

public:
/*    //! Adds additional options in default menu
    void addMenu(QMdiSubWindow* wnd);*/

    inline QString tabTextFor(QWidget* subWindow);
};

#endif /* EXTENDEDMDIAREA_H_ */
