/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgselect.h"

#include <QObject>

class SCgSelectInputOutput : public SCgSelect
{
    Q_OBJECT

public:
    explicit SCgSelectInputOutput(QObject *parent = 0);
    virtual ~SCgSelectInputOutput();
    
    //! @copydoc SCgSelect::doSelection
    void doSelection(SCgScene *scene);

signals:
    
public slots:
    
};

