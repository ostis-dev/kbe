#ifndef SCGARRANGERHORIZONTAL_H
#define SCGARRANGERHORIZONTAL_H

#include "scgarranger.h"

class SCgHorizontalArranger : public SCgArranger
{
Q_OBJECT

public:
    enum
    {
        Type = 2
    };
    explicit SCgHorizontalArranger(QObject *parent = 0);
    virtual ~SCgHorizontalArranger();

    //! @see SCgArranger::type().
    int type() const {return Type;}
protected:
    //!  @see SCgArranger::userMenu()
    bool userMenu();

    //!  @see SCgArranger::startOperation()
    void startOperation();
};

#endif // SCGARRANGERHORIZONTAL_H
