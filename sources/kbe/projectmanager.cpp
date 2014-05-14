#include "projectmanager.h"

#include "pluginmanager.h"
#include "newfiledialog.h"

#include <QMouseEvent>
#include <QProcess>

#include <QHeaderView>
#include <QMenu>
#include <QAction>

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

ProjectManagerDockWidget* ProjectManagerDockWidget::mInstance = 0;

ProjectManagerDockWidget::ProjectManagerDockWidget(QWidget *parent) :
    QDockWidget(parent)
{   
    treeView = new ProjectManagerView(this);

    this->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);

    QFile file(":/media/stylesheets/projectmanager.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    treeView->setStyleSheet(styleSheet);

    setWidget(treeView);
}

ProjectManagerDockWidget::~ProjectManagerDockWidget()
{
    Q_ASSERT(mInstance != 0);
    mInstance = 0;
}

ProjectManagerDockWidget* ProjectManagerDockWidget::instance()
{
    if (!mInstance)
        mInstance = new ProjectManagerDockWidget();

    return mInstance;
}

ProjectManagerView::ProjectManagerView(QWidget *parent) :
    QTreeView(parent)
{
    model = new ProjectManagerModel(this);
    setModel(model);

    header() -> close();

    setContextMenuPolicy(Qt::CustomContextMenu);

    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setDropIndicatorShown(true);

    this->connect(this,SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(onContextMenuRequested(QPoint)));

}

void ProjectManagerView::onContextMenuRequested(QPoint mousePoint)
{
    ProjectManagerModelItem* item = model -> getItem(currentIndex());
    createContextMenu(item);
}

void ProjectManagerView::createContextMenu(ProjectManagerModelItem* item)
{
    QMenu *menu = new QMenu;

    if (item)
        switch (item->getItemType())
        {
        case ProjectManagerModelItem::Unknown:
            break;
        case ProjectManagerModelItem::Project:
            {
#ifndef Q_OS_LINUX
                menu -> addAction(QIcon(), tr("Show in explorer"), this, SLOT(onShowInExplorer()));
                menu -> addSeparator();
#endif
                menu -> addAction(QIcon(":/media/icons/document-save.png"), tr("Save project"), this, SLOT(onProjectSave()));
                menu -> addAction(QIcon(":/media/icons/window-close.png"), tr("Close Project"),this,SLOT(onProjectClose()));

                menu -> addSeparator();
            }
        case ProjectManagerModelItem::Filter:
            {
                menu -> addAction(QIcon(":/media/icons/pm-add.png"), tr("Add File"),this,SLOT(onAddFile()));
                menu -> addAction(QIcon(":/media/icons/pm-add.png"), tr("Add Existing Files"), this, SLOT(onAddExistingFiles()));
                menu -> addAction(QIcon(":/media/icons/pm-add.png"), tr("Add Filter"), this, SLOT(onAddFilter()));

                menu -> addSeparator();

                menu -> addAction(QIcon(), tr("Rename"), this, SLOT(onRename()));
                QMenu* delMenu = menu -> addMenu(QIcon(), tr("Delete"));
                    delMenu -> addAction(QIcon(), tr("Delete From Project"),this,SLOT(onRemove()));
                    delMenu -> addAction(QIcon(), tr("Delete Permanently"),this,SLOT(onRemovePermanently()));

                menu -> addSeparator();

                menu -> addAction(QIcon(":/media/icons/pm-expand.png"),tr("Expand All"),this,SLOT(expandAll()));
                menu -> addAction(QIcon(":/media/icons/pm-collapse.png"),tr("Collapse All"),this,SLOT(collapseAll()));
                break;
            }
        case ProjectManagerModelItem::File:
            {
                menu -> setDefaultAction(menu -> addAction(QIcon(), tr("Open file"),this,SLOT(onOpenFile())));

#ifdef Q_OS_WIN
                menu -> addAction(QIcon(), tr("Show in explorer"), this, SLOT(onShowInExplorer()));
#endif

                menu -> addSeparator();

                menu -> addAction(QIcon(), tr("Rename"), this, SLOT(onFileRename()));
                QMenu* delMenu = menu -> addMenu(QIcon(), tr("Delete"));
                delMenu -> addAction(QIcon(), tr("Delete From Project"),this,SLOT(onRemove()));
                delMenu -> addAction(QIcon(), tr("Delete Permanently"),this,SLOT(onRemovePermanently()));

                menu -> addSeparator();
                menu -> addAction(QIcon(), tr("Properties"), this, SLOT(onPropertiesShow()));
            }
        }
    else
    {
        menu -> addAction(QIcon(":/media/icons/pm-expand.png"),tr("Expand All"),this,SLOT(expandAll()));
        menu -> addAction(QIcon(":/media/icons/pm-collapse.png"),tr("Collapse All"),this,SLOT(collapseAll()));

        menu -> addSeparator();

        menu -> addAction(QIcon(":/media/icons/window-close.png"),tr("Close Project"),this,SLOT(onProjectClose()));
    }
    menu->exec(QCursor::pos());
}


