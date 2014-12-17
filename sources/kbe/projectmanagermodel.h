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

#ifndef PROJECTMANAGERMODEL_H
#define PROJECTMANAGERMODEL_H

#include <QStringList>
#include <QList>
#include <QVariant>

#include <QAbstractItemModel>

#define SEPARATOR       "/"

class QXmlStreamWriter;
class QModelIndex;
class QDir;

class ProjectManagerModelItem: public QObject
{
    Q_OBJECT

public:
    /* Types of item */
    enum eItemType
    {
        Unknown,
        Project,
        Filter,
        File
    };

    Q_ENUMS(eItemType)

    ProjectManagerModelItem(QObject* parent=0);
    ProjectManagerModelItem(QString shownName, QString filePath, eItemType type, ProjectManagerModelItem *parent = 0);
    ~ProjectManagerModelItem();

    /*! Appends child in childItems list
     * @param child Item which will be appeded
     */
    void appendChild(ProjectManagerModelItem *child);

    /*! Removes child from childItems list
     * @param child Item which will be removed
     */
    void removeChild(ProjectManagerModelItem* child);

    ProjectManagerModelItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

    //! Returns item's parent
    ProjectManagerModelItem* parent();

    //! Returns project item which contains this item
    ProjectManagerModelItem* getProjectItem();

    //! Returns absolute file path of current item
    QString getAbsoluteFilePath();

    //! Returns absolute path to directory which contains current item
    QString getAbsoluteFileDir();

    //! Returns absolute directory to directory which contains sources of project
    QDir getAbsoluteSourcesDir();

    eItemType getItemType() const { return mItemType; }
    QString getFilePath() const { return mFilePath; }
    void setFilePath(QString filePath);
    QString getName() const { return mShownName.toString(); }
    void setName(QString name) { mShownName = name; }
    bool isModified() const { return mIsModified; }
    void setModified(bool val) { mIsModified = val; }

private:
    //! Flag which indicates that item is modified
    bool mIsModified;

    //! Pointer to parent
    ProjectManagerModelItem *parentItem;
    //! List of item's child
    QList<ProjectManagerModelItem*> childItems;

    //Object name contains full path to item and shown name

    //! Name which will be shown in view
    QVariant mShownName;
    //! Relative(for files) or Absolute(for projects) path
    QString mFilePath;
    //! Type of item
    eItemType mItemType;
};



class ProjectManagerModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ProjectManagerModel(QObject *parent);
    ~ProjectManagerModel();

    /*! Adds child to model
     * @param shownName Item's name which contain all filters and project name. Finally will be shown name without adds
     * @param filePath Relative(for files) or Absolute(for projects) path to real file
     * @param type Item's type
     * @param rootItem Model's root item
     */
    ProjectManagerModelItem* addChild(const QString shownName, const QString filePath, ProjectManagerModelItem::eItemType type, ProjectManagerModelItem* rootItem);

    /*! Removes item from model
     * @param item which will be removed from model
     */
    void removeItem(ProjectManagerModelItem* item);

    /*! Removes item from model by objectName
     * @param itemObjectName Item's objectName
     */
    void removeItem(QString itemObjectName);

    /*! Inserts item to model
     * @param shownName Item's name which contain all filters and project name. Finally will be shown name without adds
     * @param filePath Relative(for files) or Absolute(for projects) path to real file
     * @param type Item's type
     */
    void insertItem(const QString shownName, const QString filePath, ProjectManagerModelItem::eItemType type);

    /*! Inserts project item to model
     * @param item Project item which will be inserted in model
     */
    void insertProject(ProjectManagerModelItem* item);


    //! Returns model's root item
    ProjectManagerModelItem* getRootItem();

    /*! Returns item of parent by filePath
     * @param filePath Path to item's file on local storage
     * @param parent item which seek to item
     */
    ProjectManagerModelItem* getItemByFilePath(QString filePath, ProjectManagerModelItem* parent);


    /*! Returns QModelIndex of item's parent
     * @param item which parent is needed
     */
    QModelIndex getParentModelIndex(ProjectManagerModelItem* item);


    /*! Loads project to model by filePath
     * @param filePath Path to project file
     */
    void loadProject(QString filePath);

    /*! Recoursivly imports item with childs to project
    * @param item Item to import
    * @param directoryPath current directory path
     */
    void importChilds(ProjectManagerModelItem *item, QString directoryPath);

    /*! Saves project from model
    * @param project Project which will be saved
    * @param filePath Path to file in which will be saved project
     */
    void saveProject(ProjectManagerModelItem* project,QString filePath=0);

    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data,
        Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;

    //! Converts index to PrijectManagerModelItem
    ProjectManagerModelItem* getItem(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QModelIndexList getPersistentIndexList() const;

private:

    /*! Recoursivly saves item with childs to stream
    * @param item Item which be saved
    * @param wStream Stream in which item will be saved
     */
    void saveChilds(ProjectManagerModelItem* item, QXmlStreamWriter& wStream);


    /*! Creates path(filters) in model and returns pointer for tale
    * @param path Path which will be created in model
    * @param parent Item which will be used to find or create next filter
    * \return Pointer to last created item (path's tale)
     */
    ProjectManagerModelItem* getPath(QStringList path, ProjectManagerModelItem *parent);

private:
    //! Model's root item
    ProjectManagerModelItem *mRootItem;

};

#endif // PROJECTMANAGERTREEVIEW_H
