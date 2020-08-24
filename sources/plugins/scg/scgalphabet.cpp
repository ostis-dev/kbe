/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgalphabet.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"
#include <QDebug>
#include <QtCore/qmath.h>

#include <math.h>

#define LINE_THIN_WIDTH 2.f
#define LINE_FAT_WIDTH 3.6f
#define LINE_FATIN_WIDTH (LINE_FAT_WIDTH * 0.6f) //2.1
#define LINE_COM_ACCESS_MARK_WIDTH 4.f

#define LINE_MARK_NEG_LENGTH  4.f
#define LINE_MARK_FUZ_LENGTH  5.f

SCgAlphabet* SCgAlphabet::msInstance = 0;
QString SCgAlphabet::msEmptyTypeAlias = "-";

QVector<qreal> SCgAlphabet::msPermVarMembershipDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msPermVarCommonDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempConstMembershipDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempRectContour = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempRhombusContour = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempVarMembershipDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempVarCommonDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msCommonMembershipDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::dottedDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::metaMembershipDashPattern = QVector<qreal>();


SCgAlphabet::SCgAlphabet(QObject *parent) :
    QObject(parent)
{

}

SCgAlphabet& SCgAlphabet::getInstance()
{
    if (!msInstance)
    {
        msInstance = new SCgAlphabet;
        msInstance->initialize();
    }

    return *msInstance;
}