void ProjectManagerView::mouseDoubleClickEvent(QMouseEvent *event)
{
    ProjectManagerModelItem* item = model->getItem(indexAt(event->pos()));
    QTreeView::mouseDoubleClickEvent(event);

    if (item && item->getItemType() == ProjectManagerModelItem::File)
    {
        if (!QFile::exists(item->getAbsoluteFilePath()))
        {
            QString filter = item -> getAbsoluteFilePath().split(SEPARATOR).last();
            filter.append(" ("+filter+");;");
            filter.append(tr("Any file") + " (*." + item->getAbsoluteFilePath().split(".").last() + ")");
            QString existingFileForReplace = QFileDialog::getOpenFileName(this, tr("File not found"), item->getAbsoluteFileDir(),
                                                                          filter,0,QFileDialog::DontUseNativeDialog);
            if (existingFileForReplace.isNull())
                return;
            else
            {
                QString newFilePath;
                newFilePath = QDir(item->getProjectItem()->getAbsoluteSourcesDir()).relativeFilePath(existingFileForReplace);
                int reply = QMessageBox::question(this, tr("Replace file path"), tr("Replace file path to \"")+newFilePath+
                                                  tr("\" instead \"") + item->getFilePath() + "\"", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes)
                {
                    if (item -> getName() != QFileInfo(existingFileForReplace).fileName())
                    {
                        item->setObjectName(item->parent()->objectName() + SEPARATOR + QFileInfo(existingFileForReplace).fileName());
                        item->setName(QFileInfo(existingFileForReplace).fileName());
                    }
                    item->setFilePath(newFilePath);
                }
                else
                {
                    emit openFile(newFilePath);
                    return;
                }
            }
        }
        emit openFile(item->getAbsoluteFilePath());
    }

}

void ProjectManagerView::updateTreeView()
{
    QModelIndexList list;

    Q_FOREACH (QModelIndex index, model->getPersistentIndexList())
        if (isExpanded(index))
            list << index;

    reset();

    Q_FOREACH (QModelIndex index, list)
        if (index.isValid())
            expand(index);
}


void ProjectManagerView::mousePressEvent(QMouseEvent* event)
{
    QModelIndex item = indexAt(event->pos());
    QTreeView::mousePressEvent(event);
    if ((item.row() == -1 && item.column() == -1))
    {
        clearSelection();
        const QModelIndex index;
        selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}


void ProjectManagerView::onProjectNew()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Add new project"),
                                                    QDir::current().absolutePath(),
                                                    tr("Folder"),
                                                    0, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty())
        return;

    QFileInfo projectFileInfo(fileName);

    QString name = projectFileInfo.fileName();
    QString absPath = projectFileInfo.absoluteFilePath();
    QDir parentDir = projectFileInfo.absoluteDir();

    if (model->getRootItem()->findChild<ProjectManagerModelItem*>(name))
    {
        QMessageBox::warning(this,tr("Adding project error"),name+" "+tr("already exists"));
        return onProjectNew();
    }

    //creating project's directory
    if (parentDir.mkdir(name))
    {
        parentDir = QDir(absPath);
        parentDir.mkdir("sources");

        ProjectManagerModelItem* project = new ProjectManagerModelItem(name,QFileInfo(absPath,name+".kbpro").absoluteFilePath(),
                                                                       ProjectManagerModelItem::Project,
                                                                       model->getRootItem());
        model->insertProject(project);
        model->saveProject(project, QFileInfo(absPath,name+".kbpro").absoluteFilePath());
        emit event(ProjectCreated);
    }
    else
        QMessageBox::critical(this, tr("Creating project error"),
                              tr("Can not create directory for project"));

}


