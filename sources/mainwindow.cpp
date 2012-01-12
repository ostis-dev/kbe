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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scgwindow.h"
#include "basewindow.h"
#include "config.h"


#include "abstractfileloader.h"
#include "abstractfilewriter.h"
#include "readwritemanager.h"
#include "layoutmanager.h"

#include "version.h"

#include "scgcontentstring.h"
#include "scgcontentimage.h"
#include "scgcontentnumeric.h"
//#include "scgcontentvideo.h"

#include "scgfilewriterimage.h"
#include "scgfilewritergwf.h"
#include "scgfileloadergwf.h"

#include <QMdiSubWindow>
#include <QToolBar>
#include <QStyleFactory>
#include <QSignalMapper>
#include <QFileDialog>
#include <QUndoGroup>
#include <QMessageBox>
#include <QUrl>
#include <QGraphicsBlurEffect>
#include <QCloseEvent>
#include <QSettings>
#include <QDockWidget>


MainWindow* MainWindow::mInstance = 0;

MainWindow* MainWindow::getInstance()
{
    if(!mInstance)
        mInstance = new MainWindow();

    return mInstance;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        windowCounter(0),
        mLastActiveWindow(0),
        mToolBarFile(0),
        mToolBarEdit(0)
{
    ui->setupUi(this);

    /* creating tab widget */
    mTabWidget = new ExtendedTabWidget();
    connect(mTabWidget, SIGNAL(tabsUpdate()), this, SLOT(updateMenu()));

    setCentralWidget(mTabWidget);

    connect(mTabWidget, SIGNAL(currentChanged(int)),
            SLOT(subWindowHasChanged(int)), Qt::AutoConnection);

    // creating actions
    createActions();
    createToolBars();

    updateMenu();
    updateSpcificViewMenu();
    updateRecentFileActions();

    setWindowTitle(tr("Knowledge Base source Editor - version %1").arg(VERSION_STR));

    //QApplication::setStyle(QStyleFactory::create("Plastique"));
    //QApplication::setPalette(QApplication::style()->standardPalette());

    // temporary
    SCgContentFactory::registerFactory("string", new SCgContentStringFactory);
    SCgContentFactory::registerFactory("image", new SCgContentImageFactory);
    SCgContentFactory::registerFactory("numeric", new SCgContentNumericFactory);
    //SCgContentFactory::registerFactory("video", new SCgContentVideoFactory);

    ReadWriteManager::instance().registerFileLoaderFactory(new SCgFileLoaderGWFFactory());
    ReadWriteManager::instance().registerFileWriterFactory(new SCgFileWriterGWFFactory());
    ReadWriteManager::instance().registerFileWriterFactory(new SCgFileWriterImageFactory());

    LayoutManager::instance().addArranger(new SCgGridArranger(this));
    LayoutManager::instance().addArranger(new SCgVerticalArranger(this));
    LayoutManager::instance().addArranger(new SCgHorizontalArranger(this));

    // blur effect
    mBlurEffect = new QGraphicsBlurEffect(this);
    mBlurEffect->setEnabled(false);
    setGraphicsEffect(mBlurEffect);

    // restore geometry from settings
    QSettings settings;
    restoreGeometry(settings.value(Config::settingsMainWindowGeometry).toByteArray());

    setAcceptDrops(true);
}


MainWindow::~MainWindow()
{
    delete mBlurEffect;
    delete mToolBarFile;
    delete mToolBarEdit;
    delete ui;
    delete mTabWidget;

    ReadWriteManager::destroy();
    LayoutManager::destroy();
}

void MainWindow::createToolBars()
{
    mToolBarFile = new QToolBar;
    mToolBarFile->addAction(ui->actionNew);
    mToolBarFile->addAction(ui->actionOpen);
    mToolBarFile->addAction(ui->actionSave);
    mToolBarFile->addAction(ui->actionSave_as);
    //mToolBarFile->addAction(ui->actionSave_all);
    mToolBarFile->addSeparator();
    mToolBarFile->addAction(ui->actionClose);
    //mToolBarFile->addAction(ui->actionClose_All);
    //mToolBarFile->addAction(ui->actionClose_Others);
    mToolBarFile->setObjectName("Main Tools");
    mToolBarFile->setWindowTitle(tr("Main Tools"));
    addToolBar(mToolBarFile);
}

void MainWindow::createActions()
{
    ui->actionNew->setIcon(QIcon::fromTheme("document-new", getIcon("document-new.png")));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open", getIcon("document-open.png")));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save", getIcon("document-save.png")));
    ui->actionSave_as->setIcon(QIcon::fromTheme("document-save-as", getIcon("document-save-as.png")));

    ui->actionClose->setIcon(QIcon::fromTheme("window-close", getIcon("window-close.png")));
    ui->actionExit->setIcon(QIcon::fromTheme("application-exit", getIcon("application-exit.png")));

    ui->actionAbout->setIcon(QIcon::fromTheme("help-browser", getIcon("help-browser.png")));

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(fileSave()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    connect(ui->actionSave_all, SIGNAL(triggered()), this, SLOT(fileSaveAll()));
    connect(ui->actionTo_image, SIGNAL(triggered()), this, SLOT(fileExportToImage()));

    connect(ui->actionClose_All, SIGNAL(triggered()), mTabWidget, SLOT(closeAllDocuments()) );
    connect(ui->actionClose, SIGNAL(triggered()), mTabWidget, SLOT(close()));
    connect(ui->actionClose_Others, SIGNAL(triggered()), mTabWidget, SLOT(closeOtherDocuments()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(updateMenu()));
    connect(ui->actionClose_Others, SIGNAL(triggered()), this, SLOT(updateMenu()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(fileExit()));

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        ui->menuFile->insertAction(ui->actionExit, recentFileActs[i]);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
    separatorAct = ui->menuFile->insertSeparator(ui->actionExit);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(helpAboutQt()));
}

QIcon MainWindow::getIcon(const QString &name) const
{
    QFileInfo fi(Config::pathIcons, name);
    return QIcon(fi.absoluteFilePath());
}

bool MainWindow::checkSubWindowSavedState()
{
    QList<QWidget*> list = mTabWidget->subWindowList();
    QList<QWidget*>::iterator it = list.begin();
    for(; it != list.end(); it++)
        if (!qobject_cast<BaseWindow*>(*it)->isSaved())
            return false;
    return true;
}

BaseWindow *MainWindow::activeChild()
{
    if (QWidget *activeSubWindow = mTabWidget->currentWidget())
        return qobject_cast<BaseWindow *>(activeSubWindow);
    return 0;
}

void MainWindow::updateMenu()
{
    BaseWindow *subWindow = activeChild();

    ui->actionSave->setEnabled(subWindow && !subWindow->isSaved());
    ui->actionSave_as->setEnabled(subWindow != 0);
    ui->actionSave_all->setEnabled(subWindow != 0 && !checkSubWindowSavedState());
    ui->menuExport->setEnabled(subWindow !=0);

    ui->actionClose->setEnabled(subWindow != 0);
    ui->actionClose_All->setEnabled(subWindow != 0);
    ui->actionClose_Others->setEnabled(mTabWidget->subWindowList().size() > 1);
}

void MainWindow::updateSpcificViewMenu()
{
    ui->menuView->menuAction()->setVisible(false);//setDisabled(true);
    ui->menuView->clear();
    if(mLastActiveWindow)
    {
        QList<QWidget*> ws = mLastActiveWindow->widgetsForDocks();
        if(!ws.empty())
        {
            foreach(QWidget* w, ws)
                ui->menuView->addAction(mDockWidgets[w->objectName()]->toggleViewAction());
            ui->menuView->menuAction()->setVisible(true);
        }
    }
}
void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value(Config::settingsRecentFileList).toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i)
    {
        QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        QString fn = action->data().toString();
        if(QFile::exists(fn))
            load(fn);
        else
        {
            QSettings settings;

            QStringList files = settings.value(Config::settingsRecentFileList).toStringList();
            files.removeAll(fn);
            settings.setValue(Config::settingsRecentFileList, files);

            updateRecentFileActions();

            QMessageBox::warning(this, qAppName(), tr("Can't load file.\nFile \"%1\" not found. ").arg(fn));
        }
    }
}

