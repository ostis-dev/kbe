/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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

