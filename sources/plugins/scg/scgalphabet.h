/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCGALPHABET_H
#define SCGALPHABET_H

#include <QObject>
#include <QMap>
#include <QIcon>
#include <QPainter>
#include <QPen>
#include <QColor>

class SCgPair;
class SCgBus;
class SCgContour;

class SCgAlphabet : public QObject
{
Q_OBJECT


public:

    //! Possible width of lines
    static inline qreal lineWidthThin()
    {
        return 2.f;
    }
    static inline qreal lineWidthFat()
    {
        return 7.f;
    }
    static inline qreal lineWidthFatIn()
    {
        return lineWidthFat() * 0.6f;
    }

    //! Return width of lines for building usable shapes.
    static inline qreal lineWidthForShape()
    {
        return 9;
    }

    /* Constant types */
    typedef enum
    {
        Const   = 0,
        Var,
        Meta,
        ConstUnknown
    }SCgConstType;

    /* Structural types fo nodes */
    typedef enum    //! TODO: make new names
    {
        NotDefine = 0,
        General,
        Predmet,
        NoPredmet,
        Symmetry,
        Asymmetry,
        Attribute,
        Relation,
        Atom,
        Group,
        StructUnknown
    }SCgNodeStructType;

    /* Positive types */
    typedef enum{
        Positive = 0,
        Negative,
        Fuzzy,
        PosUnknown
    }SCgPosType;

    //! Map for storing icons corresponding to object types.
    typedef QMap<QString, QIcon> SCgObjectTypesMap;

public:
    explicit SCgAlphabet(QObject *parent = 0);

    static SCgAlphabet& getInstance();

    void initialize();
    void paintNode(QPainter *painter, const QColor &color, const QRectF &boundRect, const SCgConstType &type, const SCgNodeStructType &type_struct);
    void paintStruct(QPainter *painter, const QColor &color, const QRectF &boundRect, const SCgNodeStructType &type);

    //! Method for pair painting
    static void paintPair(QPainter *painter, SCgPair *pair);
    //! Method for bus painting
    static void paintBus(QPainter *painter, SCgBus *bus);
    //! Method for contour painting
    static void paintContour(QPainter *painter, SCgContour *contour);

    void getNodeTypes(const SCgConstType type, SCgObjectTypesMap &res);
    void getPairTypes(const SCgConstType type, SCgObjectTypesMap &res);

    void getObjectTypes(const QString &object_name, const SCgConstType const_type, SCgObjectTypesMap &res);

    //! Convertation of type alias to const type code
    SCgConstType aliasToConstCode(const QString &alias) const;
    //! Convertation of type alias to struct type code
    SCgNodeStructType aliasToStructCode(const QString &alias) const;
    //! Convertation of type alias to positive type code
    SCgPosType aliasToPositiveCode(const QString &alias) const;

protected:
    QIcon createNodeIcon(const QSize &size, const SCgConstType &type_const, const SCgNodeStructType &type_struct);
    QIcon createPairIcon(const QSize &size, QString type);

    static QPixmap* getTempPixmap(QColor color);

private:

    static QMap<int, QPixmap*> mTemporaryPixmap;

    static SCgAlphabet *mInstance;
    SCgObjectTypesMap mObjectTypes;

    //! Map to convert string representation of constant type to code
    typedef QMap<QString, SCgConstType> SCgTypeAlias2ConstTypeMap;
    SCgTypeAlias2ConstTypeMap constTypes;
    QStringList mAlias2ConstType;

    //! Map to convert string representation of structural node type to code
    typedef QMap<QString, SCgNodeStructType> SCgTypeAlias2StructTypeMap;
    SCgTypeAlias2StructTypeMap structTypes;

    //! Map to convert string representation of positive type to code
    typedef QMap<QString, SCgPosType> SCgTypeAlias2PosTypeMap;
    SCgTypeAlias2PosTypeMap posTypes;

    // patterns
    static QVector<qreal> varThinDashPattern;
    static QVector<qreal> metaThinDashPattern;
    static QVector<qreal> varFatDashPattern;
    static QVector<qreal> metaFatDashPattern;


signals:

public slots:

};



#endif // SCGALPHABET_H
