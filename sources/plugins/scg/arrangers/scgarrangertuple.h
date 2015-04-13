/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgarranger.h"

#include <QList>

class SCgTupleArranger : public SCgArranger
{
    Q_OBJECT

public:
    enum
    {
        Type = 4
    };

    explicit SCgTupleArranger(QObject *parent = 0);
    virtual ~SCgTupleArranger();

protected:
    //!  @see SCgArranger::userMenu
    bool configDialog();

    //!  @see SCgArranger::startOperation
    void startOperation();

    //!  @see SCgArranger::type
    int type() const { return Type; }

    //! @see SCgArranger::name
    QString name() const;

    /*! Create configuration dialog
      */
    void createDialog();

    /*! Get items that will be arranged
      * @param Return true, if all items founded; otherwise return false
      */
    bool findArrangeItems();

    //! Calculate positions for ghosts
    void recalculateGhostsPosition();



protected slots:
    /*! @defgroup Slots Slots to react on user actions
     *  @{
     */
    void xValueChanged(int newSpacing);
    void yValueChanged(int newSpacing);
    void dValueChanged(int newSpacing);
    /*! @}*/

private:
    //! Dialog to configure arrange parameters
    QDialog *mDialog;
    //! List of all arrange items
    QList<QGraphicsItem*> mArrangeItems;
    //! Pointer to a tuple
    SCgNode *mTupleNode;
    //! List of pairs, that go out from a tuple bus
    QList<SCgPair*> mBusPairs;

    //! Distance between tuple objects (end objects for bus pairs)
    qreal mObjectsDist;
    //! Initial x offset
    qreal mOffsetX;
    //! Initial y offset
    qreal mOffsetY;
};


