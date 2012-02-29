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

#ifndef SCGCONTOURMODEEVENTHANDLER_H_
#define SCGCONTOURMODEEVENTHANDLER_H_

#include "SCgEventHandler.h"

class SCgContourModeEventHandler: public SCgEventHandler
{
    Q_OBJECT
public:
    explicit SCgContourModeEventHandler(SCgScene* parent);

    virtual ~SCgContourModeEventHandler();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mousePress(QGraphicsSceneMouseEvent *event);
    void mouseMove(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Contour;
    }

protected:

    /*! Start linear object creation
        @param point    begin point
      */
    void startLineCreation(const QPointF &point);

    /*! End linear object creation
      */
    void endLineCreation();

    /*!
     * Updates a line between last point and current mouse position
     */
    void updateLastLine(QPointF mousePos);

    //! Line drawn from last point to mouse position
    QGraphicsLineItem* mClosingSubpathLine;

    /*! Selects items, which will be included into created contour.
     *  Item is included if it is within mPathItem and has the same parent (with mPathItem).
     */
    QList<QGraphicsItem* > selectItemsForContour() const;

};

#endif /* SCGCONTOURMODEEVENTHANDLER_H_ */
