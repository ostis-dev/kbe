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
along with OSTIS.  If not, see .
-----------------------------------------------------------------------------
*/

#ifndef SCGNODETEXTITEM_H
#define SCGNODETEXTITEM_H


#include "scgtextitem.h"
#include "scgnode.h"
#include <QVector>

class QGraphicsSceneMouseEvent;

class SCgNodeTextItem : public SCgTextItem
{
    Q_OBJECT
    friend class SCgNode;

public:
    //! Object type
    enum { Type = UserType + 9 };

    explicit SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::eIdentifierPosition idtfPos = SCgNode::BottomRight, QGraphicsScene* scene = 0);
    explicit SCgNodeTextItem(SCgNode* parent, SCgNode::eIdentifierPosition idtfPos = SCgNode::BottomRight, QGraphicsScene* scene = 0);
    virtual ~SCgNodeTextItem();

    //! Return a type of graphics item as integer
    virtual int type() const { return Type; }

    /**
    * @brief function show or hide 4 possible of SCgNodeTextItem
    * @param isShow show or hide textItemPositions, show - true, hide - false
    * @param scene  Pointer to the graphics scene that contains current item
    */
    void showPositions(SCgScene * scgScene, bool isShow);
protected:
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void setTextPos(SCgNode::eIdentifierPosition pos);

    void createTextItemPositions(SCgScene * scgScene);

    SCgNode::eIdentifierPosition textPos() const;

    void updateTextPos(SCgNode::eIdentifierPosition pos);
    SCgNode::eIdentifierPosition posToIdtfPos(const QPointF &point) const;

    SCgNode::eIdentifierPosition mTextPos;
    SCgNode *mParentItem;

    //! 4 possible postion of ScgNodeTextItem (see ScgNode::eIdentifierPosition)
    QVector<QGraphicsRectItem*> textItemPositions;
};

#endif // SCGNODETEXTITEM_H