void ProjectManagerView::onProjectSave()
{
    if (ProjectManagerModelItem* rootItem = model->getRootItem())
        for (int i=0; i< rootItem->childCount(); i++)
        {
            QString fileName = rootItem->child(0)->getAbsoluteFilePath();

            if (rootItem->child(i)->getFilePath().isEmpty() || !QFile::exists(fileName))
            {
                fileName = QFileDialog::getSaveFileName(this, tr("Project file not found"),
                                                        QDir::current().absolutePath(),rootItem->child(i)->getName()+"(*.kbpro)",
                                                        0,QFileDialog::DontUseNativeDialog);
                if (fileName.isEmpty())
                    continue;

                rootItem->child(i)->setFilePath(fileName);
            }
            model->saveProject(rootItem->child(i),fileName);
            emit event(ProjectSaved);
        }
}



bool ProjectManagerView::onProjectClose()
{
    if (ProjectManagerModelItem* rootItem = model->getRootItem())
        while (rootItem->childCount())
        {
            ProjectManagerModelItem* item = rootItem->child(0);
            if (item && item->isModified())
            {
                int ret = QMessageBox::warning(this, tr("Save project?"),
                                     tr("Project") + " " + item->getName() + " " + tr("is modified but not saved. Do you want save project?"),
                                     QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
                switch (ret)
                {
                case QMessageBox::Cancel:
                    return false;
                case QMessageBox::Yes:
                {
                    QString fileName = item->getAbsoluteFilePath();

                    if (item->getFilePath().isEmpty() || !QFile::exists(fileName))
                    {
                        fileName = QFileDialog::getSaveFileName(this, tr("Project file not found"),
                                                                QDir::current().absolutePath(),item->getName()+("(*.kbpro)"),
                                                                0,QFileDialog::DontUseNativeDialog);
                        if (fileName.isEmpty())
                            return false;

                        item->setFilePath(fileName);
                    }

                    model->saveProject(item,item->getAbsoluteFilePath());
                }
                case QMessageBox::No:
                    break;
                }
            }
            model->removeItem(item);
        }
    emit event(ProjectClosed);
    return true;
}

void ProjectManagerView::onProjectOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose project file"),
                                                    QDir::current().absolutePath(),tr("KBE project file")+("(*.kbpro)"),
                                                    0,QFileDialog::DontUseNativeDialog);
    if (!fileName.isEmpty())
    {
        model->loadProject(fileName);
        emit event(ProjectOpened);
    }
}


void ProjectManagerView::onRemove()
{
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    if (item && item->getItemType() != ProjectManagerModelItem::Project)
    {
        model->removeItem(item);
        emit event(ProjectChanged);
    }
}


void ProjectManagerView::onRemovePermanently()
{
    if (!currentIndex().isValid())
        return;

    if (ProjectManagerModelItem* item = model->getItem(currentIndex()))
        switch (item->getItemType())
        {
        case ProjectManagerModelItem::File:
            if (QFile::remove(item->getAbsoluteFilePath()))
                onRemove();
            break;
        case ProjectManagerModelItem::Filter:
            permanentRemoveTree(item);
            emit event(ProjectChanged);
        }
}


