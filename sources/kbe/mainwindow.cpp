/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

#include "interfaces/editorinterface.h"
#include "pluginmanager.h"
#include "guidedialog.h"
#include "newfiledialog.h"
#include "settingsdialog.h"

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
#include <QMimeData>

MainWindow* MainWindow::mInstance = 0;

MainWindow* MainWindow::getInstance()
{
    if(!mInstance)
        mInstance = new MainWindow();

    return mInstance;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mWindowCounter(0)
    , mLastActiveWindow(0)
    , mToolBarFile(0)
    , mToolBarEdit(0)
{
    ui->setupUi(this);

    mLastDir = QDir(QCoreApplication::applicationDirPath());

    /* creating tab widget */
    mTabWidget = new ExtendedTabWidget();
    connect(mTabWidget, SIGNAL(tabsUpdate()), this, SLOT(onUpdateMenu()));
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(onUpdateMenu()));

    setCentralWidget(mTabWidget);

    connect(mTabWidget, SIGNAL(currentChanged(int)),
            SLOT(subWindowHasChanged(int)), Qt::AutoConnection);
    connect(mTabWidget, SIGNAL(tabBeforeClose(QWidget*)),
            this, SLOT(windowWillBeClosed(QWidget*)));

    // creating actions
    createActions();
    createToolBars();

    onUpdateMenu();
    updateRecentFileActions();
    updateWindowTitle();

    new PluginManager();
    PluginManager::instance()->initialize(Config::pathPlugins.absolutePath());

    // blur effect
    mBlurEffect = new QGraphicsBlurEffect(this);
    mBlurEffect->setEnabled(false);
    setGraphicsEffect(mBlurEffect);

    // restore geometry from settings
    QSettings settings;
    restoreGeometry(settings.value(Config::settingsMainWindowGeometry).toByteArray());

    setAcceptDrops(true);

    mSettingsDialog = new SettingsDialog(this);
    mSettingsDialog->initialize();
}


MainWindow::~MainWindow()
{
    delete mBlurEffect;
    delete mToolBarFile;
    delete mToolBarEdit;
    delete ui;
    delete mTabWidget;

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

    mToolBarFile->addSeparator();
    mToolBarFile->addAction(ui->actionClose);

    mToolBarFile->setObjectName("Main Tools");
    mToolBarFile->setWindowTitle(tr("Main Tools"));

    addToolBar(mToolBarFile);

    //! @bug State of toolbars is not saved for now.
    mToolBarFile->setMovable(false);
}

void MainWindow::createActions()
{
    ui->actionNew->setIcon(QIcon::fromTheme("document-new", getIcon("document-new.png")));
    ui->actionNew_Project->setIcon(QIcon::fromTheme("document-new", getIcon("document-new.png")));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open", getIcon("document-open.png")));
    ui->actionOpen_Project->setIcon(QIcon::fromTheme("document-open", getIcon("document-open.png")));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save", getIcon("document-save.png")));
    ui->actionSave_as->setIcon(QIcon::fromTheme("document-save-as", getIcon("document-save-as.png")));
    ui->actionSave_Project->setIcon(QIcon::fromTheme("document-save", getIcon("document-save-as.png")));
    ui->actionClose->setIcon(QIcon::fromTheme("window-close", getIcon("window-close.png")));
    ui->actionExit->setIcon(QIcon::fromTheme("application-exit", getIcon("application-exit.png")));

    ui->actionAbout->setIcon(QIcon::fromTheme("help-browser", getIcon("help-browser.png")));
    ui->actionFeedback->setIcon(QIcon::fromTheme("mail", getIcon("mail.png")));

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onFileNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onFileSave()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
    connect(ui->actionSave_all, SIGNAL(triggered()), this, SLOT(onFileSaveAll()));
    connect(ui->actionTo_image, SIGNAL(triggered()), this, SLOT(onFileExportToImage()));

    connect(ui->actionClose_All, SIGNAL(triggered()), mTabWidget, SLOT(closeAllDocuments()));
    connect(ui->actionClose, SIGNAL(triggered()), mTabWidget, SLOT(close()));
    connect(ui->actionClose_Others, SIGNAL(triggered()), mTabWidget, SLOT(closeOtherDocuments()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(onUpdateMenu()));
    connect(ui->actionClose_Others, SIGNAL(triggered()), this, SLOT(onUpdateMenu()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onFileExit()));

    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(onViewSettings()));

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        ui->menuFile->insertAction(ui->actionExit, recentFileActs[i]);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(onOpenRecentFile()));
    }
    separatorAct = ui->menuFile->insertSeparator(ui->actionExit);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(onHelpAboutQt()));
    connect(ui->actionFeedback, SIGNAL(triggered()), this, SLOT(onFeedback()));
    connect(ui->actionGuide, SIGNAL(triggered()), this, SLOT(onGuide()));

    this->addAction(ui->actionExit);
    this->addAction(ui->actionAbout);
}

