/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgbasecommand.h"

#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"
#include "scgbus.h"
#include "scgscene.h"

SCgBaseCommand::SCgBaseCommand(SCgScene *scene,
                               SCgObject *object,
                               QUndoCommand *parent) :
        QUndoCommand(parent),
        mScene(scene),
        mObject(object)
{
    //Q_ASSERT(mObject);
}

SCgBaseCommand::~SCgBaseCommand()
{

}

QGraphicsScene* SCgBaseCommand::getScene() const
{
    return mScene;
}