void ProjectManagerView::permanentRemoveTree(ProjectManagerModelItem *item)
{
    if (!item)
        return;

    while (item->childCount())
        permanentRemoveTree(item->child(0));

    switch (item->getItemType())
    {
        case ProjectManagerModelItem::File:
            QFile::remove(item->getAbsoluteFilePath());

        case ProjectManagerModelItem::Filter:
            model->removeItem(item);
    }

}


void ProjectManagerView::renameItem(ProjectManagerModelItem *item, QString newName)
{
    if (item && item->parent())
    {
        QString objName = item -> objectName();
        QString itemName = item -> getName();
        objName.replace(objName.length()-itemName.length(),itemName.length(), newName);
        item -> setName(newName);
    }
}


QString ProjectManagerView::onRename()
{
    if (!currentIndex().isValid())
        return QString();
    ProjectManagerModelItem* item = model->getItem(currentIndex());
    QString itemName(item->getName());

    bool isAccepted = true;
    QString newName = QInputDialog::getText(this,tr("Rename"),tr("Please type new name for ")+itemName,
                          QLineEdit::Normal,itemName,&isAccepted,Qt::Dialog);

    if (isAccepted && !newName.isEmpty() && newName != itemName)
    {
        if (item->parent() && item->parent()->findChild<ProjectManagerModelItem*>(item->parent()->objectName()+"/"+newName))
        {
            QMessageBox::warning(this,tr("Rename error"),item->parent()->getName()+ " " + tr("already has") + " " + newName);
            return onRename();
        }
        emit event(ProjectChanged);
        if (item -> getItemType() <= ProjectManagerModelItem::Filter)
            renameItem(item,newName);
        return newName;
    }
    else
        return itemName;
}


void ProjectManagerView::onFileRename()
{
    if (!currentIndex().isValid())
        return;

    ProjectManagerModelItem* item = model->getItem(currentIndex());

    QString newName = onRename();

    QFileInfo currentFileInfo(item->getAbsoluteFilePath());

    if (!currentFileInfo.exists())
    {
        QMessageBox::critical(this,tr("Rename critical error"),tr("File not found on storage: ") + currentFileInfo.absoluteFilePath());
        return;
    }

    QFileInfo newFile(currentFileInfo.absoluteDir(),newName);

    if (newFile.exists())
    {
        QMessageBox::warning(this,tr("Rename error"),newName + tr(" already exists in ") + currentFileInfo.absolutePath());
        onFileRename();
        return;
    }

    if (!QFile::rename(currentFileInfo.absoluteFilePath(),newFile.absoluteFilePath()))
        QMessageBox::critical(this,tr("Rename critical error"),tr("Unknown error"));
    else
    {
        renameItem(item,newName);
        emit event(ProjectChanged);
    }
}


void ProjectManagerView::onAddFilter()
{
    if (!currentIndex().isValid())
        return;

    ProjectManagerModelItem* item = model->getItem(currentIndex());

    bool isAccepted = true;
    QString name = QInputDialog::getText(this,tr("Add new filter"),tr("Please type name of new filter in") + " " + item->getName(),
                                         QLineEdit::Normal, QString(),&isAccepted,Qt::Dialog);
    if (isAccepted && !name.isEmpty())
    {
        QString fullName = item->objectName() + SEPARATOR + name;
        if (item->parent() && item->parent()->findChild<ProjectManagerModelItem*>(fullName))
        {
            QMessageBox::warning(this,tr("Adding filter error"),item->parent()->getName() + " " + tr("already has") + " " + name);
            return onAddFilter();
        }

        QDir sourcesDir = item->getAbsoluteSourcesDir();
        if (!sourcesDir.exists())
            if (! QDir(item->getProjectItem()->getAbsoluteFileDir()).mkdir("sources"))
            {
                QMessageBox::critical(this, tr("Adding filter error"), tr("Can not create sources directory"));
                return;
            }

        QStringList localStorageDirsList =  fullName.split(SEPARATOR);
        localStorageDirsList.removeFirst();

        QString localStorageDirPath = localStorageDirsList.join(SEPARATOR);
        if (sourcesDir.mkpath(localStorageDirPath) || QDir(QFileInfo(sourcesDir.absolutePath(),localStorageDirPath).absolutePath()).exists())
        {

            model->insertItem(fullName,localStorageDirPath,ProjectManagerModelItem::Filter);
            emit event(ProjectChanged);

            if (!isExpanded(currentIndex()))
                expand(currentIndex());

            updateTreeView();
        } else
            QMessageBox::critical(this, tr("Adding filter error"), tr("Can not create filter directory"));

    }
}


