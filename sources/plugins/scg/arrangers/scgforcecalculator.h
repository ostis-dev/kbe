#ifndef FORCECALCULATOR_H
#define FORCECALCULATOR_H

#include "scgnode.h"
#include "scgpair.h"
#include "scgbus.h"

#include <QList>
#include <QSet>

typedef SCgNode * SCgNodeP;
//------------------------------------------------------------------------------
//! Force are influencing object.
struct Force
{
    explicit Force(double x = 0, double y = 0) : mX(x), mY(y) {}

    //! Force along the X axis.
    double mX;
    //! Force along the Y axis.
    double mY;
};
//------------------------------------------------------------------------------
//! Energy-based arranger parameters.
struct Parameters
{
    explicit Parameters(double springRate = 1, double springLength = 100,
                        double repulsionFactor = 10000,
                        double fakeRepulsionFactor = 500)
        : mSpringRate(springRate), mSpringLength(springLength),
          mRepulsionFactor(repulsionFactor),
          mFakeRepulsionFactor(fakeRepulsionFactor) {}

    double mSpringRate;
    double mSpringLength;
    double mRepulsionFactor;
    double mFakeRepulsionFactor;
};
//------------------------------------------------------------------------------
class SCgForceCalculator
{
public:
    SCgForceCalculator(const QList<SCgNode *> &nodes,
                    const QSet<SCgPair *> &pairs, const QSet<SCgBus *> &busses,
                    Parameters parameters);

    typedef Force result_type;

    //! Calculate force which influences node.
    /*!
     * @p node - SCgNode for that method calculate force.
     * @return force which influences node.
     */
    Force operator()(const SCgNodeP &node) const;

private:
    //! Add force of interaction node with other real nodes.
    /*!
     * @p node - SCgNode for which we calculate the force.
     * @p force - current force which influences node.
     */
    void addInteractionWithRealNodes(const SCgNode *node, Force &force) const;

    //! Add force which influences node because of connected pairs.
    /*!
     * @p node - SCgNode for which we calculate the force.
     * @p force - current force which influences node.
     */
    void addInteractionWithPairs(const SCgNode *node, Force &force) const;

    //! Add force of interaction node with fake nodes (they are located in middle of pairs).
    /*!
     * @p node - SCgNode for which we calculate the force.
     * @p force - current force which influences node.
     */
    void addInteractionWithFakePairNodes(const SCgNode *node, Force &force) const;

    //! Add force of interaction node with fake nodes (they are located in middle and end of busses).
    /*!
     * @p node - SCgNode for which we calculate the force.
     * @p force - current force which influences node.
     */
    void addInteractionWithFakeBusNodes(const SCgNode *node, Force &force) const;

    //! Add force of interaction node with fake node.
    /*!
     * @p node - SCgNode for which we calculate the force.
     * @p force - current force which influences node.
     * @p fakeX - X coordinate of fake node.
     * @p fakeY - Y coordinate of fake node.
     */
    void addInteractionWithFakeNodes(const SCgNode *node, Force &force,
                                     qreal fakeX, qreal fakeY) const;

    //! Nodes are selected for arranging.
    const QList<SCgNode *> mNodes;

    //! Pairs are selected for arranging.
    const QSet<SCgPair *> mPairs;

    //! Busses are selected for arranging.
    const QSet<SCgBus *> mBusses;

    //! Parameters for energe-based arranging.
    Parameters mParameters;
};
//------------------------------------------------------------------------------
//! Calculate distance between two points.
/*!
 * @p p1 - first point.
 * @p p2 - second point.
 * @return distance between the points.
 */
inline double calculateDistance(QPointF p1, QPointF p2);
//------------------------------------------------------------------------------
//! Calculate distance between two points.
/*!
 * @p x1 - X coordinate of the first point.
 * @p y1 - Y coordinate of the first point.
 * @p x2 - X coordinate of the second point.
 * @p y2 - Y coordinate of the second point.
 * @return distance between the points.
 */
inline double calculateDistance(qreal x1, qreal y1, qreal x2, qreal y2);
//------------------------------------------------------------------------------
#endif // FORCECALCULATOR_H
