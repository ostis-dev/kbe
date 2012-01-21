#include "scgarrangertuple.h"

#include "scgview.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgpair.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

SCgTupleArranger::SCgTupleArranger(QObject *parent) :
    SCgArranger(parent),
    mDialog(0),
    mTupleNode(0),
    mObjectsDist(10),
    mOffsetX(150),
    mOffsetY(20)
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
    if (!findArrangeItems()) return false;


    createGhosts(mArrangeItems);

    recalculateGhostsPosition();

    bool res = mDialog->exec() == QDialog::Accepted;

    mDialog->setParent(0, Qt::Dialog);

    return res;
}

void SCgTupleArranger::startOperation()
{
    // affect changes to bus
    SCgBus *bus = mTupleNode->bus();
    Q_ASSERT(bus != 0);
    SCgBus *ghostBus = qgraphicsitem_cast<SCgBus*>(mGhosts[bus]);
    Q_ASSERT(ghostBus != 0);

    // affect pairs and objects
    foreach(SCgPair *pair, mBusPairs)
    {
        SCgObject *end = pair->getEndObject();
        Q_ASSERT(end != 0);
        SCgObject *ghostEnd = mGhosts[end];
        Q_ASSERT(ghostEnd != 0);
        SCgPair *ghostPair = qgraphicsitem_cast<SCgPair*>(mGhosts[pair]);
        Q_ASSERT(ghostPair != 0);

        registerCommand(pair, ghostPair->points());
        registerCommand(end, ghostEnd->pos());
    }

    registerCommand(bus, ghostBus->points());

    deleteGhosts();
}

void SCgTupleArranger::createDialog()
{
    mDialog = new QDialog();
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    buttonBox->setParent(mDialog);

    QLabel *xLabel = new QLabel(tr("Horizontal offset"), mDialog);
    QLabel *yLabel = new QLabel(tr("Vertical offset"), mDialog);
    QLabel *dLabel = new QLabel(tr("Distance between objects"), mDialog);

    QSpinBox *xSpin = new QSpinBox(mDialog);
    QSpinBox *ySpin = new QSpinBox(mDialog);
    QSpinBox *dSpin = new QSpinBox(mDialog);

    xSpin->setValue((int)mOffsetX);
    xSpin->setMaximum(500);
    xSpin->setMinimum(-500);

    ySpin->setValue((int)mOffsetY);
    ySpin->setMaximum(100);
    ySpin->setMinimum(-100);

    dSpin->setValue((int)mObjectsDist);
    dSpin->setMaximum(100);
    dSpin->setMinimum(-100);

    QVBoxLayout *vlX = new QVBoxLayout();
    vlX->addWidget(xLabel);
    vlX->addWidget(xSpin);

    QVBoxLayout *vlY = new QVBoxLayout();
    vlY->addWidget(yLabel);
    vlY->addWidget(ySpin);

    QVBoxLayout *vlD = new QVBoxLayout();
    vlD->addWidget(dLabel);
    vlD->addWidget(dSpin);

    QHBoxLayout *hl = new QHBoxLayout();
    hl->addLayout(vlX);
    hl->addLayout(vlY);
    hl->addLayout(vlD);

    connect(xSpin, SIGNAL(valueChanged(int)), this, SLOT(xValueChanged(int)));
    connect(ySpin, SIGNAL(valueChanged(int)), this, SLOT(yValueChanged(int)));
    connect(dSpin, SIGNAL(valueChanged(int)), this, SLOT(dValueChanged(int)));
    connect(buttonBox, SIGNAL(accepted()), mDialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), mDialog, SLOT(reject()));

    QVBoxLayout *vl = new QVBoxLayout();

    vl->addLayout(hl);
    vl->addWidget(buttonBox);

    mDialog->setLayout(vl);
}

bool SCgTupleArranger::findArrangeItems()
{
    mTupleNode = 0;
    mBusPairs.clear();
    mArrangeItems.clear();

    QList<QGraphicsItem *>  selItems = mView->scene()->selectedItems();
    if (selItems.size() > 1 || selItems.empty()) return false;

    if (SCgNode::Type == selItems.first()->type())
        mTupleNode = qgraphicsitem_cast<SCgNode*>(selItems.first());

    if (mTupleNode == 0) return false;     // do nothing

    SCgBus *bus = mTupleNode->bus();
    if (bus == 0) return false; // do nothing

    foreach(QGraphicsItem *item, mView->scene()->items())
    {
        SCgPair *pair = qgraphicsitem_cast<SCgPair*>(item);
        if (pair != 0 && pair->getBeginObject() == bus)
        {
            SCgObject *end = pair->getEndObject();
            if (end && (!SCgObject::isSCgPointObjectType(end->type())))
            {

                mBusPairs.append(pair);

                mArrangeItems.append(pair);
                mArrangeItems.append(pair->getEndObject());
            }
        }
    }

    //mArrangeItems.append(mTupleNode);
    mArrangeItems.append(bus);

    return true;
}

void SCgTupleArranger::recalculateGhostsPosition()
{
    // calculate bus length and set objects to positions
    int idx = 0;
    qreal busLength = mOffsetY + mObjectsDist * mBusPairs.size();
    foreach(SCgPair *pair, mBusPairs)
    {
        SCgObject *realObj = pair->getEndObject();
        busLength += realObj->boundingRect().height();
    }

    // arrange bus
    SCgBus *realBus = mTupleNode->bus();
    SCgBus *ghostBus = qgraphicsitem_cast<SCgBus*>(mGhosts[realBus]);
    Q_ASSERT(realBus != 0);

    QVector<QPointF> points;
    points.append(mTupleNode->pos());
    points.append(QPointF(mTupleNode->pos().x(), mTupleNode->pos().y() + busLength));

    ghostBus->setPoints(points);
    //ghostBus->updatePosition();

    // arrage pairs
    qreal yPos = mOffsetY;
    foreach(SCgPair *pair, mBusPairs)
    {
        SCgPair *ghostPair = qgraphicsitem_cast<SCgPair*>(mGhosts[pair]);
        Q_ASSERT(ghostPair != 0);
        SCgObject *ghostEnd = mGhosts[pair->getEndObject()];
        Q_ASSERT(ghostEnd);

        ghostEnd->setPos(mTupleNode->pos().x() + mOffsetX,
                         mTupleNode->pos().y() + yPos);

        QVector<QPointF> points;
        points.append(QPointF(mTupleNode->pos().x(),
                              mTupleNode->pos().y() + yPos));
        points.append(ghostEnd->pos());
        ghostPair->setPoints(points);
        //ghostPair->setBeginDot(ghostBus->dotPos(QPointF(mTupleNode->pos().x(),
        //                                                mTupleNode->pos().y() + yPos)));

        yPos += ghostEnd->boundingRect().height() + mObjectsDist;
    }

}

void SCgTupleArranger::xValueChanged(int newSpacing)
{
    mOffsetX = newSpacing;
    recalculateGhostsPosition();
}

void SCgTupleArranger::yValueChanged(int newSpacing)
{
    mOffsetY = newSpacing;
    recalculateGhostsPosition();
}

void SCgTupleArranger::dValueChanged(int newSpacing)
{
    mObjectsDist = newSpacing;
    recalculateGhostsPosition();
}
