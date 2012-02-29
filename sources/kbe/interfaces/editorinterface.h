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

#ifndef WINDOWINTERFACE_H
#define WINDOWINTERFACE_H

#include <QtPlugin>
#include <QIcon>

class FileLoaderInterface;
class FileWriterInterface;

class QToolBar;
class QMainWindow;

class EditorInterface
{
public:
    explicit EditorInterface() {}
    virtual ~EditorInterface() {}

    //! Return pointer to widget, that represent window
    virtual QWidget* widget() = 0;

    /*! Get toolbar.
       @return Returns pointer to specialized toolbar
     */
    virtual QToolBar* toolBar() = 0;

    /*! @return widgets, that should be docked into main window.
    * @attention All widgets must have unique objectName for proper work of saving mechanism.
    * @note Title for dockWidget will be set to window title of corresponding widget.
    * @return
    */
    virtual QList<QWidget*> widgetsForDocks() = 0;

    /*! Get document save state.
     @return if document haven't any changes after last save, then return true, else - false.
     */
    virtual bool isSaved() const = 0;

    /*! Load content from file.
     @param fileName   Name of file.

     @return If file loaded, then return true, else - false.
     */
    virtual bool loadFromFile(const QString &fileName) { mFileName = fileName; return false; }

    /*! Save content to file.
     @param fileName   Name of file.

     @return If file saved, then return true, else - false.
     */
    virtual bool saveToFile(const QString &fileName) { mFileName = fileName; return false; }

    /*! Update window imideately
     */
    virtual void _update() = 0;

    /*! Get icon specified for window type
     */
    virtual QIcon icon() const = 0;

    /*! @return file name linked with this window.
    */
    virtual const QString& currentFileName() const { return mFileName; }

    /*! Window activation.
     @brief    Calls when window made active (selected in main window tab).
     @param    window  Pointer to main window
     */
    virtual void activate(QMainWindow *window) { mIsActivated = true; }

    /*! Window deactivation.
     @brief    Calls whne window made inactive (selected other window in main window tab)
     @param    window  Pointer to main window
     */
    virtual void deactivate(QMainWindow *window) { mIsActivated = false; }

    /*! Check if window is activated
     */
    virtual bool isActivated() const { return mIsActivated; }

    //! Return list of supported for save format extensions
    virtual QStringList supportedFormatsExt() const = 0;

protected:
    //! Holds file name for current document.
    QString mFileName;

    //! Activated flag
    bool mIsActivated;

};

class EditorFactoryInterface
{
public:
    explicit EditorFactoryInterface() {}
    virtual ~EditorFactoryInterface() {}

    //! Return name of window factory
    virtual const QString& name() const = 0;

    //! Create new window instance
    virtual EditorInterface* createInstance()  = 0;

    //! Return file extensions supported by that type of window
    virtual QStringList supportedFormatsExt() = 0;
};

Q_DECLARE_INTERFACE(EditorInterface,
                    "com.OSTIS.kbe.EditorInterface/1.0")
Q_DECLARE_INTERFACE(EditorFactoryInterface,
                    "com.OSTIS.kbe.EditorFactoryInterface/1.0")

#endif // WINDOWINTERFACE_H
