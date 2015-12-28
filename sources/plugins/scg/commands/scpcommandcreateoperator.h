/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

class SCpCommandCreateOperator : public SCgBaseCommand
{
public:
    explicit SCpCommandCreateOperator(SCgScene * scene,
                                      QPointF const & pos,
                                      SCgContour * parentControur,
                                      QUndoCommand * parent = 0);
    virtual ~SCpCommandCreateOperator();

private:
    SCgContour * mParentContour;
    QPointF mPosition;
};

