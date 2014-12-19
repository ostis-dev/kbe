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

#ifndef PROJECTMANAGERVIEW_H
#define PROJECTMANAGERVIEW_H

#include <QTreeView>

class QMouseEvent;
class ProjectManagerModel;
class ProjectManagerModelItem;


class ProjectManagerView : public QTreeView
{
    Q_OBJECT

public:
    enum eProjectManagerEvent
    {
        DefaultEvent,
        ProjectCreated,
        ProjectOpened,
        ProjectImported,
        ProjectSaved,
        ProjectClosed,
        ProjectChanged
    };

    Q_ENUMS(eProjectManagerEvent)

    explicit ProjectManagerView(QWidget *parent = 0);

public slots:
    void onContextMenuRequested(QPoint);
    void onProjectNew();
    void onProjectOpen();
    void onProjectImport();
    void onProjectSave();
    bool onProjectClose();
    void onRemove();
    void onRemovePermanently();
    QString onRename();
    void onFileRename();
    void onAddFilter();
    void onAddExistingFiles();
    void onAddFile();
    void onOpenFile();
    void onShowInExplorer();
    void onPropertiesShow();

signals:
    /*! This signal will send when ProjectManager requests opening some file.
     * @param Filename
     */
    void openFile(QString);

    /*! This signal will send when ProjectManager modified(or managed) project.
     * @param Filename
     */
    void event(ProjectManagerView::eProjectManagerEvent);

private:
    /*! Changes item name
     * @param item Item which name will be changed
     * @param newName new name for item
     */
    void renameItem(ProjectManagerModelItem* item, QString newName);

    /*! Removes item and his childs from localstorage and view
     * @param item Item which will be removed
     */
    void permanentRemoveTree(ProjectManagerModelItem* item);

    /*! Creates context menu which appears for item
     * @param item Item for which menu will be appear
     */
    void createContextMenu(ProjectManagerModelItem* item);

    //! QTreeView::mousePressEvent with feature that item's focus will be removed if click occured on empty area
    void mousePressEvent(QMouseEvent *event);

    //! Opens file if double clicked item's type is file
    void mouseDoubleClickEvent(QMouseEvent *event);

    void updateTreeView();

private:
    ProjectManagerModel* mModel;
};

#endif // PROJECTMANAGER_H
