#ifndef SCGARRANGERTUPLE_H
#define SCGARRANGERTUPLE_H

#include "scgarranger.h"

class SCgTupleArranger : public SCgArranger
{
    Q_OBJECT

public:
    enum
    {
        Type = 4
    };

    explicit SCgTupleArranger(QObject *parent = 0);
    virtual ~SCgTupleArranger();

protected:
    //!  @see SCgArranger::userMenu()
    bool configDialog();

    //!  @see SCgArranger::startOperation()
    void startOperation();

    //!  @see SCgArranger::type()
    int type() const { return Type; }

    /*! Create configuration dialog
      */
    void createDialog();

    /*! Get items that will be arranged
      * @param items Container to get result
      */
    void findItems(QList<QGraphicsItem*> &items);

private:
    //! Dialog to configure arrange parameters
    QDialog *mDialog;
};

#endif // SCGARRANGERTUPLE_H
