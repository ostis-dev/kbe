#include "scgtemplate.h"
//#include "scgscene.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgpair.h"

#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

SCgTemplate::SCgTemplate(SCgScene *mScene)
    :mScene(mScene)
{
}

QVector<SCgObject*> SCgTemplate::createGenElTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("genEl", pos, graphicItem);

    SCgPair *pair = createPairWithVariableNode(QPointF(pos.x()+200, pos.y() + 110), bus, .3f, graphicItem);


    SCgNode *nodeArg = createNodeForGhostAtribute("node_", QPointF(pos.x()+55,pos.y()+140), graphicItem);
    createPairForGhostAtribute(nodeArg, pair, .31f, graphicItem);

    SCgNode *arcArg = createNodeForGhostAtribute("arc_", QPointF(pos.x()+81,pos.y()+150), graphicItem);
    createPairForGhostAtribute(arcArg, pair, .44f, graphicItem);


    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x() + 107, pos.y()+160), graphicItem);
    createPairForGhostAtribute(constArg, pair, .57f, graphicItem);


    SCgNode *varArg = createNodeForGhostAtribute("var_", QPointF(pos.x() + 130,pos.y()+170), graphicItem);
    createPairForGhostAtribute(varArg, pair, .7f, graphicItem);


    SCgNode *posArg = createNodeForGhostAtribute("pos_", QPointF(pos.x()+155, pos.y()+180), graphicItem);
    createPairForGhostAtribute(posArg, pair, .83f, graphicItem);

    SCgNode *negArg = createNodeForGhostAtribute("neg_", QPointF(pos.x()+181,pos.y()+190), graphicItem);
    createPairForGhostAtribute(negArg, pair, .96f, graphicItem);

    graphicItem.push_back(pair);
    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createGenElStr3Template(const QPointF &pos)
{

     SCgBus *bus = createGroupConstruct("genElStr3", pos, graphicItem);
     bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

     SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
     SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);
     SCgPair *variablePair3 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 260), bus, .62f, graphicItem);


     SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+119,pos.y()+122), graphicItem);
     createPairForGhostAtribute(fixedArg, variablePair1, .35f, graphicItem);

     SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+180,pos.y()+122), graphicItem);
     createPairForGhostAtribute(assignArg, variablePair1, .7f, graphicItem);

    //--------------------------------------------------------------------------------------------------------

     SCgNode *fixedArg2 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+186), graphicItem);
     createPairForGhostAtribute(fixedArg2, variablePair2, .2f, graphicItem);

     SCgNode *assignArg2 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+86,pos.y()+199), graphicItem);
     createPairForGhostAtribute(assignArg2, variablePair2, .3f, graphicItem);

     SCgNode *nodeArg = createNodeForGhostAtribute("node_", QPointF(pos.x()+111,pos.y()+212), graphicItem);
     createPairForGhostAtribute(nodeArg, variablePair2, .38f, graphicItem);


     SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+136,pos.y()+224), graphicItem);
     createPairForGhostAtribute(constArg, variablePair2, .47f, graphicItem);


     SCgNode *varArg = createNodeForGhostAtribute("var_", QPointF(pos.x() + 201,pos.y()+198), graphicItem);
     createPairForGhostAtribute(varArg, variablePair2, .7f, graphicItem);


     SCgNode *posArg = createNodeForGhostAtribute("pos_", QPointF(pos.x()+225, pos.y()+210), graphicItem);
     createPairForGhostAtribute(posArg, variablePair2, .78f, graphicItem);

     SCgNode *negArg = createNodeForGhostAtribute("neg_", QPointF(pos.x()+251,pos.y()+224), graphicItem);
     createPairForGhostAtribute(negArg, variablePair2, .87f, graphicItem);

     //-------------------------------------------------------------------------------------------------------

     SCgNode *fixedArg3 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+58,pos.y()+291), graphicItem);
     createPairForGhostAtribute(fixedArg3, variablePair3, .2f, graphicItem);

     SCgNode *assignArg3 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+84,pos.y()+308), graphicItem);
     createPairForGhostAtribute(assignArg3, variablePair3, .3f, graphicItem);

     SCgNode *nodeArg3 = createNodeForGhostAtribute("node_", QPointF(pos.x()+109,pos.y()+324), graphicItem);
     createPairForGhostAtribute(nodeArg3, variablePair3, .38f, graphicItem);


     SCgNode *constArg3 = createNodeForGhostAtribute("const_", QPointF(pos.x()+138,pos.y()+340), graphicItem);
     createPairForGhostAtribute(constArg3, variablePair3, .48f, graphicItem);


     SCgNode *varArg3 = createNodeForGhostAtribute("var_", QPointF(pos.x() + 189,pos.y()+297), graphicItem);
     createPairForGhostAtribute(varArg3, variablePair3, .65f, graphicItem);


     SCgNode *posArg3 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+213, pos.y()+314), graphicItem);
     createPairForGhostAtribute(posArg3, variablePair3, .75f, graphicItem);

     SCgNode *negArg3 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+240,pos.y()+329), graphicItem);
     createPairForGhostAtribute(negArg3, variablePair3, .83f, graphicItem);

     SCgNode *arcArg3 = createNodeForGhostAtribute("arc_", QPointF(pos.x()+263,pos.y()+342), graphicItem);
     createPairForGhostAtribute(arcArg3, variablePair3, .91f, graphicItem);


     graphicItem.push_back(bus);

     return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createGenElStr5Template(const QPointF &pos)
{
     graphicItem = createGenElStr3Template(pos);

     graphicItem.at(0)->setIdtfValue("genElStr5");
     static_cast<SCgPair *>(graphicItem.at(6))->setBeginDot(.16f);
     static_cast<SCgPair *>(graphicItem.at(8))->setBeginDot(.36f);

     SCgBus *bus = static_cast<SCgBus*>(graphicItem.last());
     bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

     SCgPair *variablePair4 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 383), bus, .60f, graphicItem);
     SCgPair *variablePair5 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 500), bus, .85f, graphicItem);

     SCgNode *fixedArg3 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+58,pos.y()+414), graphicItem);
     createPairForGhostAtribute(fixedArg3, variablePair4, .2f, graphicItem);

     SCgNode *assignArg3 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+84,pos.y()+431), graphicItem);
     createPairForGhostAtribute(assignArg3, variablePair4, .3f, graphicItem);

     SCgNode *nodeArg3 = createNodeForGhostAtribute("node_", QPointF(pos.x()+109,pos.y()+447), graphicItem);
     createPairForGhostAtribute(nodeArg3, variablePair4, .38f, graphicItem);


     SCgNode *constArg3 = createNodeForGhostAtribute("const_", QPointF(pos.x()+138,pos.y()+463), graphicItem);
     createPairForGhostAtribute(constArg3, variablePair4, .48f, graphicItem);


     SCgNode *varArg3 = createNodeForGhostAtribute("var_", QPointF(pos.x() + 189,pos.y()+420), graphicItem);
     createPairForGhostAtribute(varArg3, variablePair4, .65f, graphicItem);


     SCgNode *posArg3 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+213, pos.y()+437), graphicItem);
     createPairForGhostAtribute(posArg3, variablePair4, .75f, graphicItem);

     SCgNode *negArg3 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+240,pos.y()+452), graphicItem);
     createPairForGhostAtribute(negArg3, variablePair4, .83f, graphicItem);

     SCgNode *arcArg3 = createNodeForGhostAtribute("arc_", QPointF(pos.x()+263,pos.y()+470), graphicItem);
     createPairForGhostAtribute(arcArg3, variablePair4, .91f, graphicItem);

     //----------------------------------------------------------------------------------------------------

     SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+119,pos.y()+550), graphicItem);
     createPairForGhostAtribute(fixedArg, variablePair5, .35f, graphicItem);

     SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+180,pos.y()+550), graphicItem);
     createPairForGhostAtribute(assignArg, variablePair5, .7f, graphicItem);

     return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createSearchElStr3Template(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("searchElStr3", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
    SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);
    SCgPair *variablePair3 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 228), bus, .50f, graphicItem);

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+40,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .14f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+85,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .30f, graphicItem);

    SCgNode *vardArg = createNodeForGhostAtribute("var_", QPointF(pos.x()+134,pos.y()+124), graphicItem);
    vardArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg, variablePair1, .45f, graphicItem);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+182,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .63f, graphicItem);

    //--------------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg2 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+28,pos.y()+187), graphicItem);
    fixedArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg2, variablePair2, .08f, graphicItem);

    SCgNode *assignArg2 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+69,pos.y()+187), graphicItem);
    assignArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg2, variablePair2, .23, graphicItem);

    SCgNode *vardArg2 = createNodeForGhostAtribute("var_", QPointF(pos.x()+123,pos.y()+187), graphicItem);
    vardArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg2, variablePair2, .4f, graphicItem);

    SCgNode *constArg2 = createNodeForGhostAtribute("const_", QPointF(pos.x()+156,pos.y()+187), graphicItem);
    constArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg2, variablePair2, .56f, graphicItem);

    SCgNode *posArg2 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+193,pos.y()+187), graphicItem);
    posArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(posArg2, variablePair2, .73f, graphicItem);

    SCgNode *negArg2 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+231,pos.y()+187), graphicItem);
    negArg2->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(negArg2, variablePair2, .89f, graphicItem);

    //----------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg3 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+266), graphicItem);
    createPairForGhostAtribute(fixedArg3, variablePair3, .2f, graphicItem);

    SCgNode *assignArg3 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+83,pos.y()+280), graphicItem);
    createPairForGhostAtribute(assignArg3, variablePair3, .28, graphicItem);

    SCgNode *vardArg3 = createNodeForGhostAtribute("var_", QPointF(pos.x()+106,pos.y()+295), graphicItem);
    createPairForGhostAtribute(vardArg3, variablePair3, .36f, graphicItem);

    SCgNode *constArg3 = createNodeForGhostAtribute("const_", QPointF(pos.x()+129,pos.y()+310), graphicItem);
    createPairForGhostAtribute(constArg3, variablePair3, .45f, graphicItem);

    SCgNode *posArg3 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+190,pos.y()+266), graphicItem);
    createPairForGhostAtribute(posArg3, variablePair3, .66f, graphicItem);

    SCgNode *negArg3 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+215,pos.y()+280), graphicItem);
    createPairForGhostAtribute(negArg3, variablePair3, .73f, graphicItem);

    SCgNode *nodeArg3 = createNodeForGhostAtribute("node_", QPointF(pos.x()+238,pos.y()+294), graphicItem);
    createPairForGhostAtribute(nodeArg3, variablePair3, .83f, graphicItem);

    SCgNode *arcArg3 = createNodeForGhostAtribute("arc_", QPointF(pos.x()+262,pos.y()+308), graphicItem);
    createPairForGhostAtribute(arcArg3, variablePair3, .91f, graphicItem);

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createSearchElStr5Template(const QPointF &pos)
{
    graphicItem = createSearchElStr3Template(pos);

    graphicItem.at(0)->setIdtfValue("searchElStr5");
    static_cast<SCgPair *>(graphicItem.at(6))->setBeginDot(.16f);
    static_cast<SCgPair *>(graphicItem.at(8))->setBeginDot(.31f);

    SCgBus *bus = static_cast<SCgBus*>(graphicItem.last());
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair4 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 375), bus, .60f, graphicItem);
    SCgPair *variablePair5 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 496), bus, .85f, graphicItem);

    //--------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg4 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+40,pos.y()+426), graphicItem);
    fixedArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg4, variablePair4, .13f, graphicItem);

    SCgNode *assignArg4 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+87,pos.y()+426), graphicItem);
    assignArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg4, variablePair4, .29f, graphicItem);

    SCgNode *vardArg4 = createNodeForGhostAtribute("var_", QPointF(pos.x()+137,pos.y()+426), graphicItem);
    vardArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg4, variablePair4, .47f, graphicItem);

    SCgNode *constArg4 = createNodeForGhostAtribute("const_", QPointF(pos.x()+182,pos.y()+426), graphicItem);
    constArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg4, variablePair4, .62f, graphicItem);

    //-----------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg5 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+23,pos.y()+540), graphicItem);
    fixedArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg5, variablePair5, .08f, graphicItem);

    SCgNode *assignArg5 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+67,pos.y()+540), graphicItem);
    assignArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg5, variablePair5, .23, graphicItem);

    SCgNode *vardArg5 = createNodeForGhostAtribute("var_", QPointF(pos.x()+115,pos.y()+540), graphicItem);
    vardArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg5, variablePair5, .4f, graphicItem);

    SCgNode *constArg5 = createNodeForGhostAtribute("const_", QPointF(pos.x()+162,pos.y()+540), graphicItem);
    constArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg5, variablePair5, .56f, graphicItem);

    SCgNode *posArg5 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+212,pos.y()+540), graphicItem);
    posArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(posArg5, variablePair5, .73f, graphicItem);

    SCgNode *negArg5 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+258,pos.y()+540), graphicItem);
    negArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(negArg5, variablePair5, .89f, graphicItem);

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createEraseElTemplate(const QPointF &pos)
{
    SCgBus *bus = createGroupConstruct("eraseEl", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+40,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .14f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("f_", QPointF(pos.x()+85,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .30f, graphicItem);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createEraseElStr3Template(const QPointF &pos)
{
    SCgBus *bus = createGroupConstruct("eraseElStr3", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
    SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);
    SCgPair *variablePair3 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 228), bus, .50f, graphicItem);

    //------------------------------------------------------------------------

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+40,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .14f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+85,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .30f, graphicItem);

    SCgNode *assignArgForf = createNodeForGhostAtribute("f_", QPointF(pos.x()+125,pos.y()+124), graphicItem);
    assignArgForf->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArgForf, variablePair1, .45f, graphicItem);

    //-------------------------------------------------------------------------

    SCgNode *fixedArg5 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+23,pos.y()+180), graphicItem);
    fixedArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg5, variablePair2, .08f, graphicItem);

    SCgNode *assignArg5 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+67,pos.y()+180), graphicItem);
    assignArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg5, variablePair2, .23, graphicItem);

    SCgNode *vardArg5 = createNodeForGhostAtribute("var_", QPointF(pos.x()+115,pos.y()+180), graphicItem);
    vardArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg5, variablePair2, .4f, graphicItem);

    SCgNode *constArg5 = createNodeForGhostAtribute("const_", QPointF(pos.x()+162,pos.y()+180), graphicItem);
    constArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg5, variablePair2, .56f, graphicItem);

    SCgNode *posArg5 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+212,pos.y()+180), graphicItem);
    posArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(posArg5, variablePair2, .73f, graphicItem);

    SCgNode *fArg5 = createNodeForGhostAtribute("f_", QPointF(pos.x()+258,pos.y()+180), graphicItem);
    fArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fArg5, variablePair2, .89f, graphicItem);

    //---------------------------------------------------------------------------

    SCgNode *fixedArg3 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+266), graphicItem);
    createPairForGhostAtribute(fixedArg3, variablePair3, .2f, graphicItem);

    SCgNode *assignArg3 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+83,pos.y()+280), graphicItem);
    createPairForGhostAtribute(assignArg3, variablePair3, .28, graphicItem);

    SCgNode *vardArg3 = createNodeForGhostAtribute("node_", QPointF(pos.x()+106,pos.y()+295), graphicItem);
    createPairForGhostAtribute(vardArg3, variablePair3, .36f, graphicItem);

    SCgNode *constArg3 = createNodeForGhostAtribute("const_", QPointF(pos.x()+129,pos.y()+310), graphicItem);
    createPairForGhostAtribute(constArg3, variablePair3, .45f, graphicItem);

    SCgNode *posArg3 = createNodeForGhostAtribute("arc_", QPointF(pos.x()+190,pos.y()+266), graphicItem);
    createPairForGhostAtribute(posArg3, variablePair3, .66f, graphicItem);

    SCgNode *negArg3 = createNodeForGhostAtribute("f_", QPointF(pos.x()+215,pos.y()+280), graphicItem);
    createPairForGhostAtribute(negArg3, variablePair3, .73f, graphicItem);

    graphicItem.push_back(bus);
    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createEraseElStr5Template(const QPointF &pos)
{
    graphicItem = createEraseElStr3Template(pos);

    graphicItem.at(0)->setIdtfValue("eraseElStr5");
    static_cast<SCgPair *>(graphicItem.at(6))->setBeginDot(.16f);
    static_cast<SCgPair *>(graphicItem.at(8))->setBeginDot(.31f);

    SCgBus *bus = static_cast<SCgBus*>(graphicItem.last());
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair4 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 375), bus, .60f, graphicItem);
    SCgPair *variablePair5 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 496), bus, .85f, graphicItem);

    //--------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg4 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+40,pos.y()+426), graphicItem);
    fixedArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg4, variablePair4, .13f, graphicItem);

    SCgNode *assignArg4 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+87,pos.y()+426), graphicItem);
    assignArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg4, variablePair4, .29f, graphicItem);

    SCgNode *vardArg4 = createNodeForGhostAtribute("var_", QPointF(pos.x()+137,pos.y()+426), graphicItem);
    vardArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg4, variablePair4, .47f, graphicItem);

    SCgNode *constArg4 = createNodeForGhostAtribute("const_", QPointF(pos.x()+182,pos.y()+426), graphicItem);
    constArg4->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg4, variablePair4, .62f, graphicItem);

    //-----------------------------------------------------------------------------------------------------------

    SCgNode *fixedArg5 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+23,pos.y()+540), graphicItem);
    fixedArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg5, variablePair5, .08f, graphicItem);

    SCgNode *assignArg5 = createNodeForGhostAtribute("assign_", QPointF(pos.x()+67,pos.y()+540), graphicItem);
    assignArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg5, variablePair5, .23, graphicItem);

    SCgNode *vardArg5 = createNodeForGhostAtribute("var_", QPointF(pos.x()+115,pos.y()+540), graphicItem);
    vardArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(vardArg5, variablePair5, .4f, graphicItem);

    SCgNode *constArg5 = createNodeForGhostAtribute("const_", QPointF(pos.x()+162,pos.y()+540), graphicItem);
    constArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg5, variablePair5, .56f, graphicItem);

    SCgNode *posArg5 = createNodeForGhostAtribute("pos_", QPointF(pos.x()+212,pos.y()+540), graphicItem);
    posArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(posArg5, variablePair5, .73f, graphicItem);

    SCgNode *negArg5 = createNodeForGhostAtribute("neg_", QPointF(pos.x()+258,pos.y()+540), graphicItem);
    negArg5->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(negArg5, variablePair5, .89f, graphicItem);

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createSearchSetStr3Template(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("searchSetStr3", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createSearchSetStr5Template(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("searchSetStr5", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    graphicItem.push_back(bus);

    return graphicItem;
}


QVector<SCgObject*> SCgTemplate::createProgramSCPTempale(const QPointF &pos)
{
    SCgNode *groupNode = new SCgNode();
    groupNode->setIdtfValue("scp-procedure");
    groupNode->setIdtfPos(SCgNode::TopRight);
    groupNode->setPos(pos);
    groupNode->setTypeAlias("node/const/group");
    groupNode->flags();

    mScene->addItem(groupNode);

    SCgNode *generalNode = mScene->createSCgNode(QPointF(pos.x(),pos.y()+70));

    QVector<QPointF> pointGroup;
    pointGroup.push_back(pos);
    pointGroup.push_back(QPointF(pos.x(),pos.y()+70));

    SCgPair *groupTuplePair = mScene->createSCgPair(groupNode,generalNode,pointGroup);

    QVector<QPointF> forBus;
    forBus.push_back(QPointF(pos.x(),pos.y()));
    forBus.push_back(QPointF(pos.x()+170,pos.y()+70));

    SCgBus *bus = mScene->createSCgBus(forBus,generalNode);

    SCgNode *generalNodeTwo = mScene->createSCgNode(QPointF(pos.x()+95,pos.y()+200));

    QVector<QPointF> forPair;
    forPair.push_back(bus->pos());
    forPair.push_back(generalNode->pos());

    SCgPair *groupGeneralNodeWithBus = mScene->createSCgPair(bus,generalNodeTwo,forPair);
    groupGeneralNodeWithBus->setBeginDot(.50);

    SCgNode *roleNodeForParam = new SCgNode();
    roleNodeForParam->setIdtfValue("param_");
    roleNodeForParam->setIdtfPos(SCgNode::TopRight);
    roleNodeForParam->setPos(QPointF(generalNode->pos().x() + 30, generalNode->pos().y() + 70));
    roleNodeForParam->setTypeAlias("node/const/role");
    mScene->addItem(roleNodeForParam);

    QVector<QPointF> forPairRoleNodeWithParamPair;
    forPair.push_back(roleNodeForParam->pos());
    forPair.push_back(groupGeneralNodeWithBus->pos());

    SCgPair *groupRoleNodeWithParamPair = mScene->createSCgPair(roleNodeForParam, groupGeneralNodeWithBus,forPairRoleNodeWithParamPair);
    groupRoleNodeWithParamPair->setEndDot(.6);

    SCgNode *varGeneral = mScene->createSCgNode(QPointF(pos.x()+95,pos.y()+250));
    varGeneral->setTypeAlias("node/var/general");
    varGeneral->setIdtfValue("_parameter");

    QVector<QPointF> forPairGeneralNodeWithGeneralVar;
    forPair.push_back(generalNodeTwo->pos());
    forPair.push_back(varGeneral->pos());

    SCgPair *groupGeneralNodeWithGeneralVar = mScene->createSCgPair(generalNodeTwo,varGeneral,forPairGeneralNodeWithGeneralVar);

    SCgNode *generalNodeTwo2 = mScene->createSCgNode(QPointF(pos.x()+134,pos.y()+200));

    QVector<QPointF> forPair2;
    forPair.push_back(bus->pos());
    forPair.push_back(generalNode->pos());

    SCgPair *groupGeneralNodeWithBus2 = mScene->createSCgPair(bus,generalNodeTwo2,forPair2);
    groupGeneralNodeWithBus2->setBeginDot(.80);

    SCgNode *roleNodeForParam2 = new SCgNode();
    roleNodeForParam2->setIdtfValue("operators_");
    roleNodeForParam2->setIdtfPos(SCgNode::TopRight);
    roleNodeForParam2->setPos(QPointF(generalNode->pos().x() + 170, generalNode->pos().y() + 70));
    roleNodeForParam2->setTypeAlias("node/const/role");
    mScene->addItem(roleNodeForParam2);

    QVector<QPointF> forPairRoleNodeWithParamPair2;
    forPair.push_back(roleNodeForParam2->pos());
    forPair.push_back(groupGeneralNodeWithBus2->pos());

    SCgPair *groupRoleNodeWithParamPair2 = mScene->createSCgPair(roleNodeForParam2, groupGeneralNodeWithBus2,forPairRoleNodeWithParamPair2);
    groupRoleNodeWithParamPair2->setEndDot(.6);


    graphicItem.push_back(groupNode);
    graphicItem.push_back(generalNode);
    graphicItem.push_back(bus);
    graphicItem.push_back(generalNodeTwo);
    graphicItem.push_back(generalNodeTwo2);
    graphicItem.push_back(groupGeneralNodeWithBus);
    graphicItem.push_back(groupRoleNodeWithParamPair);
    graphicItem.push_back(groupGeneralNodeWithGeneralVar);
    graphicItem.push_back(groupGeneralNodeWithBus2);
    graphicItem.push_back(groupRoleNodeWithParamPair2);
    graphicItem.push_back(varGeneral);
    graphicItem.push_back(groupTuplePair);
    graphicItem.push_back(roleNodeForParam);
    graphicItem.push_back(roleNodeForParam2);



    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createPrintElTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("printEl", pos, graphicItem);

    SCgPair *pair = createPairWithVariableNode(pos,bus,graphicItem);

    QVector<QPointF> forPair;
    forPair.push_back(bus->pos());
    forPair.push_back(pair->pos());

    SCgNode *nodeGhostFixed = createNodeForGhostAtribute("fixed_",QPointF(pos.x()+60,pos.y()+140),graphicItem);
    createPairForGhostAtribute(nodeGhostFixed, pair, forPair, graphicItem);

    SCgNode *nodeGhostVariable = createNodeForGhostAtribute("variable_",QPointF(pos.x()+90,pos.y()+160),graphicItem);
    createPairForGhostAtribute(nodeGhostVariable, pair, forPair, graphicItem);

    graphicItem.push_back(bus);
    graphicItem.push_back(pair);
    graphicItem.push_back(nodeGhostFixed);
    graphicItem.push_back(nodeGhostVariable);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createPrintNlTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("printNl", pos, graphicItem);

    SCgPair *pair = createPairWithVariableNode(pos,bus,graphicItem);

    QVector<QPointF> forPair;
    forPair.push_back(bus->pos());
    forPair.push_back(pair->pos());

    SCgNode *nodeGhostFixed = createNodeForGhostAtribute("fixed_",QPointF(pos.x()+60,pos.y()+140),graphicItem);
    createPairForGhostAtribute(nodeGhostFixed, pair, forPair, graphicItem);

    SCgNode *nodeGhostVariable = createNodeForGhostAtribute("constant_",QPointF(pos.x()+90,pos.y()+160),graphicItem);
    createPairForGhostAtribute(nodeGhostVariable, pair, forPair, graphicItem);

    graphicItem.push_back(bus);
    graphicItem.push_back(pair);
    graphicItem.push_back(nodeGhostFixed);
    graphicItem.push_back(nodeGhostVariable);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createPrintTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("print", pos, graphicItem);

    SCgPair *pair = createPairWithVariableNode(pos,bus,graphicItem);

    graphicItem.push_back(bus);
    graphicItem.push_back(pair);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createifTypeTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("ifType", pos, graphicItem);

    SCgPair *pair = createPairWithVariableNode(pos,bus,graphicItem);

    QVector<QPointF> forPair;
    forPair.push_back(bus->pos());
    forPair.push_back(pair->pos());

    SCgNode *nodeGhostFixed = createNodeForGhostAtribute("fixed_",QPointF(pos.x()+60,pos.y()+140),graphicItem);
    createPairForGhostAtribute(nodeGhostFixed, pair, forPair, graphicItem);

    SCgNode *nodeGhostNode = createNodeForGhostAtribute("node_",QPointF(pos.x()+85,pos.y()+160),graphicItem);
    createPairForGhostAtribute(nodeGhostNode, pair, forPair, graphicItem);

    SCgNode *nodeGhostArc = createNodeForGhostAtribute("arc_",QPointF(pos.x()+110,pos.y()+180),graphicItem);
    createPairForGhostAtribute(nodeGhostArc, pair, forPair, graphicItem);

    SCgNode *nodeGhostConst = createNodeForGhostAtribute("const_",QPointF(pos.x()+135,pos.y()+200),graphicItem);
    createPairForGhostAtribute(nodeGhostConst, pair, forPair, graphicItem);

    graphicItem.push_back(bus);
    graphicItem.push_back(pair);
    graphicItem.push_back(nodeGhostFixed);
    graphicItem.push_back(nodeGhostNode);
    graphicItem.push_back(nodeGhostArc);
    graphicItem.push_back(nodeGhostConst);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createifEqTemplate(const QPointF &pos)
{
    SCgBus *bus = createGroupConstruct("ifEq", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
    SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+119,pos.y()+122), graphicItem);
    createPairForGhostAtribute(fixedArg, variablePair1, .35f, graphicItem);

    SCgNode *fixedArg2 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+186), graphicItem);
    createPairForGhostAtribute(fixedArg2, variablePair2, .2f, graphicItem);

    graphicItem.push_back(bus);
    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createifCoinTemplate(const QPointF &pos)
{
    SCgBus *bus = createGroupConstruct("ifCoin", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
    SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+119,pos.y()+122), graphicItem);
    createPairForGhostAtribute(fixedArg, variablePair1, .35f, graphicItem);

    SCgNode *fixedArg2 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+186), graphicItem);
    createPairForGhostAtribute(fixedArg2, variablePair2, .2f, graphicItem);

    graphicItem.push_back(bus);
    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createifGrTemplate(const QPointF &pos)
{
    SCgBus *bus = createGroupConstruct("ifGr", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 94), bus, .03f, graphicItem);
    SCgPair *variablePair2 = createPairWithVariableNode(QPointF(pos.x()+300, pos.y() + 157), bus, .25f, graphicItem);

    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+119,pos.y()+122), graphicItem);
    createPairForGhostAtribute(fixedArg, variablePair1, .35f, graphicItem);

    SCgNode *fixedArg2 = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+60,pos.y()+186), graphicItem);
    createPairForGhostAtribute(fixedArg2, variablePair2, .2f, graphicItem);

    graphicItem.push_back(bus);
    return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createAddTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Add", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 100));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 95), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 170), bus, .45f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 260), bus, .95f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}



