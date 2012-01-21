#ifndef SCGARRANGERVERTICAL_H
#define SCGARRANGERVERTICAL_H

#include "scgarranger.h"

class SCgVerticalArranger : public SCgArranger
{
Q_OBJECT

public:
    enum
    {
        Type = 1
    };
    explicit SCgVerticalArranger(QObject *parent = 0);
    virtual ~SCgVerticalArranger();

    //! @see SCgArranger::type().
    int type() const {return Type;}

protected:
    //!  @see SCgArranger::userMenu()
    bool userMenu();

    //!  @see SCgArranger::startOperation()
    void startOperation();
};

#endif // SCGARRANGERVERTICAL_H
