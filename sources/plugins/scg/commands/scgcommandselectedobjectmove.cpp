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


#include "scgcommandselectedobjectmove.h"

#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgcontour.h"
#include "../scgbus.h"
#include "../scgscene.h"

SCgCommandSelectedObjectMove::SCgCommandSelectedObjectMove(SCgScene *scene,
                                                            const SCgScene::ObjectUndoInfo& undoInfo,
                                                            QUndoCommand *parent):
        SCgBaseCommand(scene, 0, parent),
        mUndoInfo(undoInfo)
{
    setText(QObject::tr("Move items"));
}

SCgCommandSelectedObjectMove::~SCgCommandSelectedObjectMove()
{

}

bool SCgCommandSelectedObjectMove::mergeWith (const QUndoCommand* command)
{
    if (command->id() != id() || childCount() || command->childCount())
        return false;

    const SCgCommandSelectedObjectMove* c = static_cast<const SCgCommandSelectedObjectMove*>(command);
    if(mUndoInfo.keys() != c->mUndoInfo.keys())
        return false;

    qreal maxManhattanLength = 0;

    SCgScene::ObjectUndoInfo::ConstIterator const_it = c->mUndoInfo.begin();
    while(const_it != c->mUndoInfo.end())
    {
        QPointF offset = const_it.value().second.second - const_it.value().first.second;
        if(offset.manhattanLength() > maxManhattanLength)
            maxManhattanLength = offset.manhattanLength();
        ++const_it;
    }

    if(maxManhattanLength > 35)
        return false;

    SCgScene::ObjectUndoInfo::iterator it = mUndoInfo.begin();
    while(it != mUndoInfo.end())
    {
        it.value().second = c->mUndoInfo.value(it.key()).second;
        ++it;
    }
    return true;
}

void SCgCommandSelectedObjectMove::redo()
{
    SCgScene::ObjectUndoInfo::ConstIterator const_it = mUndoInfo.begin();
    while(const_it != mUndoInfo.end())
    {
        const_it.key()->setParentItem(const_it.value().second.first);
        const_it.key()->setPos(const_it.value().second.second);
        ++const_it;
    }
    SCgBaseCommand::redo();
}

void SCgCommandSelectedObjectMove::undo()
{
    SCgScene::ObjectUndoInfo::ConstIterator const_it = mUndoInfo.begin();
    while(const_it != mUndoInfo.end())
    {
        const_it.key()->setParentItem(const_it.value().first.first);
        const_it.key()->setPos(const_it.value().first.second);
        ++const_it;
    }
}
