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

#include "config.h"

#include "interfaces/editorinterface.h"
#include "pluginmanager.h"
#include "guidedialog.h"

#include "version.h"

#include <QMdiSubWindow>
#include <QToolBar>
#include <QStyleFactory>
#include <QSignalMapper>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
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
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateMenu()));

    setCentralWidget(mTabWidget);

    connect(mTabWidget, SIGNAL(currentChanged(int)),
            SLOT(subWindowHasChanged(int)), Qt::AutoConnection);
    connect(mTabWidget, SIGNAL(tabBeforeClose(QWidget*)),
            this, SLOT(windowWillBeClosed(QWidget*)));

    // creating actions
    createActions();
    createToolBars();

    updateMenu();
    updateSpecificViewMenu();
    updateRecentFileActions();
    updateWindowTitle();

    new PluginManager();
    PluginManager::instance()->initialize(Config::pathPlugins.absolutePath());

    //QApplication::setStyle(QStyleFactory::create("Plastique"));
    //QApplication::setPalette(QApplication::style()->standardPalette());

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

//    ReadWriteManager::destroy();
//    LayoutManager::destroy();

    PluginManager::instance()->shutdown();
    delete PluginManager::instance();
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
    ui->actionFeedback->setIcon(QIcon::fromTheme("mail", getIcon("mail.png")));

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
    connect(ui->actionFeedback, SIGNAL(triggered()), this, SLOT(feedback()));
    connect(ui->actionGuide, SIGNAL(triggered()), this, SLOT(guide()));
}

void MainWindow::updateEvent(EditorInterface *editor, EditEvents event)
{
    switch(event)
    {
    case ContentChanged:
    case ContentLoaded:
    case ContentSaved:
        updateMenu();
        updateSpecificViewMenu();
        updateWindowTitle();
        break;
    }
}

QIcon MainWindow::getIcon(const QString &name) const
{
    return QIcon(QString(":/media/icons/") + name);
}

bool MainWindow::checkSubWindowSavedState()
{
    QList<QWidget*> list = mTabWidget->subWindowList();
    QList<QWidget*>::iterator it = list.begin();
    for(; it != list.end(); it++)
        if (!qobject_cast<EditorInterface*>(*it)->isSaved())
            return false;
    return true;
}

EditorInterface *MainWindow::activeChild()
{
    if (QWidget *activeSubWindow = mTabWidget->currentWidget())
    {
        Widget2EditorInterfaceMap::iterator it = mWidget2EditorInterface.find(activeSubWindow);
        if (it != mWidget2EditorInterface.end())
            return *it;
    }
    return 0;
}

void MainWindow::updateMenu()
{
    EditorInterface *subWindow = activeChild();

    ui->actionSave->setEnabled(subWindow && !subWindow->isSaved());
    ui->actionSave_as->setEnabled(subWindow != 0);
    ui->actionSave_all->setEnabled(subWindow != 0 && !checkSubWindowSavedState());
    //ui->menuExport->setEnabled(subWindow !=0);

    ui->actionClose->setEnabled(subWindow != 0);
    ui->actionClose_All->setEnabled(subWindow != 0);
    ui->actionClose_Others->setEnabled(mTabWidget->subWindowList().size() > 1);
}

void MainWindow::updateSpecificViewMenu()
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

