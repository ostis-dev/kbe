/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

/*! Object type changing command
  */
class SCgCommandObjectTypeChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to object for type changing
      @param    newType New object type
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectTypeChange(SCgScene *scene,
                                        SCgObject *object,
                                        const QString &newType,
                                        QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectTypeChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Old object type
    QString mOldType;
    //! New object type
    QString mNewType;
};