BaseWindow* MainWindow::createSubWindow(const QString& fileName, int windowType)
{
    BaseWindow* childWindow = 0;

    switch(windowType)
    {
    default:
        childWindow = new SCgWindow(fileName);
    }

    Q_ASSERT_X( childWindow,
               "void MainWindow::createSubWindow(const QString& fileName, int viewType)",
               "Error while creating window with given type");

    mTabWidget->addSubWindow(childWindow);

    return childWindow;
}

void MainWindow::fileNew()
{
    createSubWindow(tr("Untitled") + "-" + QString::number(++windowCounter));
}

void MainWindow::fileOpen()
{
    QFileDialog::Options options;
    options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QFileDialog dlg;

    mBlurEffect->setEnabled(true);
    QString fileName = dlg.getOpenFileName(this,
                                           tr("Open file"),
                                           "",
                                           ReadWriteManager::instance().openFilters(),
                                           &selectedFilter,
                                           options);
    if (!fileName.isEmpty())
        load(fileName);
    mBlurEffect->setEnabled(false);
}

void MainWindow::load(QString fileName)
{
    QString ext = fileName.mid(fileName.lastIndexOf('.') + 1);
    if(ReadWriteManager::instance().registeredLoaderExtensions().contains(ext))
    {
        BaseWindow* childWindow = createSubWindow(fileName);

        AbstractFileLoader *loader = ReadWriteManager::instance().createLoader("gwf");

        if (childWindow->loadFromFile(fileName, loader))
        {
            QSettings settings;

            QStringList files = settings.value(Config::settingsRecentFileList).toStringList();
            files.removeAll(fileName);
            files.prepend(fileName);
            while (files.size() > MaxRecentFiles)
                files.removeLast();

            settings.setValue(Config::settingsRecentFileList, files);

            updateRecentFileActions();
        }

        delete loader;
    } else
        QMessageBox::warning(this, qAppName(), tr("Can't load file.\nUnsupported file format \"%1\"").arg(ext));
}

