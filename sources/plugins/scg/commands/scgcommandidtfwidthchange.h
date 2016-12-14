#pragma once

#include "scgbasecommand.h"


class SCgCommandIdtfWidthChange : public SCgBaseCommand
{
public:
    /**
    * @brief Constructor
    * @param idtf           Item that contains object's identifier
    * @param scene          Pointer to the graphics scene that contains current object
    * @param oldWidth       Width of the identifier before changing
    * @param newPosition    Width of the identifier after changing
    * @param parent         Pointer to parent's undo command
    */
    explicit SCgCommandIdtfWidthChange(SCgObject *obj,
                                       SCgScene *scene,
                                       int oldIdtfWidth,
                                       int newIdtfWidth,
                                       QUndoCommand *parent = 0);

    //! Destructor
    virtual ~SCgCommandIdtfWidthChange();
protected:
    //! @copydoc QUndoCommand::redo
    void redo();
    //! @copydoc QUndoCommand::undo
    void undo();

private:
    //! Item that store object's identifier
    SCgObject *mObject;
    //! Identifier width before changing
    int mOldIdtfWidth;
    //! Identifier width after changing
    int mNewIdtfWidth;
};
