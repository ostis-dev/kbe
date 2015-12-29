/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpmode.h"
#include "scgcontour.h"

#include "commands/scpcommandcreateoperator.h"

SCpMode::SCpMode(SCgScene * parent)
    : SCgMode(parent)
{
}

SCpMode::~SCpMode()
{
}

SCgScene::EditMode SCpMode::mode() const
{
    return SCgScene::Mode_SCp;
}

void SCpMode::mousePress(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);


}

void SCpMode::mouseMove(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void SCpMode::mouseRelease(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void SCpMode::mouseDoubleClick(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    // left button
    if (event->button() == Qt::LeftButton)
    {
        QGraphicsItem * item = mScene->itemAt(mousePos);

        // check if there are no any items under mouse and create scg-node
        if (item == 0 || item->type() == SCgContour::Type)
        {
            SCgContour * contour = 0;
            if (item != 0 && item->type() == SCgContour::Type)
                contour = static_cast<SCgContour*>(item);

            mScene->doCommand(new SCpCommandCreateOperator(mScene, mousePos, contour));
            event->accept();
        }
    }
    SCgMode::mouseDoubleClick(event);
}
