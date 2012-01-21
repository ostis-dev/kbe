#include "scgarrangertuple.h"

#include "scgview.h"
#include "scgnode.h"
#include "scgbus.h"

#include <QDialogButtonBox>

SCgTupleArranger::SCgTupleArranger(QObject *parent) :
    SCgArranger(parent),
    mDialog(0)
{

}

SCgTupleArranger::~SCgTupleArranger()
{

}

bool SCgTupleArranger::configDialog()
{
    if(!mDialog)    createDialog();
    mDialog->setParent(mView->viewport(), Qt::Dialog);

    // Create ghost only for visible objects
    QList<QGraphicsItem*> items;
    findItems(items);

    if (items.size() == 0) return false;

    createGhosts(items);

    //recalculateGhostsPosition();

    bool res = mDialog->exec() == QDialog::Accepted;

    deleteGhosts();

    mDialog->setParent(0, Qt::Dialog);

    return res;
}

void SCgTupleArranger::startOperation()
{

}

void SCgTupleArranger::createDialog()
{
    mDialog = new QDialog();
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    buttonBox->setParent(mDialog);


    connect(buttonBox, SIGNAL(accepted()), mDialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), mDialog, SLOT(reject()));
}

void SCgTupleArranger::findItems(QList<QGraphicsItem *> &items)
{
    QList<QGraphicsItem *>  selItems = mView->scene()->selectedItems();
    if (items.size() > 1) return;

    SCgNode *tuple = 0;
    if (SCgNode::Type == selItems.first()->type())
        tuple = qgraphicsitem_cast<SCgNode*>(selItems.first());

    if (tuple == 0) return;     // do nothing

    SCgBus *bus = tuple->bus();
    if (bus == 0) return; // do nothing


    items.push_back(tuple);
    items.push_back(bus);
}
