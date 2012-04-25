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
#include <QUndoCommand>

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

    if (res == QDialog::Rejected)
    {
        deleteGhosts();
        mArrangeItems.clear();
        mBusPairs.clear();
        mTupleNode = 0;
    }

    return res;
}

void SCgTupleArranger::startOperation()
{
    // affect changes to bus
    SCgBus *bus = mTupleNode->bus();
    Q_ASSERT(bus != 0);
    SCgBus *ghostBus = qgraphicsitem_cast<SCgBus*>(mGhosts[bus]);
    Q_ASSERT(ghostBus != 0);

    // map points into bus coordinates
    registerCommand(bus, ghostBus->points());

    // affect pairs and objects
    foreach(SCgPair *pair, mBusPairs)
    {
        SCgObject *end = pair->endObject();
        SCgObject *beg = pair->beginObject();
        Q_ASSERT(end != 0 && beg != 0);
        SCgPair *ghostPair = qgraphicsitem_cast<SCgPair*>(mGhosts[pair]);
        Q_ASSERT(ghostPair != 0);

        registerCommand(pair, ghostPair->points());

        if (beg->type() == SCgBus::Type)
            registerCommand(end, mGhosts[end]->pos());
        else
            registerCommand(beg, mGhosts[beg]->pos());
    }

    deleteGhosts();
}

QString SCgTupleArranger::name() const
{
    return tr("Tuple arranger");
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

    xSpin->setMaximum(500);
    xSpin->setMinimum(-500);
    xSpin->setValue((int)mOffsetX);

    ySpin->setMaximum(100);
    ySpin->setMinimum(-100);
    ySpin->setValue((int)mOffsetY);

    dSpin->setMaximum(100);
    dSpin->setMinimum(-100);
    dSpin->setValue((int)mObjectsDist);

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

    // list used to order pairs by dot value
    QList< QPair<qreal, SCgPair*> > unorderedPairs;

    foreach(QGraphicsItem *item, mView->scene()->items())
    {
        SCgPair *pair = qgraphicsitem_cast<SCgPair*>(item);
        if (pair != 0)
        {
            qreal dot = -1.f;
            if (pair->beginObject() == bus)
            {
                SCgObject *end = pair->endObject();
                if (end && (!SCgObject::isSCgPointObjectType(end->type())))
                {
                    mArrangeItems.append(pair);
                    mArrangeItems.append(end);

                    dot = pair->beginDot();
                }
            }

            if (pair->endObject() == bus)
            {
                SCgObject *beg = pair->beginObject();
                if (beg && (!SCgObject::isSCgPointObjectType(beg->type())))
                {
                    mArrangeItems.append(pair);
                    mArrangeItems.append(beg);

                    dot = pair->endDot();
                }
            }
            if (dot >= 0.f)
                unorderedPairs.append(qMakePair(dot, pair));
        }
    }

    //mArrangeItems.append(mTupleNode);
    mArrangeItems.append(bus);

    // order pairs
    qSort(unorderedPairs);
    QPair<qreal, SCgPair*> pairInfo;
    foreach (pairInfo, unorderedPairs)
        mBusPairs.append(pairInfo.second);

    return true;
}

void SCgTupleArranger::recalculateGhostsPosition()
{
    // calculate bus length and set objects to positions
    qreal busLength = mOffsetY + mObjectsDist * (mBusPairs.size() - 1);
    foreach(SCgPair *pair, mBusPairs)
    {
        SCgObject *realObj = 0;
        if (pair->endObject()->type() == SCgBus::Type)
            realObj = pair->beginObject();
        else
            realObj = pair->endObject();
        busLength += realObj->boundingRect().height();
    }
    busLength += 10;

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
        SCgObject *ghostEnd = mGhosts[pair->endObject()];
        Q_ASSERT(ghostEnd);
        SCgObject *ghostBeg = mGhosts[pair->beginObject()];
        Q_ASSERT(ghostBeg);

        if (ghostBeg->type() == SCgBus::Type)
        {
            ghostEnd->setPos(mTupleNode->pos().x() + mOffsetX,
                             mTupleNode->pos().y() + yPos);
            QVector<QPointF> points;
            points.append(QPointF(mTupleNode->pos().x(),
                                  mTupleNode->pos().y() + yPos));
            points.append(ghostEnd->pos());
            ghostPair->setPoints(points);

            yPos += ghostEnd->boundingRect().height();
        }else
        {
            ghostBeg->setPos(mTupleNode->pos().x() + mOffsetX,
                             mTupleNode->pos().y() + yPos);
            QVector<QPointF> points;
            points.append(ghostBeg->pos());
            points.append(QPointF(mTupleNode->pos().x(),
                                  mTupleNode->pos().y() + yPos));
            ghostPair->setPoints(points);

            yPos += ghostBeg->boundingRect().height();
        }


        //ghostPair->setBeginDot(ghostBus->dotPos(QPointF(mTupleNode->pos().x(),
        //                                                mTupleNode->pos().y() + yPos)));

        yPos += mObjectsDist;
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
