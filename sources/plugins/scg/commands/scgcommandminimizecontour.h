/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Command for minimizing contour size.
class SCgCommandMinimizeContour : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    contour     Contour which will be minimized
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandMinimizeContour(SCgScene *scene,
                                       SCgContour *contour,
                                       QUndoCommand *parent = 0);

    virtual ~SCgCommandMinimizeContour();

protected:
    void redo();
    void undo();

private:
    QVector<QPointF> mOldPoints;
    QVector<QPointF> mNewPoints;
};


