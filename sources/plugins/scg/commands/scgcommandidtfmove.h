/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCGCOMMANDIDTFMOVE_H
#define SCGCOMMANDIDTFMOVE_H

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
    explicit SCgCommandIdtfMove(SCgTextItem *idtf,
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
    SCgTextItem *mIdtfItem;
    //! Position before moving
    QPointF mOldPosition;
    //! Position after moving
    QPointF mNewPosition;
};

#endif // SCGCOMMANDIDTFMOVE_H
