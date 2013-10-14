#ifndef SCGNODETEXTITEM_H
#define SCGNODETEXTITEM_H


#include "scgtextitem.h"
#include "scgnode.h"

class QGraphicsSceneMouseEvent;

class SCgNodeTextItem : public SCgTextItem
{
    Q_OBJECT

public:
    //! Object type
    enum { Type = UserType + 9 };

    explicit SCgNodeTextItem(const QString &str, SCgNode* parent, SCgNode::IdentifierPosition idtfPos = SCgNode::BottomRight, QGraphicsScene* scene = 0);
    explicit SCgNodeTextItem(SCgNode* parent, SCgNode::IdentifierPosition idtfPos = SCgNode::BottomRight, QGraphicsScene* scene = 0);
    virtual ~SCgNodeTextItem();

protected:
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void setTextPos(SCgNode::IdentifierPosition pos);
    SCgNode::IdentifierPosition textPos() const { return mTextPos; }
    void updateTextPos(SCgNode::IdentifierPosition pos);
    SCgNode::IdentifierPosition posToIdtfPos(const QPointF &point) const;

    SCgNode::IdentifierPosition mTextPos;
    SCgNode *mParentItem;

	friend class SCgNode;
};

#endif // SCGNODETEXTITEM_H