void ProjectManagerView::onAddExistingFiles()
{
    if (!currentIndex().isValid())
        return;

    ProjectManagerModelItem* filterItem = model->getItem(currentIndex());
    QString filterDirectory;
    if (filterItem->getItemType()==ProjectManagerModelItem::Project)
        filterDirectory = filterItem->getAbsoluteSourcesDir().absolutePath();
    else
        filterDirectory = filterItem->getAbsoluteFileDir();

    QStringList files = QFileDialog::getOpenFileNames(this,tr("Add existing files"),
                                                     filterDirectory,
                                                     PluginManager::instance()->openFilters(),
                                                     0,QFileDialog::DontUseNativeDialog);
    QStringList errors;
    Q_FOREACH(QString filePath, files)
    {

        QString absoluteFilePath;
        if (!filePath.contains(filterItem->getAbsoluteSourcesDir().absolutePath()))
        {
            absoluteFilePath = QFileInfo(filterDirectory, QFileInfo(filePath).fileName()).absoluteFilePath();
            if (!QFile::copy(filePath, absoluteFilePath))
            {
                errors.append( tr("Can not copy file to sources: ") + filePath);
                continue;
            }
        }
        else
            absoluteFilePath = filePath;

        QString relativeFilePath = filterItem->getAbsoluteSourcesDir().relativeFilePath(absoluteFilePath);
        QString shownName = filterItem->getProjectItem()->objectName() + SEPARATOR + relativeFilePath;

        if (ProjectManagerModelItem* findedItem = model->getItemByFilePath( relativeFilePath, filterItem->getProjectItem()))
            errors.append( relativeFilePath + " " + tr("already exists in project as") + " " + findedItem->objectName());
        else
        {
            model->insertItem(shownName,relativeFilePath,ProjectManagerModelItem::File);
            emit event(ProjectChanged);
        }

        if (!isExpanded(currentIndex()))
            setExpanded(currentIndex(), true);
    }

    updateTreeView();

    if (!errors.isEmpty())
        QMessageBox::warning(this,tr("Add existing files error"),tr("Adding has some errors:") + "\n" + errors.join("\n"));
}


void ProjectManagerView::onAddFile()
{
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    QString selectedFilter;
    QString absoluteFilePath = QFileDialog::getSaveFileName(this,tr("Add file"),
                                                            item->getAbsoluteFileDir(),
                                                            PluginManager::instance()->openFilters(),
                                                            &selectedFilter,
                                                            QFileDialog::DontUseNativeDialog);

    if (absoluteFilePath.isEmpty())
        return;

    int pos = selectedFilter.indexOf("*.");
    Q_ASSERT_X(pos != -1, "ProjectManagerView::onAddFile", "Can't find begin of extension");
    pos++;
    int pos2 = selectedFilter.indexOf(")", pos);
    Q_ASSERT_X(pos != -1, "ProjectManagerView::onAddFile", "Can't find end of extension");

    QString ext = selectedFilter.mid(pos,pos2-pos).trimmed();
    if (!absoluteFilePath.contains(ext,Qt::CaseInsensitive))
        absoluteFilePath.append(ext);

    if (QFile::exists(absoluteFilePath))
        QFile::remove(absoluteFilePath);

    QString relativeFilePath = item->getAbsoluteSourcesDir().relativeFilePath(absoluteFilePath);
    QString shownName = item->getProjectItem()->objectName() + SEPARATOR + relativeFilePath;


    if (ProjectManagerModelItem* findedItem = model->getItemByFilePath( relativeFilePath, item->getProjectItem()))
        model->removeItem(findedItem);

    model->insertItem(shownName,relativeFilePath,ProjectManagerModelItem::File);

    if (!isExpanded(currentIndex()))
        setExpanded(currentIndex(), true);
    updateTreeView();

    emit event(ProjectChanged);
    emit openFile(absoluteFilePath);
}


