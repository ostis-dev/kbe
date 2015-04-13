/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/**
* @brief Class released an undo command for object's identifier moving
*/
class SCgCommandIdtfMove : public SCgBaseCommand
{
public:
    /**
    * @brief Constructor
    * @param idtf           Item that contains object's identifier
    * @param scene          Pointer to the graphics scene that contains current object
    * @param oldPosition    Position of the identifier before moving
    * @param newPosition    Position of the identifier after moving
    * @param parent         Pointer to parent's undo command
    */
    explicit SCgCommandIdtfMove(SCgObject *obj,
                                SCgScene *scene,
                                const QPointF& oldPosition,
                                const QPointF& newPosition,
                                QUndoCommand *parent = 0);

    //! Destructor
    virtual ~SCgCommandIdtfMove();
protected:
    //! @copydoc QUndoCommand::redo
    void redo();
    //! @copydoc QUndoCommand::undo
    void undo();

private:
    //! Item that store object's identifier
    SCgObject *mObject;
    //! Position before moving
    QPointF mOldPosition;
    //! Position after moving
    QPointF mNewPosition;
};


