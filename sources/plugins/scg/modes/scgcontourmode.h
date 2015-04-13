/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgmode.h"

class SCgContourMode: public SCgMode
{
    Q_OBJECT
public:
    explicit SCgContourMode(SCgScene* parent);

    virtual ~SCgContourMode();

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


