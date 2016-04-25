/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommanddeletecontour.h"
#include "scgcommandobjectdelete.h"

#include "scgcontour.h"

SCgCommandDeleteContour::SCgCommandDeleteContour(SCgScene *scene,
                                                 SCgContour *contour,
                                                 QUndoCommand *parent)
    : SCgBaseCommand(scene, 0, parent)
    , mContour(contour)
{
    setText(QObject::tr("Delete contour"));
    Q_ASSERT_X(mContour != 0,
               "SCgCommandDeleteJustContour::SCgCommandDeleteJustContour(SCgScene *scene, "
               "SCgContour *contour, QUndoCommand *parent)",
               "Pointer to contour object is null");
}

SCgCommandDeleteContour::~SCgCommandDeleteContour()
{
}

void SCgCommandDeleteContour::redo()
{
    mChilds.clear();

    QGraphicsItem *parent = mContour->parentItem();
    QList<QGraphicsItem*> childs = mContour->childItems();
    QList<QGraphicsItem*>::iterator it;
    for (it = childs.begin(); it != childs.end(); ++it)
    {
        QGraphicsItem *item = *it;
        if (!SCgObject::isSCgObjectType(item->type()))
            continue;

        mChilds.push_back(item);
        item->setParentItem(parent);
    }

    if (childCount() == 0)
        new SCgCommandObjectDelete(mScene, mContour, this);

    SCgBaseCommand::redo();
}

void SCgCommandDeleteContour::undo()
{
    SCgBaseCommand::undo();

    QList<QGraphicsItem*>::iterator it;
    for (it = mChilds.begin(); it != mChilds.end(); ++it)
    {
        QGraphicsItem *item = *it;
        item->setParentItem(mContour);
    }
}