void ProjectManagerView::onOpenFile()
{
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    if (item && item->getItemType() == ProjectManagerModelItem::File)
    {
        if (!QFile::exists(item->getAbsoluteFilePath()))
        {
            QString filter = item -> getAbsoluteFilePath().split(SEPARATOR).last();
            filter.append(" ("+filter+");;");
            filter.append(tr("Any file") + " (*." + item->getAbsoluteFilePath().split(".").last() + ")");
            QString existingFileForReplace = QFileDialog::getOpenFileName(this, tr("File not found"), item->getAbsoluteFileDir(),
                                                                          filter,0,QFileDialog::DontUseNativeDialog);
            if (existingFileForReplace.isNull())
                return;
            else
            {
                QString newFilePath;
                newFilePath = QDir(item->getProjectItem()->getAbsoluteSourcesDir()).relativeFilePath(existingFileForReplace);
                int reply = QMessageBox::question(this, tr("Replace file path"), tr("Replace file path to \"")+newFilePath+
                                                  tr("\" instead \"") + item->getFilePath() + "\"", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes)
                {
                    if (item -> getName() != QFileInfo(existingFileForReplace).fileName())
                    {
                        item->setObjectName(item->parent()->objectName() + SEPARATOR + QFileInfo(existingFileForReplace).fileName());
                        item->setName(QFileInfo(existingFileForReplace).fileName());
                    }
                    item->setFilePath(newFilePath);
                }
                else
                {
                    emit openFile(newFilePath);
                    return;
                }
            }
        }
        emit openFile(item->getAbsoluteFilePath());
    }

}


void ProjectManagerView::onShowInExplorer()
{
    QString pathIn;
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());
    if (item && !item->getFilePath().isEmpty())
        pathIn = item->getAbsoluteFilePath();
    else
        return;

    #ifdef defined(Q_OS_WIN)
        const QString explorer = "explorer";
        QString param;
        if (!QFileInfo(pathIn).isDir())
            param = QLatin1String("/select,");
        param += QDir::toNativeSeparators(pathIn);
        QProcess::startDetached(explorer, QStringList(param));
    #elif defined(Q_OS_MAC)

        QStringList scriptArgs;
        scriptArgs << QLatin1String("-e")
                   << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
                                         .arg(pathIn);
        QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
        scriptArgs.clear();
        scriptArgs << QLatin1String("-e")
                   << QLatin1String("tell application \"Finder\" to activate");
        QProcess::execute("/usr/bin/osascript", scriptArgs);
    #endif

// Todo: opening file in filemanager for Linux
/*#else
        const QFileInfo fileInfo(pathIn);
        const QString folder = fileInfo.absoluteFilePath();
        const QString app = Utils::UnixUtils::fileBrowser(Core::ICore::instance()->settings());
        QProcess browserProc;
        const QString browserArgs = Utils::UnixUtils::substituteFileBrowserParameters(app, folder);
        if (debug)
            qDebug() <<  browserArgs;
        bool success = browserProc.startDetached(browserArgs);
        const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
        success = success && error.isEmpty();
        if (!success)
            showGraphicalShellError(this, app, error);
    #endif
*/
}


void ProjectManagerView::onPropertiesShow()
{
    if (!currentIndex().isValid())
        return;
    if (ProjectManagerModelItem* item = model->getItem(currentIndex()))
    {
        QStringList properties;
        properties << tr("Item:") + "\t\t" + item->objectName();
        properties << tr("File:") + "\t\t" + item->getAbsoluteFilePath();
        properties << tr("Size:") + "\t\t" + QString::number(QFileInfo(item->getAbsoluteFilePath()).size()) << "bytes";
        QMessageBox::information(this,tr("Properties"),properties.join("\n"));
    }
}
