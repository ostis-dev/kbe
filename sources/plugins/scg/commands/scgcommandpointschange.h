/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Command for changing points on SCgPointObject
class SCgCommandPointsChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    newPoints   Points will be set;
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandPointsChange(   SCgScene* scene,
                                    SCgPointObject* obj,
                                    const QVector<QPointF>& newPoints,
                                    QUndoCommand* parent = 0);

    virtual ~SCgCommandPointsChange();

protected:
    void redo();
    void undo();

private:
    bool mIsPair;
    double mOldEndDot;
    double mOldBeginDot;
    QVector<QPointF> mOldPoints;
    QVector<QPointF> mNewPoints;
};

