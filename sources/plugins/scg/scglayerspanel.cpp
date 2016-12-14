/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scglayerspanel.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

#include <QMenu>
#include <QAction>

#include "scgscene.h"

SCgLayersPanel::SCgLayersPanel(SCgScene* scene, QWidget* parent)
    : QWidget(parent),
      mScene(scene)
{
    mScene->setLayersPanel(this);
    mToolBar = new QToolBar(this);
    mToolBar->addAction(QIcon(":/media/icons/add.png"), "Add layer", this, SLOT(createLayer()));
    mToolBar->addAction(QIcon(":/media/icons/remove.png"), "Delete layer", this, SLOT(deleteLayer()));
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

    connect(mLayerListView, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectLayer(QListWidgetItem*)));
    connect(mLayerListView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectObjects()));
    connect(mLayerListView, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(setVisibleSelected()));
}

SCgLayersPanel::~SCgLayersPanel()
{
    delete mLayerListView;
    delete mToolBar;
}

int SCgLayersPanel::getSelectedLayerId()
{
    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    QString layerName = selItems.first()->text();
    int id = mLayerDict.key(layerName);
    return id;
}

void SCgLayersPanel::addLayer(int id, const QString &name)
{
    if (mLayerDict[id].isEmpty())
    {
        QListWidgetItem* item = new QListWidgetItem(name, mLayerListView);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        mLayerDict[id] = name;
        mLayerListView->addItem(item);
    }
}

void SCgLayersPanel::removeLayer(int id)
{
    QList<QListWidgetItem*> itemList = mLayerListView->findItems(mLayerDict[id],Qt::MatchCaseSensitive);
    if (itemList.size() != 0)
    {
        delete itemList.first();
        mLayerDict.remove(id);
    }
}

void SCgLayersPanel::createLayer()
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

void SCgLayersPanel::deleteLayer()
{
    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->deleteLayerCommand(id,layerName);
    }
}

void SCgLayersPanel::showAll()
{
    for(int i = 0; i < mLayerListView->count(); ++i)
    {
        QListWidgetItem* item = mLayerListView->item(i);
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->getLayers()[id]->show();
        item->setForeground(Qt::black);
        item->setCheckState(Qt::Checked);
    }
}

void SCgLayersPanel::hideAll()
{
    for(int i = 0; i < mLayerListView->count(); ++i)
    {
        QListWidgetItem* item = mLayerListView->item(i);
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->getLayers()[id]->hide();
        item->setForeground(Qt::gray);
        item->setCheckState(Qt::Unchecked);
    }
}

void SCgLayersPanel::setVisibleSelected() {
    for(int i = 0; i < mLayerListView->count(); ++i)
    {
        QListWidgetItem* item = mLayerListView->item(i);
        if (item->checkState() == Qt::Unchecked)
        {
            QString layerName = item->text();
            int id = mLayerDict.key(layerName);
            mScene->getLayers()[id]->hide();
            item->setForeground(Qt::gray);
        } else
        {
            QString layerName = item->text();
            int id = mLayerDict.key(layerName);
            mScene->getLayers()[id]->show();
            item->setForeground(Qt::black);
        }
    }
}

void SCgLayersPanel::selectLayer(QListWidgetItem* item)
{
    QString layerName = item->text();
    int id = mLayerDict.key(layerName);
    mScene->selectCurrentLayer(id);
}

void SCgLayersPanel::selectLayer(int id)
{
    QString layerName = mLayerDict[id];

    int count = mLayerListView->count();

    for(int index = 0; index < count; ++index)
    {
        QListWidgetItem * item = mLayerListView->item(index);
        item->setSelected(false);
        if (layerName == item->text())
        {
            item->setSelected(true);
        }
    }
}

void SCgLayersPanel::selectObjects()
{
    mScene->clearSelection();

    QList<QListWidgetItem*> selItems = mLayerListView->selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        int id = mLayerDict.key(layerName);
        mScene->getLayers()[id]->selectObjects();
    }
}