QVector<SCgObject *> SCgTemplate::createSubTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Sub", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 100));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 95), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 170), bus, .45f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 260), bus, .95f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createMultTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Mult", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 100));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 95), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 170), bus, .45f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 260), bus, .95f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createDivTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Div", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 100));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 95), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 170), bus, .45f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 260), bus, .95f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createPowTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Pow", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 100));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 95), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 170), bus, .45f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 260), bus, .95f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}


QVector<SCgObject *> SCgTemplate::createCallReturnTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("callReturn", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createReturnTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Return", pos, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
 //   bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 200));

    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createSinTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Sin", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 50));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 200), bus, .85f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createASinTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("ASin", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 50));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 200), bus, .85f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createCosTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("Cos", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 50));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 200), bus, .85f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createACosTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("ACon", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 50));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 200), bus, .85f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}

QVector<SCgObject *> SCgTemplate::createToStrTemplate(const QPointF &pos)
{

    SCgBus *bus = createGroupConstruct("toStr", pos, graphicItem);
    bus->changePointPosition(1, QPointF(bus->pointAt(1).x(), bus->pointAt(1).y() + 50));

    SCgPair *variablePair1 = createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 92), bus, .05f, graphicItem);
    createPairWithVariableNode(QPointF(pos.x()+150, pos.y() + 200), bus, .85f, graphicItem);

   //var 1---------------------------------
    SCgNode *fixedArg = createNodeForGhostAtribute("fixed_", QPointF(pos.x()+20,pos.y()+124), graphicItem);
    fixedArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(fixedArg, variablePair1, .15f, graphicItem);

    SCgNode *assignArg = createNodeForGhostAtribute("assign_", QPointF(pos.x()+70,pos.y()+124), graphicItem);
    assignArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(assignArg, variablePair1, .55f, graphicItem);
    graphicItem.push_back(bus);

    SCgNode *constArg = createNodeForGhostAtribute("const_", QPointF(pos.x()+120,pos.y()+124), graphicItem);
    constArg->setIdtfPos(SCgNode::BottomRight);
    createPairForGhostAtribute(constArg, variablePair1, .85f, graphicItem);
    graphicItem.push_back(bus);

    return graphicItem;
}

