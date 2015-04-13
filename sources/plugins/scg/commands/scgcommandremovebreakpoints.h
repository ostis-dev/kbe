/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Command for removing break points of pairs.
class SCgCommandRemoveBreakPoints : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    pair        Pair which will be removed break points
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandRemoveBreakPoints(SCgScene *scene,
                                         SCgPair *pair,
                                         QUndoCommand *parent = 0);
    virtual ~SCgCommandRemoveBreakPoints();

protected:
    void redo();
    void undo();

private:
    double mOldBeginDot;
    double mOldEndDot;
    QVector<QPointF> mOldPoints;
};

