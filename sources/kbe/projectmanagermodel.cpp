#include "projectmanagermodel.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <QFile>
#include <QFileInfo>
#include <QDir>

#include <QModelIndex>
#include <QUrl>
#include <QMimeData>

ProjectManagerModel::ProjectManagerModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Title";

    rootItem = new ProjectManagerModelItem(rootData);
}


ProjectManagerModel::~ProjectManagerModel()
{
    delete rootItem;
}


int ProjectManagerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ProjectManagerModelItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}


QVariant ProjectManagerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ProjectManagerModelItem *item = static_cast<ProjectManagerModelItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::DropActions ProjectManagerModel::supportedDropActions() const
{
    return Qt::MoveAction;
}


QStringList ProjectManagerModel::mimeTypes() const
{
    QStringList types;
    types << "application/kbe.project.item.list";
    return types;
}


QMimeData *ProjectManagerModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    QList<QUrl> urlList;

    Q_FOREACH (QModelIndex index, indexes) {
        if (index.isValid() && !index.column())
            if (ProjectManagerModelItem* item = getItem(index))
            {
                QString objectName = item->objectName();
                QString shownName = item->getName();
                QString filePath = item->getAbsoluteFilePath();
                ProjectManagerModelItem::ItemType type = item->getItemType();
                stream << objectName << shownName << filePath << type;
                urlList.append(QUrl::fromLocalFile(filePath));
            }
    }


    mimeData->setData("application/kbe.project.item.list", encodedData);
    mimeData->setUrls(urlList);

    return mimeData;
}


bool ProjectManagerModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("application/kbe.project.item.list") || !parent.isValid())
        return false;

    if (ProjectManagerModelItem* item = getItem(parent))
    {
        QByteArray encodedData = data->data("application/kbe.project.item.list");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QList< QPair<ProjectManagerModelItem*,QString> > newItems;

        while (!stream.atEnd())
        {
            QString lastObjectName;
            QString shownName;
            QString absoluteFilePath;
            int n_itemType;
            ProjectManagerModelItem::ItemType itemType;

            stream >> lastObjectName;
            stream >> shownName;
            stream >> absoluteFilePath;
            stream >> n_itemType;
            itemType = static_cast<ProjectManagerModelItem::ItemType>(n_itemType);
            ProjectManagerModelItem* newItem = new ProjectManagerModelItem(shownName,absoluteFilePath,itemType);
            QString lastPath(lastObjectName);

            newItems << QPair<ProjectManagerModelItem*,QString>(newItem,lastPath);
        }

        for (int i=0; i<newItems.count(); i++)
        {

            ProjectManagerModelItem* newItem = newItems.at(i).first;
            QString lastName = newItems.at(i).second;

            QString shownName = item->objectName() + "/" + newItem->getName();
            QString filePath = QDir(item->getProjectItem()->getAbsoluteFileDir()).relativeFilePath(newItem->getFilePath());

            if (shownName.split("/").first()!=lastName.split("/").first())
                return false;

            if (action == Qt::MoveAction)
                removeItem(lastName);

            this->insertItem(shownName,filePath,newItem->getItemType());
        }

        return true;
    }

    return false;
}


void ProjectManagerModel::loadProject(QString filePath)
{
    if (filePath.isEmpty())
        return;
    QFile proFile(QFileInfo(filePath).absoluteFilePath());
    ProjectManagerModelItem* projectItem = NULL;
    if (proFile.open(QFile::ReadOnly))
    {
        QXmlStreamReader rStream(&proFile);

        while (!rStream.atEnd() && !rStream.hasError())
        {
            rStream.readNextStartElement();
            if (rStream.name()=="KBEProject" && rStream.isStartElement())
            {
                if (projectItem)
                {
                    removeItem(projectItem);
                    break;
                }
                QString shownName = rStream.attributes().value("name").toString();
                QString fileName = proFile.fileName();
                if (rootItem->findChild<ProjectManagerModelItem*>(shownName))
                    return;
                projectItem = new ProjectManagerModelItem(shownName, fileName,
                                                              ProjectManagerModelItem::Project, rootItem);
                projectItem->setObjectName(shownName);
                insertProject(projectItem);
            }

            if (rStream.name()=="file" && rStream.isStartElement())
            {
                QString fileName = rStream.attributes().value("path").toString();
                QString filter = rStream.attributes().value("filter").toString();
                QStringList neededPath = filter.split("/");
                QString newObjectName = projectItem->objectName()+"/"+neededPath.join("/") + "/"+fileName;
                addChild(newObjectName, fileName, ProjectManagerModelItem::File, rootItem);
            }
        }
        proFile.close();
    }


}


