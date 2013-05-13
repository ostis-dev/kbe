#ifndef SCGARRANGERENERGYBASED_H
#define SCGARRANGERENERGYBASED_H

#include "scgarranger.h"

#include <QFutureWatcher>

class QDoubleSpinBox;

struct Force;
//------------------------------------------------------------------------------
class SCgEnergyBasedArranger : public SCgArranger
{
    Q_OBJECT

public:
    enum
    {
        Type = 5
    };

    explicit SCgEnergyBasedArranger(QObject *parent = 0);
    virtual ~SCgEnergyBasedArranger();

    //! @see SCgArranger::type().
    int type() const {return Type;}

protected:
    //! @see SCgArranger::configDialog()
    bool configDialog();

    //! @see SCgArranger::startOperation()
    void startOperation();

    //! Holds dialog window, shown to user.
    //! @see SCgArrangerEnergyBased::createDialog()
    QDialog *mDialog;

    //! Creates dialog for asking energy-based arrange parameters.
    QDialog * createDialog();

    //! @see SCgArranger::name
    QString name() const;

    //! Recalculates forces and moves objects each 25 ms.
    void timerEvent(QTimerEvent *event);

    /*! @defgroup EnergyBasedPars Energy-based arranger parameters
     *  @{
     */
    double mSpringRate;
    double mSpringLength;
    double mRepulsionFactor;
    double mFakeRepulsionFactor;
    double mShiftFactor;

    QDoubleSpinBox *mSpringRateSpinBox;
    QDoubleSpinBox *mSpringLengthSpinBox;
    QDoubleSpinBox *mRepulsionFactorSpinBox;
    QDoubleSpinBox *mFakeRepulsionFactorSpinBox;
    QDoubleSpinBox *mShiftFactorSpinBox;
    /*! @}*/

private:
    //! Register undo/redo commands for object moving.
    void registerMoving();

    //! Nodes which were selected during the operation start.
    QList<SCgNode *> mNodes;

    //! SCgPairs which were selected during the operation start.
    QSet<SCgPair *> mPairs;

    //! SCgBusses which were selected during the operation start.
    QSet<SCgBus *> mBusses;

    //! SCgContours which were selected during the operation start.
    QSet<SCgContour *> mContours;

    //! Timer id which calls timerEvent every 25 ms.
    qint32 mTimerId;

    //! Timer which stops the arranging after 20 s.
    QTimer *mStopTimer;

    //! Allows monitoring a QFuture using signals and slots.
    //! @see SCgArrangerEnergyBased::forceCalculationFinished()
    QFutureWatcher<Force> mFutureWatcher;

private slots:
    //! Stops the arranging.
    void stopTimerTimeout();

    //! Process results of multithread execution.
    void forceCalculationFinished();
};
//------------------------------------------------------------------------------
#endif // SCGARRANGERENERGYBASED_H