SCgNode *SCgTemplate::createNodeForGhostAtribute(const QString &idtf, const QPointF &pos, QVector<SCgObject*> &graphicItem)
{
    SCgNode *node = mScene->createSCgNode(pos);

    node->setIdtfValue(idtf);
    node->setIdtfPos(SCgNode::BottomLeft);
    node->setTypeAlias("node/const/role");
    node->setOpacity(.0f);
    node->setGhost(true);
    graphicItem.push_back(node);

    return node;
}

SCgPair *SCgTemplate::createPairForGhostAtribute(SCgObject *begObj, SCgObject *endObj, const QVector<QPointF> &points, QVector<SCgObject *> &graphicItem)
{
    SCgPair *pair = mScene->createSCgPair(begObj, endObj, points);

    pair->setEndDot(pairPos += .13f);
    pair->setOpacity(.0f);

    graphicItem.push_back(pair);

    return pair;
}

SCgBus* SCgTemplate::createGroupConstruct(const QString &idtf, const QPointF &pos, QVector<SCgObject *> &graphicItem)
{
    SCgNode *groupNode = new SCgNode();
    groupNode->setIdtfValue(idtf);
    groupNode->setIdtfPos(SCgNode::TopRight);
    groupNode->setPos(pos);
    groupNode->setTypeAlias("node/const/group");
    groupNode->flags();

    mScene->addItem(groupNode);

    SCgNode *tupleNode = new SCgNode;
    tupleNode->setPos(QPointF(pos.x(),pos.y()+70));
    tupleNode->setTypeAlias("node/const/tuple");
    mScene->addItem(tupleNode);

    QVector<QPointF> pointGroup;
    pointGroup.push_back(pos);
    pointGroup.push_back(QPointF(pos.x(),pos.y()+70));

    SCgPair *groupTuplePair = mScene->createSCgPair(groupNode,tupleNode,pointGroup);

    QVector<QPointF> forBus;
    forBus.push_back(QPointF(pos.x(),pos.y()+70));
    forBus.push_back(QPointF(pos.x(),pos.y()+170));

    graphicItem.push_back(groupNode);
    graphicItem.push_back(tupleNode);
    graphicItem.push_back(groupTuplePair);

    return mScene->createSCgBus(forBus,tupleNode);
}

