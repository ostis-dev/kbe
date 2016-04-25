/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgselect.h"

class SCgSelectSubGraph : public SCgSelect
{
    Q_OBJECT
public:
    explicit SCgSelectSubGraph(QObject *parent = 0);
    virtual ~SCgSelectSubGraph();
    
    //! @copydoc SCgSelect::doSelection
    void doSelection(SCgScene *scene);

private:
    /*! Select specified \p obj and call that function for all connected
      * to \p obj objects, that aren't selected yet.
      * @param obj Pointer to object, that need to be selected
      */
    void select(SCgObject *obj);

signals:
    
public slots:
    
};