void SCgAlphabet::initialize()
{
    mConstTypes["const"] = Const;
    mConstTypes["var"] = Var;
    mConstTypes["meta"] = Meta;

    mConstAliases[Const] = "const";
    mConstAliases[Var] = "var";
    mConstAliases[Meta] = "meta";

    mAlias2ConstType.push_back("const");
    mAlias2ConstType.push_back("var");
    mAlias2ConstType.push_back("meta");
    mAlias2ConstType.push_back("-");

    mPosTypes["pos"] = Positive;
    mPosTypes["neg"] = Negative;
    mPosTypes["fuz"] = Fuzzy;

    mPositivityAliases[Positive] = "pos";
    mPositivityAliases[Negative] = "neg";
    mPositivityAliases[Fuzzy] = "fuz";

    mPermTypes["perm"] = Permanent;
    mPermTypes["temp"] = Temporary;
    mPermTypes["any"] = PermAny;

    mPermanencyAliases[Permanent] = "perm";
    mPermanencyAliases[Temporary] = "temp";
    mPermanencyAliases[PermAny] = "any";

    mStructTypes["not_define"] = StructType_NotDefine;
    mStructTypes["general"] = StructType_General;
    mStructTypes["terminal"] = StructType_Terminal;
    mStructTypes["struct"] = StructType_Struct;
    mStructTypes["tuple"] = StructType_Tuple;
    mStructTypes["role"] = StructType_Role;
    mStructTypes["relation"] = StructType_Relation;
    mStructTypes["group"] = StructType_Group;
    mStructTypes["super_group"] = StructType_Super_Group;


    mStructAliases[StructType_NotDefine] = "not_define";
    mStructAliases[StructType_General] = "general";
    mStructAliases[StructType_Terminal] = "terminal";
    mStructAliases[StructType_Struct] = "struct";
    mStructAliases[StructType_Tuple] = "tuple";
    mStructAliases[StructType_Role] = "role";
    mStructAliases[StructType_Relation] = "relation";
    mStructAliases[StructType_Group] = "group";
    mStructAliases[StructType_Super_Group] = "super_group";

    // initiliaze patterns
    msPermVarMembershipDashPattern << 16 / LINE_THIN_WIDTH
                              << 16 / LINE_THIN_WIDTH;

    msPermVarCommonDashPattern << 16 / 1.8 / LINE_THIN_WIDTH
                                << 16 / 1.8 / LINE_THIN_WIDTH;

    qreal temp_dash = 2 / LINE_THIN_WIDTH;
    msTempConstMembershipDashPattern << temp_dash
                                << temp_dash
                                << temp_dash
                                << temp_dash;
    msTempVarMembershipDashPattern << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << 9 * temp_dash;
    metaMembershipDashPattern << 0
                    << 11.8 / LINE_THIN_WIDTH
                    << 0.5 / LINE_THIN_WIDTH
                    << 1.85; //todo calculate this cofficient
    temp_dash = 2 / 1.8 / LINE_THIN_WIDTH;

    dottedDashPattern << temp_dash
                      << temp_dash;

    msTempVarCommonDashPattern << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << 9 * temp_dash;
    temp_dash = 1.08f;
    msTempRectContour << temp_dash
                      << temp_dash
                      << temp_dash
                      << temp_dash;
    temp_dash = 1.035f;
    msTempRhombusContour << temp_dash - 0.25f
                         << temp_dash
                         << temp_dash
                         << temp_dash
                         << temp_dash
                         << temp_dash
                         << temp_dash + 0.25f;

    msCommonMembershipDashPattern << 4.f / LINE_COM_ACCESS_MARK_WIDTH << 10.f / LINE_COM_ACCESS_MARK_WIDTH;

    QSize size(24, 24);

    mObjectTypes["node/-/-/not_define"] = createNodeIcon(size, Const, Permanent, StructType_NotDefine);

    //const perm
    mObjectTypes["node/const/perm/general"] = createNodeIcon(size, Const, Permanent, StructType_General);
    mObjectTypes["node/const/perm/terminal"] = createNodeIcon(size, Const, Permanent, StructType_Terminal);
    mObjectTypes["node/const/perm/struct"] = createNodeIcon(size, Const, Permanent, StructType_Struct);
    mObjectTypes["node/const/perm/tuple"] = createNodeIcon(size, Const, Permanent, StructType_Tuple);
    mObjectTypes["node/const/perm/role"] = createNodeIcon(size, Const, Permanent, StructType_Role);
    mObjectTypes["node/const/perm/relation"] = createNodeIcon(size, Const, Permanent, StructType_Relation);
    mObjectTypes["node/const/perm/group"] = createNodeIcon(size, Const, Permanent, StructType_Group);
    mObjectTypes["node/const/perm/super_group"] = createNodeIcon(size, Const, Permanent, StructType_Super_Group);

    //var perm
    mObjectTypes["node/var/perm/general"] = createNodeIcon(size, Var, Permanent, StructType_General);
    mObjectTypes["node/var/perm/terminal"] = createNodeIcon(size, Var, Permanent, StructType_Terminal);
    mObjectTypes["node/var/perm/struct"] = createNodeIcon(size, Var, Permanent, StructType_Struct);
    mObjectTypes["node/var/perm/tuple"] = createNodeIcon(size, Var, Permanent, StructType_Tuple);
    mObjectTypes["node/var/perm/role"] = createNodeIcon(size, Var, Permanent, StructType_Role);
    mObjectTypes["node/var/perm/relation"] = createNodeIcon(size, Var, Permanent, StructType_Relation);
    mObjectTypes["node/var/perm/group"] = createNodeIcon(size, Var, Permanent, StructType_Group);
    mObjectTypes["node/var/perm/super_group"] = createNodeIcon(size, Var, Permanent, StructType_Super_Group);

    //meta perm
    mObjectTypes["node/meta/perm/general"] = createNodeIcon(size, Meta, Permanent, StructType_General);
    mObjectTypes["node/meta/perm/terminal"] = createNodeIcon(size, Meta, Permanent, StructType_Terminal);
    mObjectTypes["node/meta/perm/struct"] = createNodeIcon(size, Meta, Permanent, StructType_Struct);
    mObjectTypes["node/meta/perm/tuple"] = createNodeIcon(size, Meta, Permanent, StructType_Tuple);
    mObjectTypes["node/meta/perm/role"] = createNodeIcon(size, Meta, Permanent, StructType_Role);
    mObjectTypes["node/meta/perm/relation"] = createNodeIcon(size, Meta, Permanent, StructType_Relation);
    mObjectTypes["node/meta/perm/group"] = createNodeIcon(size, Meta, Permanent, StructType_Group);
    mObjectTypes["node/meta/perm/super_group"] = createNodeIcon(size, Meta, Permanent, StructType_Super_Group);

    //const temp
    mObjectTypes["node/const/temp/general"] = createNodeIcon(size, Const, Temporary, StructType_General);
    mObjectTypes["node/const/temp/terminal"] = createNodeIcon(size, Const, Temporary, StructType_Terminal);
    mObjectTypes["node/const/temp/struct"] = createNodeIcon(size, Const, Temporary, StructType_Struct);
    mObjectTypes["node/const/temp/tuple"] = createNodeIcon(size, Const, Temporary, StructType_Tuple);
    mObjectTypes["node/const/temp/role"] = createNodeIcon(size, Const, Temporary, StructType_Role);
    mObjectTypes["node/const/temp/relation"] = createNodeIcon(size, Const, Temporary, StructType_Relation);
    mObjectTypes["node/const/temp/group"] = createNodeIcon(size, Const, Temporary, StructType_Group);
    mObjectTypes["node/const/temp/super_group"] = createNodeIcon(size, Const, Temporary, StructType_Super_Group);

    //var temp
    mObjectTypes["node/var/temp/general"] = createNodeIcon(size, Var, Temporary, StructType_General);
    mObjectTypes["node/var/temp/terminal"] = createNodeIcon(size, Var, Temporary, StructType_Terminal);
    mObjectTypes["node/var/temp/struct"] = createNodeIcon(size, Var, Temporary, StructType_Struct);
    mObjectTypes["node/var/temp/tuple"] = createNodeIcon(size, Var, Temporary, StructType_Tuple);
    mObjectTypes["node/var/temp/role"] = createNodeIcon(size, Var, Temporary, StructType_Role);
    mObjectTypes["node/var/temp/relation"] = createNodeIcon(size, Var, Temporary, StructType_Relation);
    mObjectTypes["node/var/temp/group"] = createNodeIcon(size, Var, Temporary, StructType_Group);
    mObjectTypes["node/var/temp/super_group"] = createNodeIcon(size, Var, Temporary, StructType_Super_Group);

    //meta temp
    mObjectTypes["node/meta/temp/general"] = createNodeIcon(size, Meta, Temporary, StructType_General);
    mObjectTypes["node/meta/temp/terminal"] = createNodeIcon(size, Meta, Temporary, StructType_Terminal);
    mObjectTypes["node/meta/temp/struct"] = createNodeIcon(size, Meta, Temporary, StructType_Struct);
    mObjectTypes["node/meta/temp/tuple"] = createNodeIcon(size, Meta, Temporary, StructType_Tuple);
    mObjectTypes["node/meta/temp/role"] = createNodeIcon(size, Meta, Temporary, StructType_Role);
    mObjectTypes["node/meta/temp/relation"] = createNodeIcon(size, Meta, Temporary, StructType_Relation);
    mObjectTypes["node/meta/temp/group"] = createNodeIcon(size, Meta, Temporary, StructType_Group);
    mObjectTypes["node/meta/temp/super_group"] = createNodeIcon(size, Meta, Temporary, StructType_Super_Group);

    QSize pairSize(72, 24);

    // scg core pairs
    mObjectTypes["pair/-/-/-/noorient"] = createPairIcon(pairSize, "pair/-/-/-/noorient");
    mObjectTypes["pair/-/-/-/orient"] = createPairIcon(pairSize, "pair/-/-/-/orient");

    // const
    mObjectTypes["pair/const/-/perm/noorien"] = createPairIcon(pairSize, "pair/const/-/perm/noorien");
    mObjectTypes["pair/const/-/perm/orient"] = createPairIcon(pairSize, "pair/const/-/perm/orient");
    mObjectTypes["pair/const/-/temp/noorien"] = createPairIcon(pairSize, "pair/const/-/temp/noorien");
    mObjectTypes["pair/const/-/temp/orient"] = createPairIcon(pairSize, "pair/const/-/temp/orient");
    mObjectTypes["pair/const/pos/perm/orient/membership"] = createPairIcon(pairSize, "pair/const/pos/perm/orient/membership");
    mObjectTypes["pair/const/pos/temp/orient/membership"] = createPairIcon(pairSize, "pair/const/pos/temp/orient/membership");
    mObjectTypes["pair/const/neg/perm/orient/membership"] = createPairIcon(pairSize, "pair/const/neg/perm/orient/membership");
    mObjectTypes["pair/const/neg/temp/orient/membership"] = createPairIcon(pairSize, "pair/const/neg/temp/orient/membership");
    mObjectTypes["pair/const/fuz/perm/orient/membership"] = createPairIcon(pairSize, "pair/const/fuz/perm/orient/membership");
    mObjectTypes["pair/const/fuz/temp/orient/membership"] = createPairIcon(pairSize, "pair/const/fuz/temp/orient/membership");

    // var
    mObjectTypes["pair/var/-/perm/noorien"] = createPairIcon(pairSize, "pair/var/-/perm/noorien");
    mObjectTypes["pair/var/-/perm/orient"] = createPairIcon(pairSize, "pair/var/-/perm/orient");
    mObjectTypes["pair/var/-/temp/noorien"] = createPairIcon(pairSize, "pair/var/-/temp/noorien");
    mObjectTypes["pair/var/-/temp/orient"] = createPairIcon(pairSize, "pair/var/-/temp/orient");
    mObjectTypes["pair/var/pos/perm/orient/membership"] = createPairIcon(pairSize, "pair/var/pos/perm/orient/membership");
    mObjectTypes["pair/var/pos/temp/orient/membership"] = createPairIcon(pairSize, "pair/var/pos/temp/orient/membership");
    mObjectTypes["pair/var/neg/perm/orient/membership"] = createPairIcon(pairSize, "pair/var/neg/perm/orient/membership");
    mObjectTypes["pair/var/neg/temp/orient/membership"] = createPairIcon(pairSize, "pair/var/neg/temp/orient/membership");
    mObjectTypes["pair/var/fuz/perm/orient/membership"] = createPairIcon(pairSize, "pair/var/fuz/perm/orient/membership");
    mObjectTypes["pair/var/fuz/temp/orient/membership"] = createPairIcon(pairSize, "pair/var/fuz/temp/orient/membership");

    // meta
    mObjectTypes["pair/meta/-/perm/noorien"] = createPairIcon(pairSize, "pair/meta/-/perm/noorien");
    mObjectTypes["pair/meta/-/perm/orient"] = createPairIcon(pairSize, "pair/meta/-/perm/orient");
    mObjectTypes["pair/meta/-/temp/noorien"] = createPairIcon(pairSize, "pair/meta/-/temp/noorien");
    mObjectTypes["pair/meta/-/temp/orient"] = createPairIcon(pairSize, "pair/meta/-/temp/orient");
    mObjectTypes["pair/meta/pos/perm/orient/membership"] = createPairIcon(pairSize, "pair/meta/pos/perm/orient/membership");
    mObjectTypes["pair/meta/pos/temp/orient/membership"] = createPairIcon(pairSize, "pair/meta/pos/temp/orient/membership");
    mObjectTypes["pair/meta/neg/perm/orient/membership"] = createPairIcon(pairSize, "pair/meta/neg/perm/orient/membership");
    mObjectTypes["pair/meta/neg/temp/orient/membership"] = createPairIcon(pairSize, "pair/meta/neg/temp/orient/membership");
    mObjectTypes["pair/meta/fuz/perm/orient/membership"] = createPairIcon(pairSize, "pair/meta/fuz/perm/orient/membership");
    mObjectTypes["pair/meta/fuz/temp/orient/membership"] = createPairIcon(pairSize, "pair/meta/fuz/temp/orient/membership");

    // scg core contours
    // we use pair icon for contour, cause are the same
    mObjectTypes["contour/const/perm"] = createPairIcon(pairSize, "pair/const/pos/perm/noorient/membership");
    mObjectTypes["contour/var/perm"] = createPairIcon(pairSize, "pair/var/pos/perm/noorient/membership");
    mObjectTypes["contour/const/temp"] = createPairIcon(pairSize, "pair/const/pos/temp/noorient/membership");
    mObjectTypes["contour/var/temp"] = createPairIcon(pairSize, "pair/var/pos/temp/noorient/membership");

}

