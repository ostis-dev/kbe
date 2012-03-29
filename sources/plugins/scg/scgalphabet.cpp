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

#include "scgalphabet.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"

#include <math.h>

#define LINE_THIN_WIDTH 2.f
#define LINE_FAT_WIDTH 8.f
#define LINE_FATIN_WIDTH (LINE_FAT_WIDTH * 0.6f)

#define LINE_MARK_NEG_LENGTH  4.f
#define LINE_MARK_FUZ_LENGTH  5.f

SCgAlphabet* SCgAlphabet::mInstance = 0;

QVector<qreal> SCgAlphabet::msPermVarAccesDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msPermVarNoAccesDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempConstAccesDashPattern = QVector<qreal>();
QVector<qreal> SCgAlphabet::msTempVarAccesDashPattern = QVector<qreal>();


SCgAlphabet::SCgAlphabet(QObject *parent) :
    QObject(parent)
{

}

SCgAlphabet& SCgAlphabet::getInstance()
{
    if (!mInstance)
    {
        mInstance = new SCgAlphabet;
        mInstance->initialize();
    }

    return *mInstance;
}

void SCgAlphabet::initialize()
{
    mConstTypes["const"] = Const;
    mConstTypes["var"] = Var;

    mAlias2ConstType.push_back("const");
    mAlias2ConstType.push_back("var");

    mPosTypes["pos"] = Positive;
    mPosTypes["neg"] = Negative;
    mPosTypes["fuz"] = Fuzzy;

    mPermTypes["perm"] = Permanent;
    mPermTypes["temp"] = Temporary;
    mPermTypes["any"] = PermAny;

    mStructTypes["not_define"] = NotDefine;
    mStructTypes["general_node"] = General;
    mStructTypes["predmet"] = Predmet;
    mStructTypes["nopredmet"] = NoPredmet;
    mStructTypes["symmetry"] = Symmetry;
    mStructTypes["asymmetry"] = Asymmetry;
    mStructTypes["attribute"] = Attribute;
    mStructTypes["relation"] = Relation;
    mStructTypes["atom"] = Atom;
    mStructTypes["group"] = Group;

    // initiliaze patterns
    msPermVarAccesDashPattern << 16 / LINE_THIN_WIDTH
                              << 12 / LINE_THIN_WIDTH;
    msPermVarNoAccesDashPattern << 8 / LINE_FATIN_WIDTH
                                << 23 / LINE_FATIN_WIDTH;
    qreal temp_dash = 2 / LINE_THIN_WIDTH;
    msTempConstAccesDashPattern << temp_dash
                                << temp_dash
                                << temp_dash
                                << temp_dash;
    msTempVarAccesDashPattern << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << temp_dash
                              << 7 * temp_dash;

    QSize size(24, 24);

    mObjectTypes["node/const/not_define"] = createNodeIcon(size, Const, NotDefine);
    mObjectTypes["node/const/general_node"] = createNodeIcon(size, Const, General);
    mObjectTypes["node/const/predmet"] = createNodeIcon(size, Const, Predmet);
    mObjectTypes["node/const/nopredmet"] = createNodeIcon(size, Const, NoPredmet);
    mObjectTypes["node/const/symmetry"] = createNodeIcon(size, Const, Symmetry);
    mObjectTypes["node/const/asymmetry"] = createNodeIcon(size, Const, Asymmetry);
    mObjectTypes["node/const/attribute"] = createNodeIcon(size, Const, Attribute);
    mObjectTypes["node/const/relation"] = createNodeIcon(size, Const, Relation);
    mObjectTypes["node/const/atom"] = createNodeIcon(size, Const, Atom);
    mObjectTypes["node/const/group"] = createNodeIcon(size, Const, Group);

    mObjectTypes["node/var/not_define"] = createNodeIcon(size, Var, NotDefine);
    mObjectTypes["node/var/general_node"] = createNodeIcon(size, Var, General);
    mObjectTypes["node/var/predmet"] = createNodeIcon(size, Var, Predmet);
    mObjectTypes["node/var/nopredmet"] = createNodeIcon(size, Var, NoPredmet);
    mObjectTypes["node/var/symmetry"] = createNodeIcon(size, Var, Symmetry);
    mObjectTypes["node/var/asymmetry"] = createNodeIcon(size, Var, Asymmetry);
    mObjectTypes["node/var/attribute"] = createNodeIcon(size, Var, Attribute);
    mObjectTypes["node/var/relation"] = createNodeIcon(size, Var, Relation);
    mObjectTypes["node/var/atom"] = createNodeIcon(size, Var, Atom);
    mObjectTypes["node/var/group"] = createNodeIcon(size, Var, Group);


    QSize pairSize(24, 24);

    mObjectTypes["pair/const/pos/perm/orient/accessory"] = createPairIcon(pairSize, "pair/const/pos/perm/orient/accessory");
    mObjectTypes["pair/const/neg/perm/orient/accessory"] = createPairIcon(pairSize, "pair/const/neg/perm/orient/accessory");
    mObjectTypes["pair/const/fuz/perm/orient/accessory"] = createPairIcon(pairSize, "pair/const/fuz/perm/orient/accessory");
    mObjectTypes["pair/const/pos/temp/orient/accessory"] = createPairIcon(pairSize, "pair/const/pos/temp/orient/accessory");
    mObjectTypes["pair/const/neg/temp/orient/accessory"] = createPairIcon(pairSize, "pair/const/neg/temp/orient/accessory");
    mObjectTypes["pair/const/fuz/temp/orient/accessory"] = createPairIcon(pairSize, "pair/const/fuz/temp/orient/accessory");
    mObjectTypes["pair/const/-/-/noorien"] = createPairIcon(pairSize, "pair/const/-/-/noorien");
    mObjectTypes["pair/const/-/-/orient"] = createPairIcon(pairSize, "pair/const/-/-/orient");

    mObjectTypes["pair/var/pos/perm/orient/accessory"] = createPairIcon(pairSize, "pair/var/pos/perm/orient/accessory");
    mObjectTypes["pair/var/neg/perm/orient/accessory"] = createPairIcon(pairSize, "pair/var/neg/perm/orient/accessory");
    mObjectTypes["pair/var/fuz/perm/orient/accessory"] = createPairIcon(pairSize, "pair/var/fuz/perm/orient/accessory");
    mObjectTypes["pair/var/pos/temp/orient/accessory"] = createPairIcon(pairSize, "pair/var/pos/temp/orient/accessory");
    mObjectTypes["pair/var/neg/temp/orient/accessory"] = createPairIcon(pairSize, "pair/var/neg/temp/orient/accessory");
    mObjectTypes["pair/var/fuz/temp/orient/accessory"] = createPairIcon(pairSize, "pair/var/fuz/temp/orient/accessory");
    mObjectTypes["pair/var/-/-/noorien"] = createPairIcon(pairSize, "pair/var/-/-/noorien");
    mObjectTypes["pair/var/-/-/orient"] = createPairIcon(pairSize, "pair/var/-/-/orient");

}

