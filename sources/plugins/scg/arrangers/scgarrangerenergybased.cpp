#include "scgarrangerenergybased.h"

#include "scgforcecalculator.h"
#include "scgview.h"
#include "scgcontour.h"

#include <QApplication>
#include <QTimer>

#include <QFormLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>

#include <QtConcurrentMap>

SCgEnergyBasedArranger::SCgEnergyBasedArranger(QObject *parent)
    : SCgArranger(parent)
    , mDialog(0)
    , mSpringRate(1)
    , mSpringLength(100)
    , mRepulsionFactor(10000)
    , mFakeRepulsionFactor(500)
    , mShiftFactor(0.3)
{
    mNodes.clear();
    mTimerId = 0;

    mStopTimer = new QTimer(this);
    mStopTimer->setInterval(20000);
    mStopTimer->setSingleShot(true);
    connect(mStopTimer, SIGNAL(timeout()), SLOT(stopTimerTimeout()));

    connect(&mFutureWatcher, SIGNAL(finished()), SLOT(forceCalculationFinished()));
}
//------------------------------------------------------------------------------
SCgEnergyBasedArranger::~SCgEnergyBasedArranger()
{
}
//------------------------------------------------------------------------------
bool SCgEnergyBasedArranger::configDialog()
{
    if (!mDialog) {
        createDialog();
    }
    mDialog->setParent(mView->viewport(), Qt::Dialog);
    bool res = mDialog->exec() == QDialog::Accepted;

    mDialog->setParent(0, Qt::Dialog);

    return res;
}
//------------------------------------------------------------------------------
void SCgEnergyBasedArranger::startOperation()
{
    // Get selected SCgObjects:
    mNodes.clear();
    mPairs.clear();
    mBusses.clear();
    mContours.clear();
    foreach (QGraphicsItem *selectedItem, mView->scene()->selectedItems()) {
        if (SCgObject::isSCgObjectType(selectedItem->type())) {
            if (selectedItem->type() == SCgNode::Type) {
                SCgNode *node = static_cast<SCgNode *>(selectedItem);

                registerCommand(node, node->pos());

                mNodes.append(node);
            }
            if (selectedItem->type() == SCgPair::Type) {
                SCgPair *pair = static_cast<SCgPair *>(selectedItem);

                // Remove all pair break points:
                registerCommandRemoveBreakPoints(pair);

                mPairs.insert(pair);
            } else if (selectedItem->type() == SCgBus::Type) {
                mBusses.insert(static_cast<SCgBus *>(selectedItem));
            } else if (selectedItem->type() == SCgContour::Type) {
                SCgContour *contour = static_cast<SCgContour *>(selectedItem);

                // Minimize contour:
                registerCommandMinimizeContour(contour);

                mContours.insert(contour);
            }
        }
    }

    if (mTimerId == 0) {
        mStopTimer->start();
        mTimerId = startTimer(1000 / 40);
    }
}
//------------------------------------------------------------------------------
QDialog * SCgEnergyBasedArranger::createDialog()
{
    mDialog = new QDialog();
    mDialog->setWindowTitle(tr("Energy-based Arranger Parameters"));


    QLabel *springRateLabel = new QLabel(tr("Spring rate:"), mDialog);
    mSpringRateSpinBox = new QDoubleSpinBox(mDialog);
    mSpringRateSpinBox->setMaximum(100);
    mSpringRateSpinBox->setValue(mSpringRate);
    mSpringRateSpinBox->setToolTip(tr("Spring rate"));

    QLabel *springLengthLabel = new QLabel(tr("Spring length:"), mDialog);
    mSpringLengthSpinBox = new QDoubleSpinBox(mDialog);
    mSpringLengthSpinBox->setMaximum(10000);
    mSpringLengthSpinBox->setValue(mSpringLength);
    mSpringLengthSpinBox->setToolTip(tr("Natural spring length"));

    QLabel *repulsionFactorLabel = new QLabel(tr("Node repulsion factor:"), mDialog);
    mRepulsionFactorSpinBox = new QDoubleSpinBox(mDialog);
    mRepulsionFactorSpinBox->setMaximum(100000000);
    mRepulsionFactorSpinBox->setValue(mRepulsionFactor);
    mRepulsionFactorSpinBox->setToolTip(tr("Repulsive force factor between real nodes"));

    QLabel *fakeRepulsionFactorLabel = new QLabel(tr("Fake node repulsion factor:"), mDialog);
    mFakeRepulsionFactorSpinBox = new QDoubleSpinBox(mDialog);
    mFakeRepulsionFactorSpinBox->setMaximum(50000);
    mFakeRepulsionFactorSpinBox->setValue(mFakeRepulsionFactor);
    mFakeRepulsionFactorSpinBox->setToolTip(tr("Repulsive force factor between real and fake nodes"));

    QLabel *shiftFactorLabel = new QLabel(tr("Shift factor:"));
    mShiftFactorSpinBox = new QDoubleSpinBox(mDialog);
    mShiftFactorSpinBox->setMaximum(30);
    mShiftFactorSpinBox->setValue(mShiftFactor);
    mShiftFactorSpinBox->setToolTip(tr("Shift force factor"));


    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(springRateLabel, mSpringRateSpinBox);
    formLayout->addRow(springLengthLabel, mSpringLengthSpinBox);
    formLayout->addRow(repulsionFactorLabel, mRepulsionFactorSpinBox);
    formLayout->addRow(fakeRepulsionFactorLabel, mFakeRepulsionFactorSpinBox);
    formLayout->addRow(shiftFactorLabel, mShiftFactorSpinBox);


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), mDialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), mDialog, SLOT(reject()));
    buttonBox->setParent(mDialog);
    formLayout->addRow(buttonBox);

    mDialog->setLayout(formLayout);
    return mDialog;
}
//------------------------------------------------------------------------------
QString SCgEnergyBasedArranger::name() const
{
    return tr("Energy-based arrange");
}
//------------------------------------------------------------------------------
void SCgEnergyBasedArranger::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);


    Parameters parameters(mSpringRateSpinBox->value(), mSpringLengthSpinBox->value(),
                          mRepulsionFactorSpinBox->value(),
                          mFakeRepulsionFactorSpinBox->value());
    QFuture<Force> future = QtConcurrent::mapped(mNodes, SCgForceCalculator(mNodes, mPairs, mBusses, parameters));
    mFutureWatcher.setFuture(future);
}
//------------------------------------------------------------------------------
void SCgEnergyBasedArranger::stopTimerTimeout()
{
    if (mTimerId != 0) {
        //%qDebug() << "Timer was stopped after 20 000 ms";
        killTimer(mTimerId);
        registerMoving();
        mTimerId = 0;
    }
}
//------------------------------------------------------------------------------
void SCgEnergyBasedArranger::forceCalculationFinished()
{
    const QList<Force> forces = mFutureWatcher.future().results();
    QListIterator<Force> it(forces);
    qint32 index = 0;
    bool objectsMoved = false;
    while (it.hasNext()) {
        const Force &force = it.next();
        // If force isn't nearly 0, then move node:
        if (qAbs(force.mX) > 1 || qAbs(force.mY) > 1) {
            mNodes.at(index)->moveBy(force.mX * mShiftFactorSpinBox->value(),
                                     force.mY * mShiftFactorSpinBox->value());
            //%mNodes.at(index)->updateConnected();//%?
            objectsMoved = true;
        }
        ++index;
    }

    foreach (SCgContour *contour, mContours) {
        contour->minimize();
    }

    if (!objectsMoved) {
        killTimer(mTimerId);
        //%qDebug() << "Objects aren't moving. Timer was killed.";
        registerMoving();
        mTimerId = 0;
        mStopTimer->stop();
    }
}
//------------------------------------------------------------------------------
void SCgEnergyBasedArranger::registerMoving()
{
    foreach (SCgNode *node, mNodes) {
        registerCommand(node, node->pos());
    }
    foreach (SCgContour *contour, mContours) {
        registerCommand(contour, contour->scenePoints());
    }
}
//------------------------------------------------------------------------------