QIcon SCgAlphabet::createNodeIcon(const QSize &size, const SCgConstType &type_const,
                                   const SCgPermType &type_perm,
                                   const SCgNodeStructType &type_struct)
{
    QIcon icon;
//    for (int mode = QIcon::Normal; mode <= QIcon::Selected; mode++)
//       for (int state = QIcon::On; state <= QIcon::Off; state++)
        {
            QPixmap pixmap(size);
            QPainter painter;

            pixmap.fill(Qt::transparent);

            painter.begin(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);

            QColor color;

            painter.translate(size.width() / 2.f, size.height() / 2.f);
            painter.scale(0.8f, 0.8f);

            paintNode(&painter, QColor(0, 0, 0, 255),//(state == QIcon::On) ? 255 : 128),
                      QRectF(-size.width() / 2.f, - size.height() / 2.f, size.width(), size.height()),
                      type_const, type_perm, type_struct);
            painter.end();

            for (int mode = QIcon::Normal; mode <= QIcon::Selected; mode++)
                for (int state = QIcon::On; state <= QIcon::Off; state++)
                    icon.addPixmap(pixmap, (QIcon::Mode)mode, (QIcon::State)state);

        }

    return icon;
}

QIcon SCgAlphabet::createPairIcon(const QSize &size, QString type)
{
    QIcon icon;

    SCgPair *pair = new SCgPair;
    pair->setTypeAlias(type);

    QVector<QPointF> points;
    points.push_back(QPointF(-size.width() / 2.f, 0.f));
    points.push_back(QPointF(size.width() / 2.f, 0.f));

    pair->setPoints(points);

    QPixmap pixmap(size);
    QPainter painter;

    pixmap.fill(Qt::transparent);

    painter.begin(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    pair->setColor(QColor(0, 0, 0, 255));//(state == QIcon::On) ? 255 : 128));

    painter.translate(size.width() / 2.f, size.height() / 2.f);
    painter.scale(0.9f, 0.9f);

    paintPair(&painter, pair);

    painter.end();

    for (int mode = QIcon::Normal; mode <= QIcon::Selected; mode++)
        for (int state = QIcon::On; state <= QIcon::Off; state++)
            icon.addPixmap(pixmap, (QIcon::Mode)mode, (QIcon::State)state);

    delete pair;

    return icon;
}

QVector<qreal> SCgAlphabet::getMsTempConstMembershipDashPattern()
{
    return msTempConstMembershipDashPattern;
}

QVector<qreal> SCgAlphabet::getMsTempVarMembershipDashPattern()
{
    return msTempVarMembershipDashPattern;
}

QVector<qreal> SCgAlphabet::getMsPermVarMembershipDashPattern()
{
    return msPermVarMembershipDashPattern;
}

void SCgAlphabet::getNodeTypes(const SCgConstType type_const, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("node", type_const, res);
}

void SCgAlphabet::getNodeTypes(const SCgConstType type_const, SCgPermType type_perm, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("node", type_const, type_perm, res);
}

void SCgAlphabet::getPairTypes(SCgConstType type, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("pair", type, res);
}

void SCgAlphabet::getContourTypes(SCgConstType type, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("contour", type, res);
}

void SCgAlphabet::getObjectTypes(const QString &object_name, const SCgConstType const_type, SCgObjectTypesMap &res)
{
    SCgObjectTypesMap::iterator it;
    for (it = mObjectTypes.begin(); it != mObjectTypes.end(); ++it)
    {
        if (!it.key().startsWith(object_name)) continue;

        QStringList sl = it.key().split("/");
        if (mAlias2ConstType[const_type] == sl[1])
            res[it.key()] = it.value();
    }
}

void SCgAlphabet::getObjectTypes(const QString &object_name, const SCgConstType const_type, SCgPermType type_perm,  SCgObjectTypesMap &res)
{
    SCgObjectTypesMap::iterator it;
    for (it = mObjectTypes.begin(); it != mObjectTypes.end(); ++it)
    {
        if (!it.key().startsWith(object_name)) continue;

        QStringList sl = it.key().split("/");
        if ((mAlias2ConstType[const_type] == sl[1]) && (mPermanencyAliases[type_perm] == sl[2]))
            res[it.key()] = it.value();
    }
}

SCgAlphabet::SCgConstType SCgAlphabet::aliasToConstCode(const QString &alias) const
{
    if (!mConstTypes.contains(alias))
        return ConstUnknown;

    return mConstTypes[alias];
}

SCgAlphabet::SCgNodeStructType SCgAlphabet::aliasToStructCode(const QString &alias) const
{
    if (!mStructTypes.contains(alias))
        return StructUnknown;

    return mStructTypes[alias];
}

SCgAlphabet::SCgPosType SCgAlphabet::aliasToPositiveCode(const QString &alias) const
{
    if (!mPosTypes.contains(alias))
        return PosUnknown;

    return mPosTypes[alias];
}

SCgAlphabet::SCgPermType SCgAlphabet::aliasToPermanencyCode(const QString &alias) const
{
    if (!mPermTypes.contains(alias))
        return PermUnknown;

    return mPermTypes[alias];
}

QString SCgAlphabet::aliasFromConstCode(SCgAlphabet::SCgConstType code) const
{
    if (!mConstAliases.contains(code))
        return msEmptyTypeAlias;

    return mConstAliases[code];
}

QString SCgAlphabet::aliasFromStructCode(SCgAlphabet::SCgNodeStructType code) const
{
    if (!mStructAliases.contains(code))
        return msEmptyTypeAlias;

    return mStructAliases[code];
}

QString SCgAlphabet::aliasFromPositiveCode(SCgAlphabet::SCgPosType code) const
{
    if (!mPositivityAliases.contains(code))
        return msEmptyTypeAlias;

    return mPositivityAliases[code];
}

QString SCgAlphabet::aliasFromPermanencyCode(SCgAlphabet::SCgPermType code) const
{
    if (!mPermanencyAliases.contains(code))
        return msEmptyTypeAlias;

    return mPermanencyAliases[code];
}

void SCgAlphabet::paintNode(QPainter *painter, const QColor &color, const QRectF &boundRect,
                            const SCgConstType &type, const SCgPermType &type_perm, const SCgNodeStructType &type_struct)
{

    QColor brush_color =  QColor(255, 255, 255, 224);
    // to draw not defined nodes we just need to scale them
    if (type_struct == StructType_NotDefine)
    {
        painter->scale(0.3f, 0.3f);
        brush_color = color;
        brush_color.setAlpha(224);
    }


    // drawing of border
    QPen pen = QPen(QBrush(color, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush = QBrush(brush_color, Qt::SolidPattern);
    switch (type_perm) {
    case Temporary:
        pen.setDashPattern(msTempRectContour);
        break;
    }
    painter->setPen(pen);
    painter->setBrush(brush);

    QRectF bound = boundRect.adjusted(2, 2, -2, -2);

    if (type_struct == StructType_NotDefine)
    {
        pen.setWidth(LINE_FAT_WIDTH * 2);
        painter->setPen(pen);
        painter->drawEllipse(bound);
        return;
    }

    QPainterPath clipPath;
    switch (type) {
    case Const:
        painter->drawEllipse(bound);
        clipPath.addEllipse(bound.adjusted(1,1,-1,-1));
        break;
    case Var:
        painter->scale(0.9f, 0.9f);
        //painter->drawRect(bound);
        painter->drawLine(bound.topLeft(), bound.topRight());
        painter->drawLine(bound.topLeft(), bound.bottomLeft());
        painter->drawLine(bound.bottomRight(), bound.bottomLeft());
        painter->drawLine(bound.bottomRight(), bound.topRight());
        pen.setCapStyle(Qt::MPenCapStyle);
        painter->setPen(pen);
        painter->drawPoint(bound.topLeft());
        painter->drawPoint(bound.topRight());
        painter->drawPoint(bound.bottomLeft());
        painter->drawPoint(bound.bottomRight());

        clipPath.addRect(bound);
        break;
    case Meta:
        QPen pen = QPen(QBrush(color, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
        if (type_perm == Temporary) {
            pen.setDashPattern(msTempRhombusContour);
        }
        painter->setPen(pen);
        painter->scale(0.9f, 0.9f);
        QPointF c = boundRect.center();
        QPointF d = QPointF(boundRect.width() / 2.0, 0.f);
        QPointF d2 = QPointF(0.f, boundRect.height() / 2.0);
        painter->drawLine(c - d, c - d2);
        painter->drawLine(c + d2, c - d);
        painter->drawLine(c - d2, c + d);
        painter->drawLine(c + d, c + d2);
        pen.setCapStyle(Qt::MPenCapStyle);
        painter->setPen(pen);
        painter->drawPoint(c - d);
        painter->drawPoint(c - d2);
        painter->drawPoint(c + d);
        painter->drawPoint(c + d2);
        QPainterPath path;
        path.moveTo(bound.center().x(), bound.top());
        path.lineTo(bound.right(), bound.center().y());
        path.lineTo(bound.center().x(), bound.bottom());
        path.lineTo(bound.left(), bound.center().y());
        path.lineTo(bound.center().x(), bound.top());
        clipPath.addPath(path);
        break;
    }
    painter->setClipPath(clipPath, Qt::IntersectClip);
    paintStruct(painter, color, bound, type_struct);
}

void SCgAlphabet::paintStruct(QPainter *painter, const QColor &color,
                              const QRectF &boundRect, const SCgNodeStructType &type)
{
    QPen pen = QPen(QBrush(color, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    painter->setPen(pen);

    // structure types
    QPointF c, d, d2;
    switch (type)
    {
    case StructType_Struct:
        float w, h;
        w = boundRect.width() / 10.f;
        h = boundRect.height() / 10.f;
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawEllipse(-w, -h, w * 2 - 1, h * 2 - 1);
        painter->setBrush(QBrush(Qt::NoBrush));
        break;

    case StructType_Terminal:
    {
        QPen p = painter->pen();
        p.setWidthF(1);
        painter->setPen(p);
        qreal y1, y2, left, right;
        left = boundRect.left();
        right = boundRect.right();


        qreal dist = right - left;

        y1 = boundRect.top();
        y2 = boundRect.bottom();

        for (qreal d = 0; d <= dist; d += dist / 3.5)
        {
            painter->drawLine(QLineF(left + d, y1, left, y1 + d));
            painter->drawLine(QLineF(right - d, y2, right, y2 - d));
        }
        break;
    }

    case StructType_Tuple:
        c = boundRect.center();
        d = QPointF(boundRect.width() / 2.0, 0.f);
        painter->drawLine(c - d, c + d);
        break;

    case StructType_Role:
        c = boundRect.center();
        d = QPointF(boundRect.width() / 2.0, 0.f);
        painter->drawLine(c - d, c + d);
        d = QPointF(0.f, boundRect.height() / 2.0);
        painter->drawLine(c - d, c + d);
        break;

    case StructType_Relation:
        painter->drawLine(boundRect.topLeft(), boundRect.bottomRight());
        painter->drawLine(boundRect.topRight(), boundRect.bottomLeft());
        break;

    case StructType_Group:
    {
        QPen p = painter->pen();
        p.setWidthF(1);
        painter->setPen(p);
        d2 = QPointF(0.f, boundRect.width() / 3.0);
        d = QPointF(boundRect.height() / 3.0, 0.f);
        painter->drawLine(boundRect.bottomLeft()-d2, boundRect.bottomRight()-d2);
        painter->drawLine(boundRect.topLeft()+d2, boundRect.topRight()+d2);
        painter->drawLine(boundRect.topRight()-d, boundRect.bottomRight()-d);
        painter->drawLine(boundRect.topLeft()+d, boundRect.bottomLeft()+d);
        break;
    }
    case StructType_Super_Group:
        d = QPointF(0.f, boundRect.height() / 4.0);
        painter->drawLine(boundRect.bottomLeft(), boundRect.center()-d);
        painter->drawLine(boundRect.center()-d, boundRect.bottomRight());
        painter->drawPoint(boundRect.center()-d);
        break;
    default:
        break;
    }
}

void SCgAlphabet::paintPair(QPainter *painter, SCgPair *pair)
{
    Q_ASSERT(pair != 0);

    QVector<QPointF> points = pair->points();

    Q_ASSERT(points.size() > 1);

    static float arrowLength = 16.f;
    static float arrowWidth = 9.f;
    double angle = 0;

    if (pair->isOrient())
    {
        QLineF line(points[points.size() - 2], points.last());
        angle = ::atan2(line.dx(), line.dy());
        // correct last point
        points.last() -= QPointF((arrowLength/2) * ::sin(angle), (arrowLength/2) * ::cos(angle));
    }

    // get type data
    SCgPosType posType = pair->posType();
    SCgConstType constType = pair->constType();
    SCgPermType permType = pair->permType();

    painter->setBrush(Qt::NoBrush);

    QPen pen(pair->color());
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::RoundJoin);

    // draw all cases
    if (pair->isMempership())
    {       
        pen.setWidthF(LINE_THIN_WIDTH);
        QPen markPen = pen;
        QPen metaPen = pen;

        if (constType == ConstUnknown && posType == PosUnknown)
        {
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());

            markPen.setWidthF(LINE_COM_ACCESS_MARK_WIDTH);
            markPen.setDashPattern(msCommonMembershipDashPattern);

            painter->setPen(markPen);
            painter->drawPolyline(&(points[0]), points.size());
        } else {
            if (constType == Const) {
                if (permType == Temporary) {
                    pen.setDashPattern(msTempConstMembershipDashPattern);
                }
            }
            if (constType == Var) {
                if (permType == Permanent) {
                    pen.setDashPattern(msPermVarMembershipDashPattern);
                }
                if (permType == Temporary) {
                    pen.setDashPattern(msTempVarMembershipDashPattern);
                }
            }
            if (constType == Meta) {
                if (permType == Permanent) {
                    metaPen.setDashPattern(msPermVarMembershipDashPattern);
                    pen.setCapStyle(Qt::RoundCap);
                    pen.setWidthF(4.f);
                    pen.setDashPattern(metaMembershipDashPattern);
                }
                if (permType == Temporary) {
                    metaPen.setDashPattern(msTempVarMembershipDashPattern);
                    pen.setCapStyle(Qt::RoundCap);
                    pen.setWidthF(4.f);
                    pen.setDashPattern(metaMembershipDashPattern);
                }
                painter->setPen(metaPen);
                painter->drawPolyline(&(points[0]), points.size());
            }
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());
            // draw negative lines
            if (posType == Negative) {
                painter->setPen(markPen);

                QPainterPath path = pair->shapeNormal();
                float length = path.length() - arrowLength - 3;
                int i = 0;

                qreal mult = 32.f;
                qreal offset = 24.f;
                qreal l = offset;

                while (l < length) {
                    qreal perc = path.percentAtLength(l);

                    painter->save();
                    painter->translate(path.pointAtPercent(perc));
                    painter->rotate(-path.angleAtPercent(perc));
                    painter->drawLine(0.f, -LINE_MARK_NEG_LENGTH, 0.f, LINE_MARK_NEG_LENGTH);
                    painter->restore();

                    l = (++i) * mult + offset;
                }
            }
            // draw fuzzy lines
            if (posType == Fuzzy) {
                painter->setPen(markPen);

                QPainterPath path = pair->shapeNormal();
                float length = path.length() - arrowLength - 3;
                int i = 0;

                qreal mult = 32.f;
                qreal offset = 24.f;
                qreal l = offset;

                while (l < length) {
                    qreal perc = path.percentAtLength(l);
                    painter->save();
                    painter->translate(path.pointAtPercent(perc));
                    painter->rotate(-path.angleAtPercent(perc));
                    if (i % 2 == 0) painter->drawLine(0.f, -LINE_MARK_FUZ_LENGTH, 0.f, 0.f);
                    else painter->drawLine(0.f, LINE_MARK_FUZ_LENGTH, 0.f, 0.f);
                    painter->restore();

                    l = (++i) * mult + offset;
                }
            }
        }
    }else // draw binary pairs
    {
        if (constType == ConstUnknown)
        {
            pen.setWidthF(LINE_FAT_WIDTH);
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());
            pen.setWidthF(LINE_FATIN_WIDTH);
            pen.setColor(Qt::white);
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());
            pen.setWidthF(LINE_THIN_WIDTH);
            pen.setDashPattern(msPermVarMembershipDashPattern);
            pen.setColor(pair->color());
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());
        } else {
            if ((permType == Permanent) | (permType == PermUnknown)) {
                if (constType == Const) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
                if (constType == Var) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    pen.setDashPattern(msPermVarCommonDashPattern);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
                if (constType == Meta) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    pen.setDashPattern(msPermVarCommonDashPattern);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
            }
            if (permType == Temporary) {
                if (constType == Const) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    pen.setDashPattern(dottedDashPattern);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
                if (constType == Var) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    pen.setDashPattern(msTempVarCommonDashPattern);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
                if (constType == Meta) {
                    pen.setWidthF(LINE_FAT_WIDTH);
                    pen.setDashPattern(msTempVarCommonDashPattern);
                    painter->setPen(pen);
                    painter->drawPolyline(&(points[0]), points.size());
                }
            }
            QPen pen2(pair->color());
            pen2.setCapStyle(Qt::FlatCap);
            pen2.setJoinStyle(Qt::RoundJoin);
            pen2.setWidthF(LINE_FATIN_WIDTH);
            pen2.setColor(Qt::white);
            painter->setPen(pen2);
            painter->drawPolyline(&(points[0]), points.size());
            if (constType == Meta) {
                QPen pen2(pair->color());
                pen2.setCapStyle(Qt::RoundCap);
                pen2.setWidthF(4.f);
                pen2.setDashPattern(metaMembershipDashPattern);
                painter->setPen(pen2);
                painter->drawPolyline(&(points[0]), points.size());
            }
        }
    }
    if (pair->isOrient())
    {
        static const QPointF arrowPoints[4] = {QPointF(-arrowWidth / 2.f, 0.f),
                                               QPointF(0.f, arrowLength / 3),
                                               QPointF(arrowWidth / 2.f, 0.f),
                                               QPointF(0.f, arrowLength)};

        points.last() += QPointF((arrowLength/2) * ::sin(angle), (arrowLength/2) * ::cos(angle));
        // draw arrow for orient pairs
        QLineF line(points[points.size() - 2], points.last());

        painter->save();
        painter->translate(line.p2());
        painter->rotate(-angle * 180.f / M_PI);
        painter->translate(0.f, -arrowLength);

        painter->setBrush(QBrush(pair->color(), Qt::SolidPattern));
        painter->setPen(Qt::NoPen);
        painter->drawConvexPolygon(arrowPoints, 4);

        painter->restore();
    }
}

void SCgAlphabet::paintBus(QPainter *painter, SCgBus *bus)
{
    SCgBus::PointFVector points = bus->points();

    QPen pen(bus->color());
    pen.setWidthF(bus->getWidth());

    painter->setPen(pen);
    painter->drawPolyline(&(points[0]), points.size());
}

void SCgAlphabet::paintContour(QPainter *painter, SCgContour *contour)
{
    QPen pen(contour->color());
    pen.setWidthF(LINE_THIN_WIDTH);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::RoundJoin);



    if (contour->constType() == SCgAlphabet::Var) {
        if (contour->permType() == SCgAlphabet::Permanent) {
            pen.setDashPattern(msPermVarMembershipDashPattern);
        }
        else {
            pen.setDashPattern(msTempVarMembershipDashPattern);
        }
    }
    else {
        if (contour->permType() == SCgAlphabet::Permanent) {
            //leave standart pattern
        }
        else {
            pen.setDashPattern(msTempConstMembershipDashPattern);
        }
    }

    QBrush brush(contour->colorBack(), Qt::NoBrush);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawPath(contour->shapeNormal());
}
