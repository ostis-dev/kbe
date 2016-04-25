/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
        ConstUnknown
    } SCgConstType;

    /* Structural types fo nodes */
    typedef enum    //! TODO: make new names
    {
        StructType_NotDefine = 0,
        StructType_General,
        StructType_Abstract,
        StructType_Material,
        StructType_Struct,
        StructType_Tuple,
        StructType_Role,
        StructType_Relation,
        StructType_Group,
        StructUnknown
    } SCgNodeStructType;

    /* Positive types */
    typedef enum
    {
        Positive = 0,
        Negative,
        Fuzzy,
        PosUnknown
    } SCgPosType;

    /* Permanency type */
    typedef enum
    {
        Permanent = 0,
        Temporary,
        PermAny,
        PermUnknown
    } SCgPermType;

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

    /*! Converts constant type string alias into code
      * @param alias String representation of const type alias
      */
    SCgConstType aliasToConstCode(const QString &alias) const;
    /*! Converts struct type string alias into code
      * @param alias String representation of struct type alias
      */
    SCgNodeStructType aliasToStructCode(const QString &alias) const;
    /*! Converts positivity type string alias into code
      * @param alias String representation of positivity type alias
      */
    SCgPosType aliasToPositiveCode(const QString &alias) const;
    /*! Converts permanency type string alias into code
      * @param alias String representation of permanency type alias
      */
    SCgPermType aliasToPermanencyCode(const QString &alias) const;

    /*! Converts const type code into string alias
     * @param code Constant type code to convert
     */
    QString aliasFromConstCode(SCgConstType code) const;

    /*! Converts struct type code into string alias
     * @param code Struct type code to convert
     */
    QString aliasFromStructCode(SCgNodeStructType code) const;

    /*! Converts positivity type code into string alias
     * @param code Positivity code to convert
     */
    QString aliasFromPositiveCode(SCgPosType code) const;

    /*! Converts permanency type code into string alias
     * @param code Permanency type code to convert
     */
    QString aliasFromPermanencyCode(SCgPermType code) const;

protected:
    QIcon createNodeIcon(const QSize &size, const SCgConstType &type_const, const SCgNodeStructType &type_struct);
    QIcon createPairIcon(const QSize &size, QString type);

private:

    static SCgAlphabet *msInstance;
    SCgObjectTypesMap mObjectTypes;
    static QString msEmptyTypeAlias;

    //! Map to convert string representation of constant type into code
    typedef QMap<QString, SCgConstType> SCgAlias2ConstTypeMap;
    SCgAlias2ConstTypeMap mConstTypes;
    QStringList mAlias2ConstType;

    //! Map to convert string representation of struct type into code
    typedef QMap<QString, SCgNodeStructType> SCgAlias2StructTypeMap;
    SCgAlias2StructTypeMap mStructTypes;

    //! Map to convert string representation of positive type into code
    typedef QMap<QString, SCgPosType> SCgAlias2PosTypeMap;
    SCgAlias2PosTypeMap mPosTypes;

    //! Map to convert string representation of permanent type into code
    typedef QMap<QString, SCgPermType> SCgAlias2PermTypeMap;
    SCgAlias2PermTypeMap mPermTypes;

    //! Map to convert constant type into string
    typedef QMap<SCgConstType, QString> SCgConstType2AliasMap;
    SCgConstType2AliasMap mConstAliases;

    //! Map to convert struct type into string
    typedef QMap<SCgNodeStructType, QString> SCgStructType2AliasMap;
    SCgStructType2AliasMap mStructAliases;

    //! Map to convert positivity type into string
    typedef QMap<SCgPosType, QString> SCgPositivityType2AliasMap;
    SCgPositivityType2AliasMap mPositivityAliases;

    //! Map to convert permanency type into string
    typedef QMap<SCgPermType, QString> SCgPermanencyType2AliasMap;
    SCgPermanencyType2AliasMap mPermanencyAliases;

    //! Pattern that used to draw permanent, variable, accessory pairs
    static QVector<qreal> msPermVarAccesDashPattern;
    //! Pattern that used to draw permanent, variable, not accessory pairs
    static QVector<qreal> msPermVarNoAccesDashPattern;
    //! Pattern that used to draw temporary, constant, accessory pairs
    static QVector<qreal> msTempConstAccesDashPattern;
    //! Pattern that used to draw temporary, variable, accessory pairs
    static QVector<qreal> msTempVarAccesDashPattern;
    //! Pattern that used to draw common accessory marks
    static QVector<qreal> msCommonAccessoryDashPattern;

signals:

public slots:

};

