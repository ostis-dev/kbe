#include "scgcommandidtfwidthchange.h"

#include <scgtextitem.h>

SCgCommandIdtfWidthChange::SCgCommandIdtfWidthChange(SCgObject *obj,
                                                     SCgScene *scene,
                                                     int oldIdtfWidth,
                                                     int newIdtfWidth,
                                                     QUndoCommand *parent)
    : SCgBaseCommand(scene, obj, parent),
      mObject(obj)
{
    Q_ASSERT(obj);

    setText(QObject::tr("Change identifier width"));
}

SCgCommandIdtfWidthChange::~SCgCommandIdtfMove()
{
}

void SCgCommandIdtfWidthChange::redo()
{
    if (mObject)
        mObject->mtxtItem->setTextWidth(mNewIdtfWidth);
    SCgBaseCommand::redo();
}

void SCgCommandIdtfWidthChange::undo()
{
    if (mObject)
        mObject->mTextItem->setTextWidth(mOldIdtfWidth);
    SCgBaseCommand::undo();
}
