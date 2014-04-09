#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QDockWidget>
#include <QTreeView>

#include "projectmanagermodel.h"

class QMouseEvent;
class ProjectManagerView;
class ProjectManagerModel;
class ProjectManagerModelItem;

class ProjectManagerDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ProjectManagerDockWidget(QWidget *parent = 0);
    virtual ~ProjectManagerDockWidget();

    static ProjectManagerDockWidget* instance();

    ProjectManagerView* getTreeView() { return treeView; }
private:
    static ProjectManagerDockWidget* mInstance;

    //! Content of this widget
    ProjectManagerView *treeView;
};

class ProjectManagerView : public QTreeView
{
    Q_OBJECT
public:
    explicit ProjectManagerView(QWidget *parent = 0);

public slots:
    void onContextMenuRequested(QPoint);
    void onProjectNew();
    void onProjectOpen();
    void onProjectSave();
    void onProjectClose();
    void onAllProjectsSave();
    bool onAllProjectsClose();
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
    void mousePressEvent(QMouseEvent*);

    //! Opens file if double clicked item's type is file
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    ProjectManagerModel* model;
};

#endif // PROJECTMANAGER_H
