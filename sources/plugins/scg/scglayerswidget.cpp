#include "scglayerswidget.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

#include <QMenu>
#include <QAction>

#include "scgscene.h"

SCgLayersWidget::SCgLayersWidget(SCgScene* scene, QWidget* parent)
    : QWidget(parent),
      mScene(scene)
{
    mToolBar = new QToolBar(this);
    mToolBar->addAction(QIcon(":/media/icons/add.png"), "Add layout", this, SLOT(createLayer()));
    mToolBar->addAction(QIcon(":/media/icons/remove.png"), "Delete layout", this, SLOT(deleteLayer()));
    mToolBar->addAction(QIcon(":/media/icons/enable.png"), "Show all", this, SLOT(showAll()));
    mToolBar->addAction(QIcon(":/media/icons/disable.png"), "Hide all", this, SLOT(hideAll()));

    mLayerListView = new QListWidget(this);
    mLayerListView->setSortingEnabled(true);
    mLayerListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mLayerListView->setContextMenuPolicy(Qt::CustomContextMenu);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mToolBar);
    layout->addWidget(mLayerListView);
    setLayout(layout);

    connect(mScene, SIGNAL(layerAdded(int,QString)), SLOT(addLayer(int,QString)));
    connect(mScene, SIGNAL(layerRemoved(int)), SLOT(removeLayer(int)));
    connect(mScene, SIGNAL(currentLayerChanged(int)), this, SLOT(selectLayer(int)));

    connect(mLayerListView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customContextMenu(QPoint)));
    connect(mLayerListView, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectLayer(QListWidgetItem*)));
    connect(mLayerListView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectObjects()));
}

SCgLayersWidget::~SCgLayersWidget()
{
    delete mLayerListView;
}

void SCgLayersWidget::addLayer(int id, const QString &name)
{
    if (mLayerDict[id].isEmpty())
    {
        mLayerDict[id] = name;
        mLayerListView->addItem(name);
    }
}

void SCgLayersWidget::removeLayer(int id)
{
    QList<QListWidgetItem*> itemList = mLayerListView->findItems(mLayerDict[id],Qt::MatchCaseSensitive);
    if (itemList.size() != 0)
    {
        delete itemList.first();
        mLayerDict.remove(id);
    }
}

void SCgLayersWidget::createLayer()
{
    bool isAccepted;
    QString layerName = QInputDialog::getText(this, tr("Create layer"), tr("Please type name for new layer"),
                              QLineEdit::Normal, QString(), &isAccepted, Qt::Dialog);
    if (!isAccepted)
        return;

    QList<QListWidgetItem*> itemList = mLayerListView->findItems(layerName,Qt::MatchCaseSensitive);
    if (itemList.size() != 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Already exists"));
        return;
    }

    mScene->createLayerCommand(layerName, SCgLayer::User);
}

void SCgLayersWidget::deleteLayer()
{
    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->deleteLayerCommand(id,layerName);
    }
}

void SCgLayersWidget::showAll()
{
    SCgScene::SCgLayerMap layers = mScene->scgLayers();

    Q_FOREACH(SCgLayer* layer, layers)
        layer->show();
}

void SCgLayersWidget::hideAll()
{
    SCgScene::SCgLayerMap layers = mScene->scgLayers();

    Q_FOREACH(SCgLayer* layer, layers)
        layer->hide();
}

void SCgLayersWidget::customContextMenu(QPoint point)
{
    QMenu contextMenu(tr("Edit layers"), this);

    QAction* selectObjectAction = contextMenu.addAction(tr("Select objects"), this, SLOT(selectObjects()));
    QFont boldFont = selectObjectAction->font();
    boldFont.setBold(true);
    selectObjectAction->setFont(boldFont);
    contextMenu.addSeparator();
    contextMenu.addAction(tr("Show"), this, SLOT(showSelected()));
    contextMenu.addAction(tr("Hide"), this, SLOT(hideSelected()));
    contextMenu.addSeparator();
    contextMenu.addAction(tr("Remove"), this, SLOT(deleteLayer()));

    contextMenu.exec(mapToGlobal(point));
}

void SCgLayersWidget::showSelected()
{
    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->scgLayers()[id]->show();
    }
}

void SCgLayersWidget::hideSelected()
{
    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->scgLayers()[id]->hide();
    }
}

void SCgLayersWidget::selectLayer(QListWidgetItem* item)
{
    QString layerName = item->text();
    int id = mLayerDict.key(layerName);
    mScene->selectCurrentLayer(id);
}

void SCgLayersWidget::selectLayer(int id)
{
    QString layerName = mLayerDict[id];

    int count = mLayerListView->count();

    for(int index = 0; index < count; index++)
    {
        QListWidgetItem * item = mLayerListView->item(index);
        item->setSelected(false);
        if (layerName == item->text())
        {
            item->setSelected(true);
        }
    }
}

void SCgLayersWidget::selectObjects()
{
    mScene->clearSelection();

    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->scgLayers()[id]->selectObjects();
    }
}