bool MainWindow::saveWindow(BaseWindow* window, QString& name, const QString& ext)
{
    if(!name.isEmpty() && window)
    {
        bool retVal = false;

        if(ReadWriteManager::instance().registeredWriterExtensions().contains(ext))
        {
            if (!name.endsWith("." + ext))
                name += "." + ext;

            AbstractFileWriter *writer = ReadWriteManager::instance().createWriter(ext);
            retVal = window->saveToFile(name, writer);
            delete writer;
        } else
            QMessageBox::warning(this, qAppName(), tr("Can't save file.\nUnsupported file format \"%1\"").arg(ext));

        return retVal;
    }

    return false;
}

void MainWindow::fileSave(BaseWindow* window)
{
    BaseWindow* childWindow = window;

    if(!childWindow)
        childWindow = activeChild();

    Q_ASSERT(childWindow);

    if (!childWindow->isSaved())
    {
        QString fileName = childWindow->currentFileName();
        if(QFile::exists(fileName))
        {
            int dPos = fileName.lastIndexOf(".") + 1;
            Q_ASSERT_X(dPos != 0, "MainWindow::fileSave()", "File with empty extension!");
            QString ext = fileName.mid(dPos);
            saveWindow(childWindow, fileName, ext);
        }else
            fileSaveAs(childWindow);
    }
}

void MainWindow::fileSaveAs(BaseWindow* window)
{
    BaseWindow* childWindow = window;

    if(!childWindow)
        childWindow = activeChild();

    Q_ASSERT(childWindow);

    QString formatsStr = ReadWriteManager::instance().saveFilters();
    QFileDialog::Options options;
    options |= QFileDialog::DontUseNativeDialog ;


    QString selectedFilter;
    QString fileName = QCoreApplication::applicationDirPath() + "/" + childWindow->currentFileName();
    mBlurEffect->setEnabled(true);
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save file to .."),
                                            fileName,
                                            formatsStr,
                                            &selectedFilter,
                                            options);
    if(!fileName.isEmpty())
        saveWindow(childWindow, fileName, ReadWriteManager::extFromFilter(selectedFilter));

    mBlurEffect->setEnabled(false);

}

void MainWindow::fileSaveAll()
{
    for(int i = 0; i < mTabWidget->subWindowList().size(); i++) {
        if (!qobject_cast<SCgWindow*>(activeChild())->isSaved())
            fileSave();
            mTabWidget->setCurrentIndex(mTabWidget->currentIndex()+1);
        }
}

void MainWindow::fileExportToImage()
{
    SCgWindow *childWindow = qobject_cast<SCgWindow*>(activeChild());

    if(childWindow){

        QString formatsStr = ReadWriteManager::instance().exportFilters();
        QFileDialog::Options options;
        options |= QFileDialog::DontUseNativeDialog;


        QString selectedFilter;
        QFileDialog dlg;

        mBlurEffect->setEnabled(true);
        QString fileName = QCoreApplication::applicationDirPath() + "/" + childWindow->currentFileName();
        fileName = dlg.getSaveFileName(this,
                                       tr("Export file to ..."),
                                       fileName,
                                       formatsStr,
                                       &selectedFilter,
                                       options);

        if (!fileName.isEmpty())
        {
            QString ext = ReadWriteManager::instance().extFromFilter(selectedFilter);
            if (!fileName.endsWith("." + ext))
                fileName += "." + ext;
            AbstractFileWriter *writer = ReadWriteManager::instance().createWriter(ext);
            childWindow->saveToFile(fileName, writer);
            delete writer;
        }
        mBlurEffect->setEnabled(false);
    }

}

