/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QWidget>

class QToolBar;
class QUndoStack;
class AbstractFileLoader;
class AbstractFileWriter;
class QMimeData;
class QMainWindow;

class BaseWindow : public QWidget
{
Q_OBJECT
public:
    /*!
     *
     * @param objectName Global name for this editor used to save its configuration(e.g dock widgets positions)
     * @param _windowTitle window title for edited document.
     * @param parent @see QWidget::parent()
     */
    explicit BaseWindow(const QString& objectName, const QString& _windowTitle, QWidget *parent = 0);
    virtual ~BaseWindow();

    /*! Get toolbar.
        @return Returns pointer to specialized toolbar
      */
    QToolBar* toolBar();

    /*! @return widgets, that should be docked into main window.
     * @attention All widgets must have unique objectName for proper work of saving mechanism.
     * @note Title for dockWidget will be set to window title of corresponding widget.
     * @return
     */
    QList<QWidget*> widgetsForDocks();

    /*! Get document save state.
      @return if document haven't any changes after last save, then return true, else - false.
      */
    virtual bool isSaved() const;


    /*! Create tool bar
      */
    virtual void createToolBar() = 0;

    /*! Load content from file.
      @param fileName   Name of file.
      @param loader     Loader to load file.

      @note File loader will be removed automaticaly. You doesn't need to do that.

      @return If file loaded, then return true, else - false.
      */
    virtual bool loadFromFile(const QString &fileName, AbstractFileLoader *loader) = 0;

    /*! Save content to file.
      @param fileName   Name of file.
      @param writer     Writer to save file.

      @note File writer will be removed automaticaly. You doesn't need to do that.

      @return If file saved, then return true, else - false.
      */
    virtual bool saveToFile(const QString &fileName, AbstractFileWriter *writer) = 0;

    /*! Update window imideately
      */
    virtual void _update() = 0;

    /*! Get icon specified for window type
      */
    virtual QIcon icon() const = 0;

    /*! @return file name linked with this window.
     */
    const QString& currentFileName() const;

    /*! Window activation.
      @brief    Calls when window made active (selected in main window tab).
      @param    window  Pointer to main window
      */
    virtual void activate(QMainWindow *window);

    /*! Window deactivation.
      @brief    Calls whne window made inactive (selected other window in main window tab)
      @param    window  Pointer to main window
      */
    virtual void deactivate(QMainWindow *window);

    /*! Check if window is activated
      */
    bool isActivated() const;


protected:
    /*! Add widget @p w to list of widgets, which will be added into mainwindow's dock area.
     * @attention For proper work, widget @p w must has unique objectName and windowTitle.
     * @note BaseWindow doesn't take ownership of this widget.
     */
    void addWidgetForDock(QWidget* w);

    //! Tool bar
    QToolBar *mToolBar;

    //! Undo stack
    QUndoStack *mUndoStack;

    //! Holds file name for current document.
    QString mFileName;

    //! Activated flag
    bool mIsActivated;

signals:

private:
    //! Widgets, which will be placed into dock area of main window.
    QList<QWidget*> mWidgetsForDocks;


protected slots:

    /*! Slot for changing saved state after any modification
      */
    void stackCleanStateChanged(bool value);

    /*! Slot handled close event
      */
    void closeEvent(QCloseEvent *event);

};

#endif // BASEVIEW_H