QIcon SCgAlphabet::createNodeIcon(const QSize &size, const SCgConstType &type_const,
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
                      type_const, type_struct);
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

void SCgAlphabet::getNodeTypes(SCgConstType type, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("node", type, res);
}

void SCgAlphabet::getPairTypes(SCgConstType type, SCgAlphabet::SCgObjectTypesMap &res)
{
    getObjectTypes("pair", type, res);
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

void SCgAlphabet::paintNode(QPainter *painter, const QColor &color, const QRectF &boundRect,
                            const SCgConstType &type, const SCgNodeStructType &type_struct)
{

    QColor brush_color =  QColor(255, 255, 255, 224);
    // to draw not defined nodes we just need to scale them
    if (type_struct == NotDefine)
    {
        painter->scale(0.3f, 0.3f);
        brush_color = color;
        brush_color.setAlpha(224);
    }


    // drawing of border
    QPen pen = QPen(QBrush(color, Qt::SolidPattern), 4, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush = QBrush(brush_color, Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);

    QRectF bound = boundRect.adjusted(2, 2, -2, -2);

    if (type == Const)
    {
        painter->drawEllipse(bound);

        QPainterPath clipPath;
        clipPath.addEllipse(bound.adjusted(1,1,-1,-1));
        painter->setClipPath(clipPath, Qt::IntersectClip);

        paintStruct(painter, color, bound, type_struct);
    }else
    {
        if (type == Var)
        {
            painter->scale(0.9f, 0.9f);
            painter->drawRect(bound);

            QPainterPath clipPath;
            clipPath.addRect(bound);
            painter->setClipPath(clipPath, Qt::IntersectClip);
            paintStruct(painter, color, bound, type_struct);
        }

    }
}

void SCgAlphabet::paintStruct(QPainter *painter, const QColor &color,
                              const QRectF &boundRect, const SCgNodeStructType &type)
{
    QPen pen = QPen(QBrush(color, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    painter->setPen(pen);

    // structure types
    QPointF c, d;
    switch (type)
    {
    case NoPredmet:
        float w, h;
        w = boundRect.width() / 10.f;
        h = boundRect.height() / 10.f;
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawEllipse(-w, -h, w * 2 - 1, h * 2 - 1);
        painter->setBrush(QBrush(Qt::NoBrush));
        break;

    case Predmet:
    {
        QPen p = painter->pen();
        p.setWidthF(0);
        painter->setPen(p);
        qreal x1, x2, top, bottom;
        top = boundRect.top() + 3.4;
        bottom = boundRect.bottom() - 3.5;
        x1 = boundRect.left();
        x2 = boundRect.right();

        for (qreal y = top; y < bottom; y += 2)
            painter->drawLine(QLineF(x1, y, x2, y));
        break;
    }
    case Symmetry:
        c = boundRect.center();
        d = QPointF(0.f, boundRect.height() / 2.0);
        painter->drawLine(c - d, c + d);
        break;

    case Asymmetry:
        c = boundRect.center();
        d = QPointF(boundRect.width() / 2.0, 0.f);
        painter->drawLine(c - d, c + d);
        break;

    case Attribute:
        c = boundRect.center();
        d = QPointF(boundRect.width() / 2.0, 0.f);
        painter->drawLine(c - d, c + d);
        d = QPointF(0.f, boundRect.height() / 2.0);
        painter->drawLine(c - d, c + d);
        break;

    case Relation:
        painter->drawLine(boundRect.topLeft(), boundRect.bottomRight());
        painter->drawLine(boundRect.topRight(), boundRect.bottomLeft());
        break;

    case Atom:
        break;

    case Group:
        painter->drawLine(boundRect.topLeft(), boundRect.bottomRight());
        painter->drawLine(boundRect.topRight(), boundRect.bottomLeft());
        painter->drawLine(boundRect.left(), boundRect.center().y(), boundRect.right(), boundRect.center().y());
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

    static float arrowLength = 10.f;
    static float arrowWidth = LINE_FAT_WIDTH;

    if (pair->isOrient())
    {

        static const QPointF arrowPoints[3] = {QPointF(-arrowWidth / 2.f, 0.f),
                                               QPointF(arrowWidth / 2.f, 0.f),
                                               QPointF(0.f, arrowLength)};

        // draw arrow for orient pairs
        QLineF line(points[points.size() - 2], points.last());
        double angle = ::atan2(line.dx(), line.dy());

        painter->save();
        painter->translate(line.p2());
        painter->rotate(-angle * 180.f / M_PI);
        painter->translate(0.f, -arrowLength);

        painter->setBrush(QBrush(pair->color(), Qt::SolidPattern));
        painter->setPen(Qt::NoPen);
        painter->drawConvexPolygon(arrowPoints, 3);

        painter->restore();

        // correct last point
        points.last() -= QPointF((arrowLength) * ::sin(angle), (arrowLength) * ::cos(angle));
    }

    // get type data
    SCgPosType posType = pair->getPosType();
    SCgConstType constType = pair->getConstType();
    SCgPermType permType = pair->getPermType();

    painter->setBrush(Qt::NoBrush);

    QPen pen(pair->color());
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::RoundJoin);

    // draw all cases
    if (pair->isAccessory())
    {       
        pen.setWidthF(LINE_THIN_WIDTH);
        QPen markPen = pen;


        if (permType == Permanent && constType == Var)
            pen.setDashPattern(msPermVarAccesDashPattern);

        if (permType == Temporary)
        {
            if (constType == Const)
                pen.setDashPattern(msTempConstAccesDashPattern);
            else
                pen.setDashPattern(msTempVarAccesDashPattern);
        }

        painter->setPen(pen);
        painter->drawPolyline(&(points[0]), points.size());

        // draw negative lines
        if (posType == Negative)
        {
            painter->setPen(markPen);

            QPainterPath path = pair->shapeNormal();
            float length = path.length() - arrowLength - 3;
            int i = 0;

            qreal mult = (permType == Temporary) ? 28.f : 28.f;
            qreal offset = (permType == Temporary) ? 20.f : 22.f;
            qreal l = offset;

            while (l < length)
            {
                qreal perc = path.percentAtLength(l);

                painter->save();
                painter->translate(path.pointAtPercent(perc));
                painter->rotate(-path.angleAtPercent(perc));
                painter->drawLine(0.f, -LINE_MARK_NEG_LENGTH, 0.f, LINE_MARK_NEG_LENGTH);
                painter->restore();

                l = (++i) * mult + offset;
            }

        }else   // draw fuzzy lines
            if (posType == Fuzzy)
            {
                painter->setPen(markPen);

                QPainterPath path = pair->shapeNormal();
                float length = path.length() - arrowLength - 3;
                int i = 0;

                qreal mult = (permType == Temporary) ? 28.f : 28.f;
                qreal offset = (permType == Temporary) ? 20.f : 22.f;
                qreal l = offset;

                while (l < length)
                {
                    qreal perc = path.percentAtLength(l);

                    painter->save();
                    painter->translate(path.pointAtPercent(perc));
                    painter->rotate(-path.angleAtPercent(perc));

                    if (i % 2 == 0)
                        painter->drawLine(0.f, -LINE_MARK_FUZ_LENGTH, 0.f, 0.f);
                    else
                        painter->drawLine(0.f, LINE_MARK_FUZ_LENGTH, 0.f, 0.f);
                    painter->restore();

                    l = (++i) * mult + offset;
                }
            }

    }else // draw binary pairs
    {
        pen.setWidthF(LINE_FAT_WIDTH);

        if (constType == Var)
        {
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());

            pen.setWidthF(LINE_FATIN_WIDTH);
            pen.setDashPattern(msPermVarNoAccesDashPattern);
            pen.setDashOffset(11 / LINE_FATIN_WIDTH);
            pen.setColor(QColor(255, 255, 255));
            painter->setPen(pen);
            painter->drawPolyline(&(points[0]), points.size());
        }else
        {
            if (constType == Const)
            {
                painter->setPen(pen);
                painter->drawPolyline(&(points[0]), points.size());

                pen.setWidthF(LINE_FATIN_WIDTH);
                pen.setColor(Qt::white);
                painter->setPen(pen);
                painter->drawPolyline(&(points[0]), points.size());
            }
        }
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
    SCgContour::PointFVector points = contour->points();

    QPen pen(contour->color());
    pen.setWidthF(LINE_THIN_WIDTH);
    pen.setJoinStyle(Qt::RoundJoin);

    QBrush brush(contour->colorBack(), Qt::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawPolygon(&(points[0]), points.size(), Qt::OddEvenFill);
}