void MainWindow::fileExit()
{
    close();
}

void MainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About KBE"),
                       QString("<table><tr valign=\"middle\"><td align=\"left\"><img src=\"%1\"></td>"
                               "<td>%2 %3: %4 <br> <br> Site: "
                               "<STYLE type=\"text/css\">"
                               "a:link {text-decoration: none}"
                               "</STYLE>"
                               "<a href=\"http://www.ostis.net\">http://www.ostis.net</a>"
                               "<br> <br>Copyright © OSTIS.net</td></tr><tr>"
                               "<td></td><td>%5:<ul>"
                               "<li>Denis Koronchik</li>"
                               "<li>Gumbar Ilya</li>"
                               "<li>Harkunov Evgeny</li>"
                               "</ul>"
                               "</td></tr></table>")
                       .arg(QFileInfo(Config::pathIcons, "help-about-logo.png").absoluteFilePath())
                       .arg(tr("Knowledge Base source Editor "))
                       .arg(tr("version"))
                       .arg(VERSION.toString())
                       .arg(tr("Authors")));
}

void MainWindow::helpAboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::updateDockWidgets(bool visible)
{
    Q_ASSERT_X(mLastActiveWindow,
               "void MainWindow::updateDockWidgets(bool hide)",
               "window must be activated first!");

    QString objName = mLastActiveWindow->objectName();

    if(!visible)
    {
        mStates[objName] = saveState();
        QMap<QString, QDockWidget*>::const_iterator it = mDockWidgets.begin();
        while(it != mDockWidgets.end())
        {
            it.value()->close();
            ++it;
        }
    }else
    {
        if(!mStates.contains(objName))
        {
            // Read window state from settings.
            QSettings settings;
            mStates[objName] = settings.value(Config::settingsDocksGeometry + "/" + objName).toByteArray();
        }

        QByteArray b = mStates[objName];

        foreach(QWidget* w, mLastActiveWindow->widgetsForDocks())
        {

            if(!mDockWidgets.contains(w->objectName()))
            {
                QDockWidget* d = new QDockWidget(w->windowTitle(), this);
                mDockWidgets[w->objectName()] = d;
                d->setObjectName(w->objectName());
            }

            mDockWidgets[w->objectName()]->setWidget(w);

            if(b.isEmpty())
                addDockWidget(Qt::RightDockWidgetArea, mDockWidgets[w->objectName()]);
        }

        if(!b.isEmpty())
            restoreState(b);
    }
}

void MainWindow::subWindowHasChanged(int index)
{
    if (mLastActiveWindow)
    {
        mLastActiveWindow->deactivate(this);
        updateDockWidgets(false);
    }

    mLastActiveWindow = 0;

    QWidget* window = mTabWidget->widget(index);
    if (window)
    {
        mLastActiveWindow = qobject_cast<BaseWindow*>(window);

        Q_ASSERT(mLastActiveWindow);
        mLastActiveWindow->activate(this);

        updateDockWidgets(true);
    }

    updateSpcificViewMenu();
}

void MainWindow::windowWillBeClosed(QWidget* w)
{
    BaseWindow* wnd = qobject_cast<BaseWindow*>(w);

    Q_ASSERT_X( wnd,
               "void MainWindow::windowWillBeClosed(QWidget *w)",
               "Given widget is null or invalid widget type!");

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int countActiveWindow = mTabWidget->subWindowList().size();
    for (int i = 0; i < countActiveWindow; i++) {
        if (!mTabWidget->closeWindow(mTabWidget->currentWidget()))
        {
            event->ignore();
            updateMenu();
            return;
        }
    }
    event->accept();

    QSettings settings;
    QMap<QString, QByteArray>::const_iterator it = mStates.begin();
    while(it != mStates.end())
    {
        settings.setValue(Config::settingsDocksGeometry + "/" + it.key(), it.value());
        ++it;
    }
    settings.setValue(Config::settingsMainWindowGeometry, saveGeometry());
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QList<QUrl>::iterator it = urls.begin();
    for(; it != urls.end(); it++) {
        QString fileName = it->toLocalFile();
        if(QFile::exists(fileName))
            load(fileName);
    }
    event->acceptProposedAction();
}