SCgPair *SCgTemplate::createPairWithVariableNode(const QPointF &pos,SCgObject *begObj, QVector<SCgObject *> &graphicItem)
{
    SCgNode *variableNode = mScene->createSCgNode(QPointF(pos.x()+200,pos.y()+100));

    QVector<QPointF> forPair;
        forPair.push_back(begObj->pos());
        forPair.push_back(variableNode->pos());

    SCgPair *busVariablePair = mScene->createSCgPair(begObj, variableNode, forPair);
    busVariablePair->setBeginDot(pairPos += .2);

    graphicItem.push_back(variableNode);
    graphicItem.push_back(busVariablePair);

    return busVariablePair;
}

SCgPair *SCgTemplate::createPairWithVariableNode(const QPointF &pos,
                                                  SCgObject *begObj,
                                                  float pairBeginDot,
                                                  QVector<SCgObject *> &graphicItem)
 {
     SCgNode *variableNode = mScene->createSCgNode(pos);

     QVector<QPointF> forPair;
         forPair.push_back(begObj->pos());
         forPair.push_back(variableNode->pos());

     SCgPair *busVariablePair = mScene->createSCgPair(begObj, variableNode, forPair);
     busVariablePair->setBeginDot(pairBeginDot);

     graphicItem.push_back(variableNode);
     graphicItem.push_back(busVariablePair);

     return busVariablePair;
 }