void MainWindow::updateWindowTitle()
{
    QWidget *window = mTabWidget->currentWidget();

    if (window != 0)
    {
        setWindowTitle(tr("%1 - KBE version %2").arg(mTabWidget->tabTextFor(window)).arg(VERSION_STR));
    }else
    {
        setWindowTitle(tr("Knowledge Base source Editor - version %1").arg(VERSION_STR));
    }
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

EditorInterface* MainWindow::createSubWindow(const QString& ext)
{
    EditorInterface* childWindow = 0;

    if (PluginManager::instance()->supportedFilesExt().contains(ext))
        childWindow = PluginManager::instance()->createWindow(ext);
    else
        return 0;

    mWidget2EditorInterface[childWindow->widget()] = childWindow;
    mTabWidget->addSubWindow(childWindow);
    childWindow->_setObserver(this);

    return childWindow;
}

void MainWindow::fileNew()
{
    if (PluginManager::instance()->supportedFilesExt().size() > 0)
    {
        QDialog *fileNewDlg = new QDialog(this);
        QVBoxLayout *lay = new QVBoxLayout;
        QLabel *lab = new QLabel(tr("List of available formats:"));

        QListWidget *availableTypesList = new QListWidget;
        availableTypesList->setSelectionMode(QAbstractItemView::SingleSelection);
        availableTypesList->setIconSize(QSize(16, 16));

        foreach (QString ext, PluginManager::instance()->supportedFilesExt())
            availableTypesList->addItem(new QListWidgetItem(QIcon(), ext + " format (."+ ext + ")"));

        QHBoxLayout *buttonLay = new QHBoxLayout;
        QPushButton *butOk = new QPushButton(tr("OK"));

        if (availableTypesList->count() > 0)
            availableTypesList->item(0)->setSelected(true);
        else
            butOk->setEnabled(false);

        QPushButton *butCancel = new QPushButton(tr("Cancel"));

        buttonLay->addWidget(butOk, 1, Qt::AlignRight);
        buttonLay->addWidget(butCancel, 1, Qt::AlignRight);

        lay->addWidget(lab);
        lay->addWidget(availableTypesList);
        lay->addLayout(buttonLay);
        fileNewDlg->setLayout(lay);

        connect(butOk, SIGNAL(clicked()), fileNewDlg, SLOT(accept()));
        connect(butCancel, SIGNAL(clicked()), fileNewDlg, SLOT(reject()));

        int dlgResult = fileNewDlg->exec();
        if (dlgResult == QDialog::Accepted)
        {
            QString str = availableTypesList->selectedItems().at(0)->text();
            QString format = str.mid(0, str.indexOf(" "));
            createSubWindow(format);
        }

    }
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
                                           PluginManager::instance()->openFilters(),
                                           &selectedFilter,
                                           options);
    if (!fileName.isEmpty())
        load(fileName);
    mBlurEffect->setEnabled(false);
}

void MainWindow::load(QString fileName)
{
    QFileInfo fi(fileName);
    QString ext = fi.suffix();
    if(PluginManager::instance()->supportedFilesExt().contains(ext))
    {
        EditorInterface* childWindow = createSubWindow(ext);

        if (childWindow->loadFromFile(fileName))
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

    } else
        QMessageBox::warning(this, qAppName(), tr("Can't load file.\nUnsupported file format \"%1\"").arg(ext));
}

bool MainWindow::saveWindow(EditorInterface* window, QString& name, const QString& ext)
{
    if(!name.isEmpty() && window)
    {
        bool retVal = false;

        if(PluginManager::instance()->supportedFilesExt().contains(ext))
        {
            if (!name.endsWith("." + ext))
                name += "." + ext;

            retVal = window->saveToFile(name);
        } else
            QMessageBox::warning(this, qAppName(), tr("Can't save file.\nUnsupported file format \"%1\"").arg(ext));

        return retVal;
    }

    return false;
}

void MainWindow::fileSave(QWidget* window)
{
    EditorInterface* childWindow = 0;

    Widget2EditorInterfaceMap::iterator it = mWidget2EditorInterface.find(window);
    if (it != mWidget2EditorInterface.end())
        childWindow = *it;

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
            fileSaveAs(childWindow->widget());
    }
}

void MainWindow::fileSaveAs(QWidget* window)
{
    EditorInterface* childWindow = 0;
    Widget2EditorInterfaceMap::iterator it = mWidget2EditorInterface.find(window);
    if (it != mWidget2EditorInterface.end())
        childWindow = *it;

    if(!childWindow)
        childWindow = activeChild();

    Q_ASSERT(childWindow);

    QString formatsStr = PluginManager::instance()->saveFilters(childWindow->supportedFormatsExt());
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
    {
        //! TODO: use regular expression
        int pos = selectedFilter.indexOf("*.");
        Q_ASSERT_X(pos != -1, "MainWindow::fileSaveAs", "Can't find begin of extension");
        pos += 2;
        int pos2 = selectedFilter.indexOf(")", pos);
        Q_ASSERT_X(pos2 != -1, "MainWindow::fileSaveAs", "Can't find end of extension");
        saveWindow(childWindow, fileName, selectedFilter.mid(pos, pos2 - pos).trimmed());
    }

    mBlurEffect->setEnabled(false);

}

void MainWindow::fileSaveAll()
{
//    for(int i = 0; i < mTabWidget->subWindowList().size(); i++) {
//        if (!qobject_cast<SCgWindow*>(activeChild())->isSaved())
//            fileSave();
//            mTabWidget->setCurrentIndex(mTabWidget->currentIndex()+1);
//        }
}

