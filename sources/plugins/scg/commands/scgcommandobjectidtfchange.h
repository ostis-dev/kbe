/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/*! Object identification change command
  */
class SCgCommandObjectIdtfChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to object for identifier changing
      @param    newIdtf New object identifier
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectIdtfChange(SCgScene *scene,
                                        SCgObject *object,
                                        const QString &newIdtf,
                                        QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectIdtfChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Old identifier
    QString mOldIdtf;
    //! New identifier
    QString mNewIdtf;
};


