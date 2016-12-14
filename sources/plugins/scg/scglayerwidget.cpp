#define NODE_LAYER "node layer"
#define ARC_LAYER "arc layer"
#define BUS_LAYER "bus layer"
#define CONTOUR_LAYER "contour layer"

#include "scglayerwidget.h"
#include <QInputDialog>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

SCgLayerWidget::SCgLayerWidget(SCgScene* scene)
{
    this->scene = scene;
    scene->setLayerWidget(this);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(setVisibleSelected()));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customContextMenu(QPoint)));
    createStandartLayers();
}

SCgLayerWidget::~SCgLayerWidget()
{

}

QString SCgLayerWidget::getSelectedLayerName()
{
    QList<QListWidgetItem*> selItems = selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        return layerName;
    }
    return "";
}

void SCgLayerWidget::createLayer()
{
    bool isAccepted;
    QString layerName = QInputDialog::getText(this, tr("Create layer"), tr("Please type name for new layer"),
                              QLineEdit::Normal, QString(), &isAccepted, Qt::Dialog);
    if (!isAccepted)
        return;

    QList<QListWidgetItem*> itemList = findItems(layerName, Qt::MatchCaseSensitive);
    if (itemList.size() != 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Already exists"));
        return;
    }

    if (layerName.isEmpty())
        layerName = tr("New layer") + " " + QString::number(scene->getLayers().size() + 1);
    scene->createSCgLayer(layerName);
    QListWidgetItem* item = new QListWidgetItem(layerName, this);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    addItem(item);
}

void SCgLayerWidget::deleteLayer()
{
    QList<QListWidgetItem*> selItems = selectedItems();
    Q_FOREACH (QListWidgetItem* item, selItems)
    {
        QString layerName = item->text();
        if(layerName == NODE_LAYER
                || layerName == ARC_LAYER
                || layerName == BUS_LAYER
                || layerName == CONTOUR_LAYER)
        {
            QMessageBox::warning(this, tr("Warning"), tr("You can't delete standart layer"));
            return;
        }
        QList<QListWidgetItem*> itemList = findItems(layerName,Qt::MatchCaseSensitive);
        if (itemList.size() != 0)
        {
            delete itemList.first();
        }
        SCgLayer* layer = scene->findLayerWithName(layerName);
        if (layer != 0)
        {
            scene->deleteSCgLayer(layer);
        }
    }
}

void SCgLayerWidget::customContextMenu(QPoint point)
{
    QMenu contextMenu(tr("Edit layers"), this);

    contextMenu.addAction(tr("New layer"), this, SLOT(createLayer()));
    contextMenu.addAction(tr("Delete layer"), this, SLOT(deleteLayer()));

    contextMenu.exec(mapToGlobal(point));
}

void SCgLayerWidget::setVisibleSelected()
{
    for(int i = 0; i < count(); ++i)
    {
        QListWidgetItem* item = this->item(i);
        if (item->checkState() == Qt::Unchecked)
        {
            QString layerName = item->text();
            SCgLayer* layer = scene->findLayerWithName(layerName);
            if (layer != 0)
            {
                layer->setVisible(false);
            }
            item->setForeground(Qt::gray);
        } else
        {
            QString layerName = item->text();
            SCgLayer* layer = scene->findLayerWithName(layerName);
            if (layer != 0)
            {
                layer->setVisible(true);
            }
            item->setForeground(Qt::black);
        }
    }
}

void SCgLayerWidget::createStandartLayers()
{
    scene->createSCgLayer(NODE_LAYER);
    QListWidgetItem* item = new QListWidgetItem(NODE_LAYER, this);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    addItem(item);
    scene->createSCgLayer(ARC_LAYER);
    item = new QListWidgetItem(ARC_LAYER, this);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    addItem(item);
    scene->createSCgLayer(BUS_LAYER);
    item = new QListWidgetItem(BUS_LAYER, this);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    addItem(item);
    scene->createSCgLayer(CONTOUR_LAYER);
    item = new QListWidgetItem(CONTOUR_LAYER, this);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    addItem(item);
}
