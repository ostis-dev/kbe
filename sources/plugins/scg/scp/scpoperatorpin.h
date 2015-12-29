/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QGraphicsItem>

class SCpOperatorPin : public QGraphicsItem
{
    friend class SCpOperator;

public:
    explicit SCpOperatorPin(QString const & displayName, QGraphicsItem * parent = 0);
    virtual ~SCpOperatorPin();

    typedef enum
    {
        Input,
        Output
    } ePinType;

    void setPinType(ePinType pinType);
    ePinType pinType() const;

    void setDisplayName(QString const & displayName);
    QString const & displayName() const;

protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, QStyleOptionGraphicsItem const * option, QWidget * widget);

    // hover events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void updateBounds();

private:
    // cached bounds rectangle
    QRectF mBoundRect;
    ePinType mPinType;
    QString mDisplayName;

    bool mIsHovered:1;
};
