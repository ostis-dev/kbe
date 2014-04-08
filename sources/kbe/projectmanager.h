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

    ProjectManagerView *treeView;

};

class ProjectManagerView : public QTreeView
{
    Q_OBJECT
public:
    explicit ProjectManagerView(QWidget *parent = 0);

private slots:
    void onContextMenuRequested(QPoint);
    void onProjectNew();
    void onProjectOpen();
    void onProjectSave();
    void onProjectClose();
    void onAllProjectsSave();
    void onAllProjectsClose();
    void onRemoveFile();
    void onRemovePermanently();
    QString onRename();
    void onFileRename();
    void onAddFilter();
    void onAddExistingFiles();
    void onAddFile();
    void onOpenFile();
    void onShowInExplorer();


signals:
    void openFile(QString); // filename

private:
    void renameItem(ProjectManagerModelItem* item, QString newName);
    void createContextMenu(ProjectManagerModelItem* item);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    ProjectManagerModel* model;

};

#endif // PROJECTMANAGER_H