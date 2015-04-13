/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgtextitem.h"
#include "scgnode.h"

class QGraphicsSceneMouseEvent;

class SCgNodeTextItem : public SCgTextItem
{
    Q_OBJECT
    friend class SCgNode;

public:
    //! Object type
    enum { Type = UserType + 9 };

    explicit SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::IdentifierPosition idtfPos = SCgNode::BottomRight);
    explicit SCgNodeTextItem(SCgNode* parent, SCgNode::IdentifierPosition idtfPos = SCgNode::BottomRight);
    virtual ~SCgNodeTextItem();

    //! Return a type of graphics item as integer
    virtual int type() const { return Type; }

    void setTextPos(const QPointF &pos);

    void setPlainText(const QString &text);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void setNodeTextPos(SCgNode::IdentifierPosition pos);
    SCgNode::IdentifierPosition nodeTextPos() const;

    void updateTextPos(SCgNode::IdentifierPosition pos);
    SCgNode::IdentifierPosition posToIdtfPos(const QPointF &point) const;

    SCgNode::IdentifierPosition mTextPos;
    SCgNode *mParentItem;
};


