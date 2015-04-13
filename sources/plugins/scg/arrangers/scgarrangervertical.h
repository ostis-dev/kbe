/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
    //! @see SCgArranger::userMenu()
    bool configDialog();

    //! @see SCgArranger::startOperation()
    void startOperation();

    //! @see SCgArranger::name
    QString name() const;
};

