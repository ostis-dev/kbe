/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpcommandcreateoperator.h"
#include "scp/scpoperator.h"

SCpCommandCreateOperator::SCpCommandCreateOperator(SCgScene * scene,
                                                   QPointF const & pos,
                                                   SCgContour * parentContour,
                                                   QUndoCommand * parent)
    : SCgBaseCommand(scene, 0, parent)
    , mParentContour(parentContour)
    , mPosition(pos)
    , mOperator(0)
{
    setText(QObject::tr("Create SCp operator"));
    createOperator();
}

SCpCommandCreateOperator::~SCpCommandCreateOperator()
{
    if (mOperator)
        delete mOperator;
}

void SCpCommandCreateOperator::onOperatorDestroyed()
{
    mOperator = 0;
}

void SCpCommandCreateOperator::createOperator()
{
    Q_ASSERT(mOperator == 0);

    mOperator = new SCpOperator(0);
    connect(mOperator, SIGNAL(destroyed()), this, SLOT(onOperatorDestroyed()));
}

void SCpCommandCreateOperator::undo()
{
    mScene->removeItem(mOperator);
    mOperator->setDead(true);
}

void SCpCommandCreateOperator::redo()
{
    mScene->addItem(mOperator);
    mOperator->setPos(mPosition);
    mOperator->setDead(false);
}
