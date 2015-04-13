/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Moves specified object from it's initial position to finish position.
class SCgCommandObjectMove : public SCgBaseCommand
{
public:
    explicit SCgCommandObjectMove(SCgScene *scene,
                                  SCgObject* obj,
                                  const QPointF& oldPos,
                                  const QPointF& newPos,
                                  QUndoCommand *parent = 0 );
    virtual ~SCgCommandObjectMove();

protected:
    void redo();
    void undo();

private:
    QPointF mOldPosition;
    QPointF mNewPosition;
};


