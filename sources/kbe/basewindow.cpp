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

#include "basewindow.h"
#include "mainwindow.h"
#include "config.h"

#include <QSettings>
#include <QUndoStack>
#include <QMessageBox>
#include <QCloseEvent>
#include <QToolBar>
#include <QApplication>

BaseWindow::BaseWindow(const QString& objectName, const QString& _windowTitle, QWidget *parent) :
    QWidget(parent),
    mToolBar(0),
    mFileName(_windowTitle),
    mIsActivated(false)
{
    setObjectName(objectName);
    setWindowTitle(_windowTitle + "[*]");
    setAttribute(Qt::WA_DeleteOnClose);
    mUndoStack = new QUndoStack(this);
    connect(mUndoStack, SIGNAL(cleanChanged(bool)), this, SLOT(stackCleanStateChanged(bool)));
    connect(mUndoStack, SIGNAL(cleanChanged(bool)), MainWindow::getInstance(), SLOT(updateMenu()));
}

BaseWindow::~BaseWindow()
{
    delete mUndoStack;
    if(mToolBar)
        delete mToolBar;
}

QToolBar* BaseWindow::toolBar()
{
    if(!mToolBar)
        createToolBar();
    return mToolBar;
}

void BaseWindow::addWidgetForDock(QWidget* w)
{
    mWidgetsForDocks.push_back(w);
}

QList<QWidget*> BaseWindow::widgetsForDocks()
{
    return mWidgetsForDocks;
}

void BaseWindow::closeEvent(QCloseEvent *event)
{
    if (!isSaved()) {
        QString name = windowTitle();
        name.remove(name.size() - 3, 3);

        int variant = QMessageBox::information(MainWindow::getInstance(),
                                               qAppName(),
                                               tr("Do you want to save the ") + name,
                                               QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (variant == QMessageBox::Yes)
            MainWindow::getInstance()->fileSave(this);
        else
            if (variant == QMessageBox::Cancel)
                event->ignore();
    }

}


const QString& BaseWindow::currentFileName() const
{
    return mFileName;
}


void BaseWindow::stackCleanStateChanged(bool value)
{
    setWindowModified(!value);
}

bool BaseWindow::isSaved() const
{
    return mUndoStack->isClean();
}

void BaseWindow::activate(QMainWindow *window)
{
    Q_ASSERT_X(!mIsActivated,
               "void BaseWindow::activate(QMainWindow *window)",
               "Window is activated");

//    window->menuBar()

    QToolBar *tool_bar = toolBar();
    if (tool_bar != 0)
    {
        window->addToolBar(Qt::LeftToolBarArea, tool_bar);
        tool_bar->show();
    }
    mUndoStack->setActive(true);

    mIsActivated = true;
}

void BaseWindow::deactivate(QMainWindow *window)
{
    Q_ASSERT_X(mIsActivated,
               "void BaseWindow::activate(QMainWindow *window)",
               "Window isn't activated");

    window->removeToolBar(toolBar());
    mUndoStack->setActive(false);

    mIsActivated = false;
}

bool BaseWindow::isActivated() const
{
    return mIsActivated;
}
