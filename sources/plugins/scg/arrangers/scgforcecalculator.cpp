#include "scgforcecalculator.h"

#include <qmath.h>

const double minDistance = 10; // Minimal distance between nodes. It's used at calculation.
// (It's influence fast leap of nodes).
//------------------------------------------------------------------------------
SCgForceCalculator::SCgForceCalculator(const QList<SCgNode *> &nodes,
        const QSet<SCgPair *> &pairs, const QSet<SCgBus *> &busses,
        Parameters parameters)
    : mNodes(nodes), mPairs(pairs), mBusses(busses), mParameters(parameters)
{
}
//------------------------------------------------------------------------------
Force SCgForceCalculator::operator()(const SCgNodeP &node) const
{
    Force force;
    addInteractionWithRealNodes(node, force);
    addInteractionWithPairs(node, force);
    addInteractionWithFakePairNodes(node, force);
    addInteractionWithFakeBusNodes(node, force);

    return force;
}
//------------------------------------------------------------------------------
void SCgForceCalculator::addInteractionWithRealNodes(const SCgNode *node,
                                                  Force &force) const
{
    foreach (SCgNode *curNode, mNodes) {
        if (curNode != node) {
            // Coordinates of other node:
            qreal x2 = curNode->scenePos().x();
            qreal y2 = curNode->scenePos().y();

            // Calculate distance between nodes:
            qreal x1 = node->scenePos().x();
            qreal y1 = node->scenePos().y();
            double distance = calculateDistance(x1, y1, x2, y2);

            // Add interaction force.
            if (distance < minDistance) {
                distance = minDistance; // Need to avoid fast leaps of nodes and devision by zero.
            }
            force.mX += mParameters.mRepulsionFactor * (x1 - x2) / qPow(distance, 3);
            force.mY += mParameters.mRepulsionFactor * (y1 - y2) / qPow(distance, 3);
        }
    }
}
//------------------------------------------------------------------------------
void SCgForceCalculator::addInteractionWithPairs(const SCgNode *node,
        Force &force) const
{
    foreach (SCgObject *object, node->connectedObjects()) {
        if (object->type() == SCgPair::Type) {
            SCgPair *pair = static_cast<SCgPair *>(object);

            // x1, y1 - coodinates of pair end, which connected with node.
            // x2, y2 - other end of pair:
            qreal x1, y1, x2, y2;
            if (pair->beginObject() == node) {
                x2 = pair->scenePoints().last().x();
                y2 = pair->scenePoints().last().y();
                x1 = pair->scenePoints().first().x();
                y1 = pair->scenePoints().first().y();
            } else {
                x2 = pair->scenePoints().first().x();
                y2 = pair->scenePoints().first().y();
                x1 = pair->scenePoints().last().x();
                y1 = pair->scenePoints().last().y();
            }

            // Calculate length of pair:
            double distance = calculateDistance(x1, y1, x2, y2);

            // Add interaction force.
            if (distance < minDistance) {
                distance = minDistance; // Need to avoid fast leaps of nodes and devision by zero.
            }
            force.mX -= mParameters.mSpringRate * (distance - mParameters.mSpringLength)
                    * (x1 - x2) / distance;
            force.mY -= mParameters.mSpringRate * (distance - mParameters.mSpringLength)
                    * (y1 - y2) / distance;
        }
    }
}
//------------------------------------------------------------------------------
void SCgForceCalculator::addInteractionWithFakePairNodes(const SCgNode *node,
                                                  Force &force) const
{
    foreach (SCgPair *pair, mPairs) {
        // Calculate coordinates of fake node (middle of the pair):
        qreal fakeX = (pair->scenePoints().last().x() + pair->scenePoints().first().x()) / 2;
        qreal fakeY = (pair->scenePoints().last().y() + pair->scenePoints().first().y()) / 2;

        addInteractionWithFakeNodes(node, force, fakeX, fakeY);
    }
}
//------------------------------------------------------------------------------
void SCgForceCalculator::addInteractionWithFakeBusNodes(const SCgNode *node,
                                                     Force &force) const
{
    foreach (SCgBus *bus, mBusses) {
        // Calculate coordinates of fake node and add interection with this one:
        // on the middle of the bus:
        qreal fakeX = (bus->scenePoints().last().x() + bus->scenePoints().first().x()) / 2;
        qreal fakeY = (bus->scenePoints().last().y() + bus->scenePoints().first().y()) / 2;
        addInteractionWithFakeNodes(node, force, fakeX, fakeY);
        // on the end of the bus:
        fakeX = bus->scenePoints().last().x();
        fakeY = bus->scenePoints().last().y();
        addInteractionWithFakeNodes(node, force, fakeX, fakeY);
    }
}
//------------------------------------------------------------------------------
void SCgForceCalculator::addInteractionWithFakeNodes(const SCgNode *node,
        Force &force, qreal fakeX, qreal fakeY) const
{
    // Calculate distance between the node and a fake node:
    qreal nodeX = node->scenePos().x();
    qreal nodeY = node->scenePos().y();
    double distance = calculateDistance(nodeX, nodeY, fakeX, fakeY);

    // Add interaction force with the fake node:
    if (distance < minDistance) {
        distance = minDistance; // Need to avoid fast leaps of nodes and devision by zero.
    }
    force.mX += mParameters.mFakeRepulsionFactor * (nodeX - fakeX) / qPow(distance, 3);
    force.mY += mParameters.mFakeRepulsionFactor * (nodeY - fakeY) / qPow(distance, 3);
}
//------------------------------------------------------------------------------
double calculateDistance(QPointF p1, QPointF p2)
{
    return qSqrt(qPow(p2.x() - p1.x(), 2) + qPow(p2.y() - p1.y(), 2));
}
//------------------------------------------------------------------------------
double calculateDistance(qreal x1, qreal y1, qreal x2, qreal y2)
{
    return qSqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2));
}
//------------------------------------------------------------------------------
