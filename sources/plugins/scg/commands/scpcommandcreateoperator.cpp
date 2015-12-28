/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpcommandcreateoperator.h"

SCpCommandCreateOperator::SCpCommandCreateOperator(SCgScene * scene,
                                                   QPointF const & pos,
                                                   SCgContour * parentContour,
                                                   QUndoCommand * parent)
    : SCgBaseCommand(scene, 0, parent)
    , mParentContour(parentContour)
    , mPosition(pos)
{

}

SCpCommandCreateOperator::~SCpCommandCreateOperator()
{

}
