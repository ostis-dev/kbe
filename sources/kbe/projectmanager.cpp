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
    setWidget(treeView);
}

ProjectManagerDockWidget::~ProjectManagerDockWidget()
{
    Q_ASSERT(mInstance != 0);
    mInstance = 0;
}

ProjectManagerDockWidget* ProjectManagerDockWidget::instance()
{
    if (mInstance)
        return mInstance;
    mInstance = new ProjectManagerDockWidget();
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
                menu -> addAction(QIcon(), tr("Save project"), this, SLOT(onProjectSave()));
                menu -> addAction(QIcon(), tr("Close Project"),this,SLOT(onProjectClose()));

                menu -> addSeparator();
            }
        case ProjectManagerModelItem::Filter:
            {
                menu -> addAction(QIcon(), tr("Add File"),this,SLOT(onAddFile()));
                menu -> addAction(QIcon(), tr("Add Existing Files"), this, SLOT(onAddExistingFiles()));
                menu -> addAction(QIcon(), tr("Add Filter"), this, SLOT(onAddFilter()));

                menu -> addSeparator();

                menu -> addAction(QIcon(), tr("Rename"), this, SLOT(onRename()));
                QMenu* delMenu = menu -> addMenu(QIcon(), tr("Delete"));
                    delMenu -> addAction(QIcon(), tr("Delete From Project"),this,SLOT(onRemove()));
                    delMenu -> addAction(QIcon(), tr("Delete Permanently"),this,SLOT(onRemovePermanently()));

                menu -> addSeparator();

                menu -> addAction(QIcon(),tr("Expand All"),this,SLOT(expandAll()));
                menu -> addAction(QIcon(),tr("Collapse All"),this,SLOT(collapseAll()));
                break;
            }
        case ProjectManagerModelItem::File:
            {
                menu -> setDefaultAction(menu -> addAction(QIcon(), tr("Open file"),this,SLOT(onOpenFile())));

#ifndef Q_OS_LINUX
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
        menu -> addAction(QIcon(),tr("Expand All"),this,SLOT(expandAll()));
        menu -> addAction(QIcon(),tr("Collapse All"),this,SLOT(collapseAll()));

        menu -> addSeparator();

        menu -> addAction(QIcon(),tr("Close All Projects"),this,SLOT(onAllProjectsClose()));
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
            QString existingFileForReplace = QFileDialog::getOpenFileName(this, tr("File not found"),
                                                                          item->getAbsoluteFileDir(),filter);
            if (existingFileForReplace.isNull())
                return;
            else
            {
                QString newFilePath = QDir(item->getProjectItem()->getAbsoluteFileDir()).relativeFilePath(existingFileForReplace);
                int reply = QMessageBox::question(this, tr("Replace file path"), tr("Replace file path to \"")+newFilePath+
                                                  tr("\" instead \"") + item->getFilePath() + "\"", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes)
                    item->setFilePath(newFilePath);
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
    bool isAccepted = true;
    QString name = QInputDialog::getText(this,tr("Add new project"),tr("Please type name of new project"),
                                         QLineEdit::Normal, QString(),&isAccepted,Qt::Dialog);
    if (isAccepted && !name.isEmpty())
    {
        if (model->getRootItem()->findChild<ProjectManagerModelItem*>(name))
        {
            QMessageBox::warning(this,tr("Adding project error"),name+" "+tr("already exists"));
            return onProjectNew();
        }
        ProjectManagerModelItem* project = new ProjectManagerModelItem(name,"",ProjectManagerModelItem::Project,model->getRootItem());
        model->insertProject(project);
    }
}


void ProjectManagerView::onProjectClose()
{
    //todo:
    // check modified
    if (!currentIndex().isValid())
        return;
    model->removeItem(model->getItem(currentIndex()));
}


void ProjectManagerView::onAllProjectsSave()
{
    if (ProjectManagerModelItem* rootItem = model->getRootItem())
        for (int i=0; i< rootItem->childCount(); i++)
        {
            QString fileName = rootItem->child(0)->getAbsoluteFilePath();

            if (rootItem->child(i)->getFilePath().isEmpty() || !QFile::exists(fileName))
            {
                fileName = QFileDialog::getSaveFileName(this, tr("Project file not found"),
                                                        QDir::current().absolutePath(),rootItem->child(i)->getName()+"(*.kbpro)");
                if (fileName.isEmpty())
                    continue;

                rootItem->child(i)->setFilePath(fileName);
            }
            model->saveProject(rootItem->child(i),fileName);
        }
}



void ProjectManagerView::onAllProjectsClose()
{
    if (ProjectManagerModelItem* rootItem = model->getRootItem())
        while (rootItem->childCount())
            model->removeItem(rootItem->child(0));
}

void ProjectManagerView::onProjectOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose project file"),
                                                    QDir::current().absolutePath(),tr("KBE project file")+("(*.kbpro)"));
    if (!fileName.isEmpty())
        model->loadProject(fileName);
}

