#ifndef PROJECTMANAGERTREEVIEW_H
#define PROJECTMANAGERTREEVIEW_H

#include <QStringList>
#include <QList>
#include <QVariant>

#include <QAbstractItemModel>

class QXmlStreamWriter;
class QModelIndex;





class ProjectManagerModelItem: public QObject
{
    Q_OBJECT

public:
    enum ItemType {
        Unknown,
        Project,
        Filter,
        File
    };

    Q_ENUMS(ItemType);

    ProjectManagerModelItem(const QList<QVariant> &data, ProjectManagerModelItem *parent = 0);
    ProjectManagerModelItem(QString shownName, QString filePath, ItemType type, ProjectManagerModelItem *parent = 0);
    ~ProjectManagerModelItem();

    void appendChild(ProjectManagerModelItem *child);
    void removeChild(ProjectManagerModelItem* child);

    ProjectManagerModelItem* child(int row);
    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    int row() const;
    ProjectManagerModelItem *parent();

    ProjectManagerModelItem* getProjectItem();

    ItemType getItemType() const { return type; }
    QString getFilePath() const { return filePath; }
    void setFilePath(QString filePath);
    QString getAbsoluteFilePath();
    QString getAbsoluteFileDir();
    QString getName() const { return shownName.toString(); }
    void setName(QString name) { shownName = name; }

private:
    bool isModified;
    QList<ProjectManagerModelItem*> childItems;
    QVariant shownName;
    QString filePath;
    ProjectManagerModelItem *parentItem;
    ItemType type;
};



class ProjectManagerModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ProjectManagerModel(QObject *parent);
    ~ProjectManagerModel();

    ProjectManagerModelItem* addChild(const QString shownName, const QString filePath, ProjectManagerModelItem::ItemType type, ProjectManagerModelItem* rootItem);
    void removeItem(ProjectManagerModelItem* item);
    void removeItem(QString itemObjectName);
    void insertItem(const QString shownName, const QString filePath, ProjectManagerModelItem::ItemType type);
    void insertProject(ProjectManagerModelItem* item);

    ProjectManagerModelItem* getRootItem();
    ProjectManagerModelItem* getItemByFilePath(QString filePath, ProjectManagerModelItem* parent);

    void loadProject(QString filePath);
    void saveProject(ProjectManagerModelItem* project,QString filePath=0);

    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data,
        Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;
    QVariant data(const QModelIndex &index, int role) const;
    ProjectManagerModelItem* getItem(const QModelIndex &index) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;



private:
    void saveChilds(ProjectManagerModelItem* item, QXmlStreamWriter& wStream);
    ProjectManagerModelItem* getPath(QStringList path, ProjectManagerModelItem *parent);
    ProjectManagerModelItem *rootItem;

};

#endif // PROJECTMANAGERTREEVIEW_H