void MainWindow::updateEvent(EditorInterface *editor, EditEvents event)
{
    Q_UNUSED(editor);

    switch(event)
    {
    case ContentChanged:
    case ContentLoaded:
    case ContentSaved:
        onUpdateMenu();
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

void MainWindow::onUpdateMenu()
{
    EditorInterface *subWindow = activeChild();

    ui->actionSave->setEnabled(subWindow && !subWindow->isSaved());
    ui->actionSave_as->setEnabled(subWindow != 0);
    ui->actionSave_all->setEnabled(subWindow != 0 && !checkSubWindowSavedState());

    ui->actionClose->setEnabled(subWindow != 0);
    ui->actionClose_All->setEnabled(subWindow != 0);
    ui->actionClose_Others->setEnabled(mTabWidget->subWindowList().size() > 1);
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

void MainWindow::onOpenRecentFile()
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

EditorInterface* MainWindow::createSubWindowByType(const QString& type)
{
    EditorInterface* childWindow = 0;

    if (PluginManager::instance()->getEditorFactoriesByType().contains(type))
        childWindow = PluginManager::instance()->createWindowByType(type);
    else
        return 0;

    mWidget2EditorInterface[childWindow->widget()] = childWindow;
    mTabWidget->addSubWindow(childWindow);
    childWindow->_setObserver(this);

    return childWindow;
}

EditorInterface* MainWindow::createSubWindowByExt(const QString& ext)
{
    EditorInterface* childWindow = 0;

    if (PluginManager::instance()->getEditorFactoriesByExt().contains(ext))
        childWindow = PluginManager::instance()->createWindowByExt(ext);
    else
        return 0;
    mWidget2EditorInterface[childWindow->widget()] = childWindow;
    mTabWidget->addSubWindow(childWindow);
    childWindow->_setObserver(this);

    return childWindow;
}

QString MainWindow::getSettingKeyValueForWindow(const QString& editorType) const
{
    return Config::settingsDocksGeometry + "/" + editorType;
}

void MainWindow::onFileNew()
{
    if (PluginManager::instance()->getEditorFactoriesByType().size() > 0)
    {
        NewFileDialog *fileNewDlg = new NewFileDialog(this);

        int dlgResult = fileNewDlg->exec();
        if (dlgResult == QDialog::Accepted)
            createSubWindowByType(fileNewDlg->selectedEditor());
    }
}

void MainWindow::onFileOpen(QString fileName)
{
    if (fileName.isNull())
    {
        QFileDialog::Options options;
        options |= QFileDialog::DontUseNativeDialog;
        QString selectedFilter;
        QFileDialog dlg;

        mBlurEffect->setEnabled(true);
        dlg.setDirectory(mLastDir);
        fileName = dlg.getOpenFileName(this,
                                       tr("Open file"),
                                       "",
                                       PluginManager::instance()->openFilters(),
                                       &selectedFilter,
                                       options);
        mLastDir = QDir(fileName);
        mBlurEffect->setEnabled(false);
    }

    if (!fileName.isEmpty() && QFile::exists(fileName))
    {
        if (!mTabWidget->activateTab(fileName))
            load(fileName);
        return;
    }

}

void MainWindow::load(QString fileName)
{
    QFileInfo fi(fileName);
    QString ext = fi.suffix();
    if(PluginManager::instance()->getSupportedFilesExt().contains(ext))
    {
        EditorInterface* childWindow = createSubWindowByExt(ext);

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

        if(PluginManager::instance()->getSupportedFilesExt().contains(ext))
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

void MainWindow::onFileSave(QWidget* window)
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
            onFileSaveAs(childWindow->widget());
    }
}

void MainWindow::onFileSaveAs(QWidget* window)
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
    QString fileName = mLastDir.path() + "/" + childWindow->currentFileName();
    mBlurEffect->setEnabled(true);
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save file to .."),
                                            fileName,
                                            formatsStr,
                                            &selectedFilter,
                                            options);
    mLastDir = QDir(fileName);
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

void MainWindow::onFileSaveAll()
{

}

void MainWindow::onFileExportToImage()
{

}

void MainWindow::onFileExit()
{
    close();
}

void MainWindow::onViewSettings()
{
    Q_ASSERT(mSettingsDialog);
    mSettingsDialog->show();
}

void MainWindow::onHelpAbout()
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
                          "<li>Alexander Yurkov (zioba)</li>"
                          "<li>Witkowsky Dmitry (wagos)</li>"
                          "<li>Aliaksei Palkanau (lifus)</li>"
                          "<li>Nikita Grishko (Gr1N)</li>"
                          "<li>Denis Klimenko</li>"
                          "<li>Dmitry Kolb (skif-sarmat)</li>"
                          "<li>Konstantin Savon (Konstantsin)</li>"
                          "<li>Sergei Yakimchik (Gudini)</li>"
                          "<li>Lapitsky Artem</li>"
                          "<li>Eugen Zakharich</li>"
                          "<li>Pavel Karpan (pioneer)</li>"
                          "</ul>"
                          "</td></tr></table>")
                       .arg(QString(":/media/icons/help-about-logo.png"))
                       .arg(tr("Knowledge Base source Editor "))
                       .arg(tr("version"))
                       .arg(VERSION.toString())
                       .arg(tr("Authors"))
                       .arg(tr("Contributors")));
}

