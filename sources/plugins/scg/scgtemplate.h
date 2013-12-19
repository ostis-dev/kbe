#ifndef SCGTEMPLATE_H
#define SCGTEMPLATE_H

#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

#include "scgscene.h"
#include "scgnode.h"
#include "scgpair.h"
#include "vector"


class SCgTemplate
{
public:
    SCgTemplate(SCgScene *mScene);

    QVector<SCgObject *> createGenElTemplate(const QPointF &pos);
    QVector<SCgObject *> createGenElStr3Template(const QPointF &pos);
    QVector<SCgObject *> createGenElStr5Template(const QPointF &pos);
    QVector<SCgObject *> createProgramSCPTempale(const QPointF &pos);
    QVector<SCgObject *> createPrintElTemplate(const QPointF &pos);
    SCgPair *createPairWithVariableNode(const QPointF &pos, SCgObject *begObj, QVector<SCgObject *> &graphicItem);
    SCgBus *createGroupConstruct(const QString &idtf, const QPointF &pos, QVector<SCgObject *> &graphicItem);
    QVector<SCgObject *> createPrintNlTemplate(const QPointF &pos);
    QVector<SCgObject *> createPrintTemplate(const QPointF &pos);
    QVector<SCgObject *> createifTypeTemplate(const QPointF &pos);
    QVector<SCgObject *> createifEqTemplate(const QPointF &pos);
    SCgPair *createPairForGhostAtribute(SCgObject *begObj, SCgObject *endObj, QVector<SCgObject *> &graphicItem);
    QVector<SCgObject *> createifCoinTemplate(const QPointF &pos);
    SCgPair *createPairWithVariableNode(const QPointF &pos, SCgObject *begObj, float pairBeginDot, QVector<SCgObject *> &graphicItem);
    SCgPair *createPairForGhostAtribute(SCgObject *begObj, SCgObject *endObj, float pairEndDot, QVector<SCgObject *> &graphicItem);
    QVector<SCgObject *> createifGrTemplate(const QPointF &pos);
    QVector<SCgObject *> createSearchElStr3Template(const QPointF &pos);
    QVector<SCgObject *> createSearchElStr5Template(const QPointF &pos);
    QVector<SCgObject *> createSearchSetStr3Template(const QPointF &pos);
    QVector<SCgObject *> createSearchSetStr5Template(const QPointF &pos);
    QVector<SCgObject *> createToStrTemplate(const QPointF &pos);
    QVector<SCgObject *> createACosTemplate(const QPointF &pos);
    QVector<SCgObject *> createCosTemplate(const QPointF &pos);
    QVector<SCgObject *> createASinTemplate(const QPointF &pos);
    QVector<SCgObject *> createSinTemplate(const QPointF &pos);
    QVector<SCgObject *> createReturnTemplate(const QPointF &pos);
    QVector<SCgObject *> createCallReturnTemplate(const QPointF &pos);
    QVector<SCgObject *> createPowTemplate(const QPointF &pos);
    QVector<SCgObject *> createDivTemplate(const QPointF &pos);
    QVector<SCgObject *> createMultTemplate(const QPointF &pos);
    QVector<SCgObject *> createSubTemplate(const QPointF &pos);
    QVector<SCgObject *> createAddTemplate(const QPointF &pos);
    QVector<SCgObject *> createEraseElStr3Template(const QPointF &pos);
    QVector<SCgObject *> createEraseElStr5Template(const QPointF &pos);
    QVector<SCgObject *> createEraseElTemplate(const QPointF &pos);
private:
    SCgNode *createNodeForGhostAtribute(const QString &idtf,
                                        const QPointF &pos,
                                        QVector<SCgObject *> &graphicItem);

    SCgPair *createPairForGhostAtribute(SCgObject *begObj,
                                        SCgObject *endObj,
                                        const QVector<QPointF> &points,
                                        QVector<SCgObject *> &graphicItem);
private:
    SCgScene *mScene;

    float pairPos;
};

#endif // SCGTEMPLATE_H
