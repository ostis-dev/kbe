/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QPixmap>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QGraphicsEffect>

class SCpGraphicalStyle : public QObject
{
    Q_OBJECT

public:
    static SCpGraphicalStyle * instance();
    static void destroy();

private:
    explicit SCpGraphicalStyle(QObject *parent = 0);
    virtual ~SCpGraphicalStyle();

public:
    void initialize();
    void shutdown();

    QPixmap const & operatorHeaderPixmap() const;
    float operatorHeaderHeight() const;
    QFont const & operatorTitleFont() const;
    QFont const & operatorIconFont() const;
    QString const & operatorIconText() const;

    QPixmap const & operatorBodyPixmap() const;
    float operatorBodyRadius() const;

    float operatorPinSize() const;
    QPen const & operatorPinPen() const;
    QPen const & operatorPinPenHovered() const;
    QBrush const & operatorPinBrush() const;
    float operatorPinSpacer() const;
    QFont const & operatorPinFont() const;

    void configureShadowEffect(QGraphicsDropShadowEffect * effect) const;

private:
    QPixmap mOperatorHeaderPixmap;
    float mOperatorHeaderHieght;
    QFont mOperatorTitleFont;
    QFont mOperatorIconFont;
    QString mOperatorIconText;

    QPixmap mOperatorBodyPixmap;
    float mOperatorBodyRadius;

    float mOperatorPinSize;
    QPen mOperatorPinPen;
    QPen mOperatorPinPenHovered;
    QBrush mOperatorPinBrush;
    float mOperatorPinSpacer;
    QFont mOperatorPinFont;

private:
    static SCpGraphicalStyle * msInstance;

signals:

public slots:
};