void MainWindow::onHelpAboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::onFeedback()
{
    QMessageBox::about(this, tr("Feedback"),
                       QString("%1 <a href=\"https://sem.systems\">%2</a>."
                               "<br/>%3 <a href=\"%4\">%5</a>.")
                       .arg(tr("Founded errors and new ideas you can send to developers on"))
                       .arg(tr("site"))
                       .arg(tr("Also you can find our contact information on "))
                       .arg("https://sem.systems/#contacts")
                       .arg(tr("here")));
}

void MainWindow::onGuide()
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
    Q_UNUSED(event);
}

void MainWindow::updateDockWidgets(bool visible)
{
    Q_ASSERT_X(mLastActiveWindow,
               "void MainWindow::updateDockWidgets(bool hide)",
               "window must be activated first!");

    QString windowClassName = mLastActiveWindow->widget()->metaObject()->className();
    if(!visible)
    {
        mStates[windowClassName] = saveState();
        QMap<QString, QDockWidget*>::const_iterator it = mDockWidgets.begin();
        while(it != mDockWidgets.end())
        {
            it.value()->close();
            ++it;
        }
    }else
    {
        foreach(QWidget* w, mLastActiveWindow->widgetsForDocks())
        {
            if(!mDockWidgets.contains(w->objectName()))
            {
                QDockWidget* d = new QDockWidget(w->windowTitle(), this);
                mDockWidgets[w->objectName()] = d;
                d->setObjectName(w->objectName());
            }
            mDockWidgets[w->objectName()]->setWidget(w);
                addDockWidget(Qt::RightDockWidgetArea, mDockWidgets[w->objectName()]);
        }
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

    updateWindowTitle();
}

bool MainWindow::windowWillBeClosed(QWidget* w)
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
        QString fileName = editor->currentFileName();

        if(fileName.isEmpty())
            //: Appers after 'Do you want to save changes in '
            fileName = tr("newly created document");

        int question = QMessageBox::question(this, tr("Save changes"),
                                             tr("Do you want to save changes in %1 ?").arg(fileName),
                                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);

        if (question == QMessageBox::Yes)
        {
            onFileSave(it.key());
        }
        if(question == QMessageBox::Cancel){
            return false;
        }
    }

    mWidget2EditorInterface.erase(it);
    return true;
}

void MainWindow::saveLayout() const
{
    QSettings settings;

    // Save window geometry (width, height) and layout
    settings.setValue(Config::settingsMainWindowGeometry, saveGeometry());

    // Save layouts for all used editor types.
    QMap<QString, QByteArray>::const_iterator i;
    for(i = mStates.constBegin(); i != mStates.constEnd() ; i++)
    {
        settings.setValue(getSettingKeyValueForWindow(i.key()), i.value());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{  
    // close all child windows
    QList<QWidget*> widgets = mWidget2EditorInterface.keys();
    QWidget *widget = 0;
    foreach (widget, widgets)
    {
        if(!mTabWidget->onCloseWindow(widget))
        {
            event->ignore();
            return;
        }
    }

    saveLayout();
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
    for(; it != urls.end(); it++)
    {
        QString fileName = it->toLocalFile();
        if(QFile::exists(fileName))
            load(fileName);
    }
    event->acceptProposedAction();
}