void MainWindow::fileExportToImage()
{
//    SCgWindow *childWindow = qobject_cast<SCgWindow*>(activeChild());

//    if(childWindow){

//        QString formatsStr = ReadWriteManager::instance().exportFilters();
//        QFileDialog::Options options;
//        options |= QFileDialog::DontUseNativeDialog;


//        QString selectedFilter;
//        QFileDialog dlg;

//        mBlurEffect->setEnabled(true);
//        QString fileName = QCoreApplication::applicationDirPath() + "/" + childWindow->currentFileName();
//        fileName = dlg.getSaveFileName(this,
//                                       tr("Export file to ..."),
//                                       fileName,
//                                       formatsStr,
//                                       &selectedFilter,
//                                       options);

//        if (!fileName.isEmpty())
//        {
//            QString ext = ReadWriteManager::instance().extFromFilter(selectedFilter);
//            if (!fileName.endsWith("." + ext))
//                fileName += "." + ext;
//            AbstractFileWriter *writer = ReadWriteManager::instance().createWriter(ext);
//            childWindow->saveToFile(fileName, writer);
//            delete writer;
//        }
//        mBlurEffect->setEnabled(false);
//    }

}

void MainWindow::fileExit()
{
    close();
}

void MainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About KBE"),
                       tr("<table><tr valign=\"middle\"><td align=\"left\"><img src=\"%1\"></td>"
                          "<td>%2 %3: %4 <br> <br> Site: "
                          "<STYLE type=\"text/css\">"
                          "a:link {text-decoration: none}"
                          "</STYLE>"
                          "<a href=\"http://www.ostis.net\">http://www.ostis.net</a>"
                          "<br> <br>Copyright  OSTIS.net</td></tr><tr>"
                          "<td></td><td>%5:<ul>"
                          "<li>Denis Koronchik</li>"
                          "<li>Gumbar Ilya (zooner)</li>"
                          "<li>Harkunov Evgeny (filosov)</li>"
                          "</ul>%6:<ul>"
                          "<li>Witkowsky Dmitry (wagos)</li>"
                          "<li>Aliaksei Palkanau (lifus)</li>"
                          "<li>Nikita Grishko (Gr1N)</li>"
                          "<li>Denis Klimenko</li>"
                          "<li>Konstantin Savon (Konstantsin)</li>"
                          "<li>Sergei Yakimchik (Gudini)</li>"
                          "<li>Lapitsky Artem</li>"
                          "<li>Eugen Zakharich</li>"
                          "<li>Pavel Karpan (pioneer)</li>"
                          "<li>Dmitry Kolb (skif-sarmat)</li>"
                          "</ul>"
                          "</td></tr></table>")
                       .arg(QString(":/media/icons/help-about-logo.png"))
                       .arg(tr("Knowledge Base source Editor "))
                       .arg(tr("version"))
                       .arg(VERSION.toString())
                       .arg(tr("Authors"))
                       .arg(tr("Contributors")));
}

void MainWindow::helpAboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::feedback()
{
    QMessageBox::about(this, tr("Feedback"),
                       QString("%1 <a href=\"http://forum.ostis.net/viewtopic.php?f=7&t=3\">%2</a>."
                               "<br/>%3 <a href=\"%4\">%5</a>.")
                       .arg(tr("Founded errors and new ideas you can write in"))
                       .arg(tr("forum"))
                       .arg(tr("Also you can find our contact information on "))
                       .arg("http://www.ostis.net/feedback.html")
                       .arg(tr("site")));
}

void MainWindow::guide()
{
    GuideDialog dlg;
    dlg.exec();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    switch (event->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
}


void MainWindow::updateDockWidgets(bool visible)
{
    Q_ASSERT_X(mLastActiveWindow,
               "void MainWindow::updateDockWidgets(bool hide)",
               "window must be activated first!");

    QString objName = mLastActiveWindow->widget()->objectName();

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
        Q_ASSERT(mWidget2EditorInterface.contains(window));

        mLastActiveWindow = mWidget2EditorInterface[window];

        Q_ASSERT(mLastActiveWindow);
        mLastActiveWindow->activate(this);

        updateDockWidgets(true);
    }

    updateSpecificViewMenu();
    updateWindowTitle();
}

void MainWindow::windowWillBeClosed(QWidget* w)
{
    QMap<QWidget*, EditorInterface*>::iterator it = mWidget2EditorInterface.find(w);


    Q_ASSERT_X( it != mWidget2EditorInterface.end(),
               "void MainWindow::windowWillBeClosed(QWidget *w)",
               "There are no conversion to editor interface for a given window");

    it.value()->_setObserver(0);

    // check if it saved
    EditorInterface *editor = it.value();
    if (!editor->isSaved())
    {
        if (QMessageBox::question(this, tr("Save changes"),
                                  tr("Do you want to save changes in %1 ?").arg(editor->currentFileName()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            fileSave(it.key());
        }
    }

    mWidget2EditorInterface.erase(it);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue(Config::settingsMainWindowGeometry, saveGeometry());

    // close all child windows
    QList<QWidget*> widgets = mWidget2EditorInterface.keys();
    QWidget *widget = 0;
    foreach (widget, widgets)
        mTabWidget->closeWindow(widget);
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