SCgPair *SCgTemplate::createPairForGhostAtribute(SCgObject *begObj, SCgObject *endObj, float pairEndDot, QVector<SCgObject *> &graphicItem)
{
    QVector<QPointF> points;
    points.push_back(begObj->pos());
    points.push_back(begObj->pos());
    SCgPair *pair = mScene->createSCgPair(begObj, endObj, points);

    pair->setEndDot(pairEndDot);
    pair->setOpacity(.25f);
    pair->setVisible(false);
    graphicItem.push_back(pair);

    return pair;
}

void SCgTemplate::expandTemplate(QString nodeValue, QGraphicsSceneMouseEvent *event)
{
    if(nodeValue == "genEl")
        createGenElTemplate(event->scenePos());
    if(nodeValue == "eraseEl")
        createEraseElTemplate(event->scenePos());
    if(nodeValue == "genElStr3")
        createGenElStr3Template(event->scenePos());
    if(nodeValue == "genElStr5")
        createGenElStr5Template(event->scenePos());
    if(nodeValue == "searchElStr3")
        createSearchElStr3Template(event->scenePos());
    if(nodeValue == "searchElStr5")
        createSearchElStr5Template(event->scenePos());
    if(nodeValue == "eraseElStr3")
        createEraseElStr3Template(event->scenePos());
    if(nodeValue == "eraseElStr5")
        createEraseElStr5Template(event->scenePos());
    if(nodeValue == "searchSetStr3")
        createSearchElStr3Template(event->scenePos());
    if(nodeValue == "searchSetStr5")
        createSearchElStr5Template(event->scenePos());
    if(nodeValue == "scp-procedure")
        createProgramSCPTempale(event->scenePos());
    if(nodeValue == "printEl")
        createPrintElTemplate(event->scenePos());
    if(nodeValue == "printNl")
        createPrintNlTemplate(event->scenePos());
    if(nodeValue == "print")
        createPrintTemplate(event->scenePos());
    if(nodeValue == "ifType")
        createifTypeTemplate(event->scenePos());
    if(nodeValue == "ifEq")
        createifEqTemplate(event->scenePos());
    if(nodeValue == "ifCoin")
        createifCoinTemplate(event->scenePos());
    if(nodeValue == "ifGr")
        createifGrTemplate(event->scenePos());
    if(nodeValue == "Add")
        createAddTemplate(event->scenePos());
    if(nodeValue == "Sub")
        createSubTemplate(event->scenePos());
    if(nodeValue == "Mult")
        createMultTemplate(event->scenePos());
    if(nodeValue == "Div")
        createDivTemplate(event->scenePos());
    if(nodeValue == "Pow")
        createPowTemplate(event->scenePos());
    if(nodeValue == "callReturn")
        createCallReturnTemplate(event->scenePos());
    if(nodeValue == "Return")
        createReturnTemplate(event->scenePos());
    if(nodeValue == "Sin")
        createSinTemplate(event->scenePos());
    if(nodeValue == "ASin")
        createASinTemplate(event->scenePos());
    if(nodeValue == "Cos")
        createCosTemplate(event->scenePos());
    if(nodeValue == "ACos")
        createACosTemplate(event->scenePos());
    if(nodeValue == "toStr")
        createToStrTemplate(event->scenePos());
}

void SCgTemplate::generateSCPCode(QString nodeValue, QMap<int, QList<QString> > atrMap, QList<QString> endObject)
{
    QFile file("SCPProgram.m4scp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;
    QTextStream out(&file);
    out << nodeValue <<"([\n" ;
    int keyValue = 1;

    for(int index = 0; index < atrMap.size(); index++)
    {
        out << keyValue << "_: ";

        foreach (QString s, atrMap[index])
                out << s << ": ";

        out << endObject.at(index) << returnComma(index, atrMap.size()) << "\n";

        keyValue++;
    }
    out << "])";

    file.close();
}

QString SCgTemplate::returnComma(int index, int size)
{
    if(index + 1 < size)
        return ",";
    else
        return "";
}