void ProjectManagerModel::saveProject(ProjectManagerModelItem *project, QString filePath)
{
    if (!project || filePath.isEmpty())
        return;
    QFile proFile(filePath);
    if (proFile.open(QFile::WriteOnly))
    {
        QXmlStreamWriter wStream(&proFile);
        wStream.setAutoFormatting(true);
        wStream.setAutoFormattingIndent(4);
        wStream.writeStartDocument();

        wStream.writeStartElement("KBEProject");
            wStream.writeAttribute("name", project->getName());
            saveChilds(project,wStream);
        wStream.writeEndElement();

        wStream.writeEndDocument();

        proFile.close();
    }
}

void ProjectManagerModel::saveChilds(ProjectManagerModelItem *item, QXmlStreamWriter &wStream)
{
    if (!item)
        return;
    for (int i=0; i<item->childCount(); i++)
        saveChilds(item->child(i),wStream);
    if (item->getItemType() == ProjectManagerModelItem::Project ||
            item->getItemType() == ProjectManagerModelItem::Filter)
        return;
    wStream.writeStartElement("file");
        QStringList filterPath = item->objectName().split("/");
        filterPath.pop_back();
        filterPath.pop_front();
        if (filterPath.count())
            wStream.writeAttribute("filter",filterPath.join("/"));
        wStream.writeAttribute("path",item->getFilePath());
    wStream.writeEndElement();
}

void ProjectManagerModel::insertItem(const QString shownName, const QString filePath, ProjectManagerModelItem::ItemType type)
{
    QStringList path = shownName.split('/');
    path.pop_back();
    ProjectManagerModelItem* neededFilter = getPath(path,rootItem);
    if (!neededFilter)
        return;
    beginInsertRows(createIndex(0,0,neededFilter),
                    neededFilter->childCount(),
                    neededFilter->childCount()+1);
        addChild(shownName,filePath,type,rootItem);
    endInsertRows();
}


void ProjectManagerModel::insertProject(ProjectManagerModelItem *item)
{
    beginInsertRows(QModelIndex(),
                    rootItem->childCount(),
                    rootItem->childCount()+1);

    rootItem -> appendChild(item);

    endInsertRows();
}


void ProjectManagerModel::removeItem(ProjectManagerModelItem *item)
{
    if (item==NULL)
        return;
    QModelIndex index = createIndex(0,0,item);
     if (index.isValid())
     {
         if (item->childCount())
            beginRemoveRows(index, 0, item->childCount()-1);
         else
            beginRemoveRows(index,0,0);

         item->parent()->removeChild(item);
         endRemoveRows();
     }
}


void ProjectManagerModel::removeItem(QString itemObjectName)
{
    if (itemObjectName.isNull() || itemObjectName.isEmpty())
        return;
    ProjectManagerModelItem* item = getRootItem()->findChild<ProjectManagerModelItem*>(itemObjectName);
    if (item==NULL)
        return;
    QModelIndex index = createIndex(0,0,item);
     if (index.isValid())
     {
         if (item->childCount())
            beginRemoveRows(index, 0, item->childCount()-1);
         else
            beginRemoveRows(index,0,0);

         item->parent()->removeChild(item);
         endRemoveRows();
     }
}


ProjectManagerModelItem* ProjectManagerModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        ProjectManagerModelItem* item = static_cast<ProjectManagerModelItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return NULL;
}


Qt::ItemFlags ProjectManagerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if (ProjectManagerModelItem* item = getItem(index))
    {
        if (item->getItemType()== ProjectManagerModelItem::Project)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled;

        if (item->getItemType()== ProjectManagerModelItem::Filter)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}


QVariant ProjectManagerModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex ProjectManagerModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ProjectManagerModelItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = getItem(parent);

    ProjectManagerModelItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


QModelIndex ProjectManagerModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ProjectManagerModelItem *childItem = getItem(index);
    ProjectManagerModelItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int ProjectManagerModel::rowCount(const QModelIndex &parent) const
{
    ProjectManagerModelItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = getItem(parent);

    return parentItem->childCount();
}

ProjectManagerModelItem* ProjectManagerModel::getRootItem()
{
    return rootItem;
}

ProjectManagerModelItem* ProjectManagerModel::getItemByFilePath(QString filePath, ProjectManagerModelItem *parent)
{
    if (!parent)
        return NULL;
    for (int i=0; i<parent->childCount(); i++)
    {
        if (filePath == parent->child(i)->getFilePath())
            return parent->child(i);
        if (ProjectManagerModelItem* item = getItemByFilePath(filePath,parent->child(i)))
            return item;
    }
    return NULL;
}


