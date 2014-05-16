#ifndef SCGTEMPLATEMODE_H
#define SCGTEMPLATEMODE_H

#include "scgmode.h"
#include "scginsertmode.h"

class SCgTemplateMode : public SCgMode
{
public:
    SCgTemplateMode(SCgScene* parent);

    void mouseDoubleClick(QGraphicsSceneMouseEvent *event);

    void mouseMove(QGraphicsSceneMouseEvent *event);

    void mousePress(QGraphicsSceneMouseEvent *event);

    void mouseRelease(QGraphicsSceneMouseEvent *event);

    void keyPress(QKeyEvent *event);

    void activate();



    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Template;
    }

    SCgNode *createGoToNodeAtribute(const QPointF &pos);
    QPointF calc(QPointF beginPoint, QPointF endPoint);
    SCgNode *createThenNodeAtribute(const QPointF &pos);
    SCgNode *createElseNodeAtribute(const QPointF &pos);

private slots:
    void onTemplateChanged(SCgScene::Template templ);
private:
    int ghostsetVisibleClickCount;

    QVector<SCgObject*> switchTemplate(SCgScene::Template templ);



protected:
    //! Inserted objects
    QGraphicsItemGroup* mInsertedObjectGroup;


};

#endif // SCGTEMPLATEMODE_H