void ProjectManagerView::onProjectSave()
{
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    QString fileName = item->getAbsoluteFilePath();

    if (item->getFilePath().isEmpty() || !QFile::exists(fileName))
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Project file not found"),
                                                QDir::current().absolutePath(),item->getName()+("(*.kbpro)"));
        if (fileName.isEmpty())
            return;

        item->setFilePath(fileName);
    }

    model->saveProject(item,item->getAbsoluteFilePath());
}

void ProjectManagerView::onRemove()
{
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    if (item && item->getItemType() != ProjectManagerModelItem::Project)
        model->removeItem(item);
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
        renameItem(item,newName);
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
        model->insertItem(fullName,QString(),ProjectManagerModelItem::Filter);

        if (!isExpanded(currentIndex()))
            setExpanded(currentIndex(), true);
    }
}


void ProjectManagerView::onAddExistingFiles()
{
    if (!currentIndex().isValid())
        return;

    ProjectManagerModelItem* filterItem = model->getItem(currentIndex());

    QStringList files = QFileDialog::getOpenFileNames(this,tr("Add existing files"),
                                                     filterItem->getAbsoluteFileDir(),
                                                     PluginManager::instance()->openFilters());
    QStringList errors;
    Q_FOREACH(QString filePath, files)
    {
        QString shownName = filterItem->objectName() + SEPARATOR + QFileInfo(filePath).fileName();
        QString relativeFilePath = QDir(filterItem->getProjectItem()->getAbsoluteFileDir()).relativeFilePath(filePath);

        if (ProjectManagerModelItem* findedItem = model->getItemByFilePath( relativeFilePath, filterItem->getProjectItem()))
            errors.append( relativeFilePath + " " + tr("already exists in project as") + " " + findedItem->objectName());
        else
            model->insertItem(shownName,relativeFilePath,ProjectManagerModelItem::File);

        if (!isExpanded(currentIndex()))
            setExpanded(currentIndex(), true);
    }

    if (!errors.isEmpty())
        QMessageBox::warning(this,tr("Add existing files error"),tr("Adding has some errors:") + "\n" + errors.join("\n"));
}


void ProjectManagerView::onAddFile()
{
    if (!currentIndex().isValid())
        return;
    ProjectManagerModelItem* item = model->getItem(currentIndex());

    QString absoluteFilePath;

    absoluteFilePath = QFileDialog::getSaveFileName(this,tr("Add file"),
                                                     item->getAbsoluteFileDir(),
                                                    PluginManager::instance()->openFilters());

    if (absoluteFilePath.isEmpty())
        return;

    QString shownName = item->objectName() + SEPARATOR + QFileInfo(absoluteFilePath).fileName();
    QString relativeFilePath = QDir(item->getAbsoluteFileDir()).relativeFilePath(absoluteFilePath);

    if (ProjectManagerModelItem* findedItem = model->getItemByFilePath( relativeFilePath, item->getProjectItem()))
        model->removeItem(findedItem);

    model->insertItem(shownName,relativeFilePath,ProjectManagerModelItem::File);

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
            filter.append(tr("Any file") + "(*." + item->getAbsoluteFilePath().split(".").last() + ")");
            QString existingFileForReplace = QFileDialog::getOpenFileName(this, tr("File not found"),
                                                                          item->getAbsoluteFileDir(),filter);
            if (existingFileForReplace.isNull())
                return;
            else
            {
                QString newFilePath = QDir(item->getProjectItem()->getAbsoluteFileDir()).relativeFilePath(existingFileForReplace);
                int reply = QMessageBox::question(this, tr("Replace file path"), tr("Replace file path to") + " \"" + newFilePath +
                                                  "\""  + tr("instead") + " \"" + item->getFilePath() + "\"", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes)
                    item->setFilePath(newFilePath);
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

    #if defined(Q_OS_WIN)
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
    #else

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
