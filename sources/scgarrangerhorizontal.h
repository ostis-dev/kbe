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
    //! @see SCgArranger::userMenu()
    bool configDialog();

    //! @see SCgArranger::startOperation()
    void startOperation();

    //! @see SCgArranger::name
    QString name() const;
};

#endif // SCGARRANGERHORIZONTAL_H
