/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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

    QVector<QGraphicsRectItem*> textItemPositions;
};

#endif // SCGNODETEXTITEM_H
