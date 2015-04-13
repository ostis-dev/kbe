/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

//! Moves specified object from it's initial position to finish position.
class SCgCommandSelectedObjectMove : public SCgBaseCommand
{
public:
    /*! This command will be major if we'll rewrite scene event handling.
     * @param undoInfo Map holding object and pair with it's
     * initial parent, position and final parent, position.
     */
    explicit SCgCommandSelectedObjectMove(SCgScene *scene,
                                      const SCgScene::ObjectUndoInfo& undoInfo,
                                      QUndoCommand *parent = 0 );
    virtual ~SCgCommandSelectedObjectMove();

    int id() const
    {
        return 1;
    }

    bool mergeWith (const QUndoCommand* command);

protected:
    void redo();
    void undo();

private:
    SCgScene::ObjectUndoInfo mUndoInfo;
};


