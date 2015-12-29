/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scpgraphicalstyle.h"

#include <QGraphicsItem>

SCpGraphicalStyle * SCpGraphicalStyle::msInstance = 0;

SCpGraphicalStyle * SCpGraphicalStyle::instance()
{
    if (!msInstance)
    {
        msInstance = new SCpGraphicalStyle();
        msInstance->initialize();
    }

    return msInstance;
}

void SCpGraphicalStyle::destroy()
{
    if (msInstance)
    {
        delete msInstance;
        msInstance = 0;
    }
}

SCpGraphicalStyle::SCpGraphicalStyle(QObject *parent)
    : QObject(parent)
{
}

SCpGraphicalStyle::~SCpGraphicalStyle()
{
}

void SCpGraphicalStyle::initialize()
{
    mOperatorHeaderPixmap.load(":/scg/media/scp/scp-operator-header.png");
    mOperatorBodyPixmap.load(":/scg/media/scp/scp-operator-body.png");

    mOperatorHeaderHieght = 20.f;
    mOperatorBodyRadius = 5.f;

    mOperatorTitleFont = QFont("Helvetica [Cronyx]", 8, QFont::Normal);
    mOperatorIconFont = QFont("Helvetica [Cronyx]", 5, QFont::Thin, true);
    mOperatorIconText = "f(x)";

    mOperatorPinSize = 12.f;
    mOperatorPinPen = QPen(QBrush(Qt::gray), 2.f, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    mOperatorPinPenHovered = QPen(QBrush(Qt::white), 2.f, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    mOperatorPinBrush = QBrush(Qt::gray);
    mOperatorPinSpacer = 10.f;
    mOperatorPinFont = QFont("Helvetica [Cronyx]", 6, QFont::Normal);
}

void SCpGraphicalStyle::shutdown()
{

}

QPixmap const & SCpGraphicalStyle::operatorHeaderPixmap() const
{
    return mOperatorHeaderPixmap;
}

float SCpGraphicalStyle::operatorHeaderHeight() const
{
    return mOperatorHeaderHieght;
}

QFont const & SCpGraphicalStyle::operatorTitleFont() const
{
    return mOperatorTitleFont;
}

QFont const & SCpGraphicalStyle::operatorIconFont() const
{
    return mOperatorIconFont;
}

QString const & SCpGraphicalStyle::operatorIconText() const
{
    return mOperatorIconText;
}

QPixmap const & SCpGraphicalStyle::operatorBodyPixmap() const
{
    return mOperatorBodyPixmap;
}

float SCpGraphicalStyle::operatorBodyRadius() const
{
    return mOperatorBodyRadius;
}

float SCpGraphicalStyle::operatorPinSize() const
{
    return mOperatorPinSize;
}

QPen const & SCpGraphicalStyle::operatorPinPen() const
{
    return mOperatorPinPen;
}

QPen const & SCpGraphicalStyle::operatorPinPenHovered() const
{
    return mOperatorPinPenHovered;
}

QBrush const & SCpGraphicalStyle::operatorPinBrush() const
{
    return mOperatorPinBrush;
}

float SCpGraphicalStyle::operatorPinSpacer() const
{
    return mOperatorPinSpacer;
}

QFont const & SCpGraphicalStyle::operatorPinFont() const
{
    return mOperatorPinFont;
}

void SCpGraphicalStyle::configureShadowEffect(QGraphicsDropShadowEffect * effect) const
{
    effect->setEnabled(true);
    effect->setBlurRadius(8);
    effect->setColor(Qt::black);
    effect->setOffset(3, 3);
}