ProjectManagerModelItem* ProjectManagerModel::addChild(const QString shownName, const QString filePath,
                                                               ProjectManagerModelItem::ItemType type, ProjectManagerModelItem* rootItem)
{
    ProjectManagerModelItem* item  = NULL;
    QStringList path = shownName.split('/');
    QString name = path.last();

    if (type == ProjectManagerModelItem::Project)
    {
        item = new ProjectManagerModelItem(name,filePath,type,rootItem);
        item -> setObjectName(shownName);
        rootItem -> appendChild(item);
        return item;
    }

    if (getPath(QStringList(shownName.split("/").first()),rootItem) -> findChild<ProjectManagerModelItem*>(shownName))
        return NULL;
    path.pop_back();
    if (ProjectManagerModelItem* neededFilter = getPath(path,rootItem))
    {
        item = new ProjectManagerModelItem(name,filePath,type,neededFilter);
        item -> setObjectName(shownName);
        neededFilter -> appendChild(item);
    }
    return item;
}


ProjectManagerModelItem* ProjectManagerModel::getPath(QStringList path, ProjectManagerModelItem *parent)
{
    if (path.isEmpty() || path.first().isEmpty())
        return parent;
    QString neededItemObjectName = path.first();
    if (!parent->objectName().isEmpty())
        neededItemObjectName = parent->objectName()+"/"+neededItemObjectName;
    if (ProjectManagerModelItem* item = parent -> findChild<ProjectManagerModelItem*>(neededItemObjectName))
    {
            path.pop_front();
            return getPath(path, item);
    }
    else
    {
        ProjectManagerModelItem* newItem = new ProjectManagerModelItem(path.first(),QString(),ProjectManagerModelItem::Filter,parent);
        newItem -> setObjectName(neededItemObjectName);
        parent -> appendChild(newItem);
        path.pop_front();
        return getPath(path,newItem);
    }
    return NULL;
}

// Model Item

ProjectManagerModelItem::ProjectManagerModelItem(const QList<QVariant> &data, ProjectManagerModelItem *parent):
    QObject(parent), isModified(false)
{
    parentItem = parent;

    if (data.count()==3)
    {
        shownName = data.at(0).toString().split("/").last();
        setObjectName(data.at(0).toString());
        filePath = data.at(1).toString();
        type = static_cast<ItemType>(data.at(2).toInt());
    }
}

ProjectManagerModelItem::ProjectManagerModelItem(QString shownName, QString filePath, ItemType type, ProjectManagerModelItem *parent):
    QObject(parent), isModified(false)
{
    parentItem = parent;

    this -> shownName = shownName;
    this -> setObjectName(shownName);
    this -> filePath = filePath;
    this -> type = type;
}

ProjectManagerModelItem::~ProjectManagerModelItem()
{
    qDeleteAll(childItems);
}


void ProjectManagerModelItem::appendChild(ProjectManagerModelItem *item)
{
    childItems.append(item);
}

void ProjectManagerModelItem::removeChild(ProjectManagerModelItem *child)
{
    if (child && child->parent())
        childItems.removeOne(child);
    for (int i=0; i< child -> childCount(); i++)
        child->removeChild(child->child(i));
    child->setObjectName("");
}

ProjectManagerModelItem *ProjectManagerModelItem::child(int row)
{
    return childItems.value(row);
}


int ProjectManagerModelItem::childCount() const
{
    return childItems.count();
}


int ProjectManagerModelItem::columnCount() const
{
    return 1;
}


QVariant ProjectManagerModelItem::data(int column) const
{
    if (objectName().isNull())
        return tr("Projects");

    return shownName;
}


ProjectManagerModelItem *ProjectManagerModelItem::parent()
{
    return parentItem;
}


ProjectManagerModelItem* ProjectManagerModelItem::getProjectItem()
{
    if (type == Project)
        return this;
    ProjectManagerModelItem* projectItem = this->parent();
    while (projectItem)
    {
        if (projectItem -> type == ProjectManagerModelItem::Project)
            return projectItem;
        projectItem = projectItem->parent();
    }
    return projectItem;
}


void ProjectManagerModelItem::setFilePath(QString filePath)
{
    this->filePath = filePath;
}


QString ProjectManagerModelItem::getAbsoluteFilePath()
{
    if (type == Project)
        return QFileInfo(filePath).absoluteFilePath();
    if (ProjectManagerModelItem* projectItem = this -> getProjectItem())
    {
        QFileInfo projectFileInfo(projectItem->getFilePath());
        QDir projectDir = projectFileInfo.absoluteDir();
        QFileInfo currentItemFileInfo(projectDir,filePath);
        return currentItemFileInfo.absoluteFilePath();
    }
    return QString();
}


QString ProjectManagerModelItem::getAbsoluteFileDir()
{
    return QFileInfo(getAbsoluteFilePath()).absoluteDir().absolutePath();
}


int ProjectManagerModelItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<ProjectManagerModelItem*>(this));

    return 1;
}

