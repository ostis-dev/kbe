/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgnode.h"

#include "scgcontentfactory.h"
#include "scgcontentviewer.h"
#include "scgbus.h"
#include "scgview.h"
#include "scgnodetextitem.h"
#include "scgconfig.h"

#include <QPainter>
#include <QVector2D>
#include <QGraphicsScene>
#include <QGraphicsView>

#define DEFAULT_IDTF_POS BottomRight

SCgNode::SCgNode(QGraphicsItem *parent) :
    SCgObject(parent),
    SCgContent(),
    mStructType(SCgAlphabet::StructUnknown),
    mIsContentVisible(false),
    mContentViewer(0),
    mBus(0)
{
    mSize = QSizeF(19.f, 19.f);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setToolTip(QObject::tr("sc.g-node"));
    setZValue(2);
}

SCgNode::~SCgNode()
{
    //Q_ASSERT(!mBus);    // must be deleted before
    if (mContentViewer)
    {
        delete mContentViewer;
        mContentViewer = 0;
    }

    if (mBus)
    {
    	mBus->setOwner(0);
    	mBus = 0;
    }
}

void SCgNode::setTypeAlias(const QString &typeAlias)
{
    SCgObject::setTypeAlias(typeAlias);
    updateType();
}

SCgAlphabet::SCgNodeStructType SCgNode::structType() const
{
    return mStructType;
}

void SCgNode::updateType()
{    
    /* updating information based on type alias */
    QStringList sl = mTypeAlias.split("/");

    Q_ASSERT(sl.size() > 1);
    if (sl.size() > 3) {
        mConstType = SCgAlphabet::getInstance().aliasToConstCode(sl[1]);
        mPermType = SCgAlphabet::getInstance().aliasToPermanencyCode(sl[2]);
        mStructType = SCgAlphabet::getInstance().aliasToStructCode(sl[3]);
    }
    else {
        mConstType = SCgAlphabet::getInstance().aliasToConstCode(sl[1]);
        mPermType = SCgAlphabet::Permanent;
        mStructType = SCgAlphabet::getInstance().aliasToStructCode(sl[2]);
    }
}

QRectF SCgNode::boundingRect() const
{
    QRectF res;

    if (!mIsContentVisible)
    {
        res = QRectF(-mSize.width() / 2.f, -mSize.height() / 2.f, mSize.width(), mSize.height());
    }else
    {
        Q_ASSERT(mContentViewer);

        QSizeF size = mContentViewer->size();
        res = QRectF(0, 0, size.width(), size.height());
        res.moveCenter(QPointF(0.f, 0.f));
        res.adjust(-5, -5, 5, 5);
    }

    return res;
}

QPainterPath SCgNode::shape() const
{
    QPainterPath path;
    QRectF boundRect = boundingRect();

    if (mIsContentVisible)
    {
        path.addRect(boundRect);
    }else
    {
        QMatrix matrix;
        switch (mConstType)
        {
        case SCgAlphabet::Const:
        case SCgAlphabet::ConstUnknown:
            path.addEllipse(boundRect);
            break;

        case SCgAlphabet::Var:
            path.addRect(boundRect);
            break;
        case SCgAlphabet::Meta:
            path.moveTo(boundRect.center().x(), boundRect.top());
            path.lineTo(boundRect.right(), boundRect.center().y());
            path.lineTo(boundRect.center().x(), boundRect.bottom());
            path.lineTo(boundRect.left(), boundRect.center().y());
            path.lineTo(boundRect.center().x(), boundRect.top());
            break;
        default:
            break;
        }
    }

    return path;
}

QVariant SCgNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (mBus && !mBus->isDead() && change == QGraphicsItem::ItemParentHasChanged)
    {
        mBus->setParentItem(parentItem());
        updateConnected();
    }

    return SCgObject::itemChange(change, value);
}

void SCgNode::positionChanged()
{
}

void SCgNode::objectDelete(SCgObject *object)
{
    Q_UNUSED(object);
    if (mBus)
        mBus->setOwner(0);
}

void SCgNode::del(QList<SCgObject*> &delList)
{
    if(mIsContentVisible)
        mContentViewer->hide();

    if(mBus)
        mBus->del(delList);

    SCgObject::del(delList);
}

void SCgNode::undel(SCgScene* scene)
{
    if(mBus)
        mBus->undel(scene);

    SCgObject::undel(scene);
    if(mIsContentVisible)
        mContentViewer->show();
}

QPointF SCgNode::cross(const QPointF &from, float dot) const
{
    Q_UNUSED(dot);

    QPointF p(0.f, 0.f);

    if (!mIsContentVisible)
    {
        QVector2D vec(from - scenePos());
        p = vec.normalized().toPointF() * (mSize.width() / 2.f);
    }else
    {

        // count intersection with content border
        QPolygonF polygon(boundingRect());
        QPointF p1 = polygon.last();
        QPointF p2, intersectPoint;
        QLineF line, pair(p, mapFromScene(from));
        bool haveItersect = false;

        for (int i = 0; i < polygon.size(); i++)
        {
            p2 = polygon.at(i);
            line = QLineF(p1, p2);
            QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
            {
                haveItersect = true;
                break;
            }

            p1 = p2;
        }
        p = haveItersect ? intersectPoint : p;
    }

    return mapToScene(p);
}

float SCgNode::dotPos(const QPointF &point) const
{
    Q_UNUSED(point);
    return 0.f;
}

void SCgNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* need to rebuild that code to more flexible.
       Just for example make drawers class for different types.
     */

    QRectF boundRect = boundingRect();

    if (!mIsContentVisible)
    {
        painter->save();
        SCgAlphabet::getInstance().paintNode(painter, mColor, boundRect, mConstType, mPermType,  mStructType);
        painter->restore();

        if (isContentData())
        {
            QBrush brush(QColor(128, 0, 255), Qt::SolidPattern);
            painter->setBrush(brush);

            painter->drawRect(boundRect.right() - 5, boundRect.bottom() - 5, 5, 5);
        }
    }else
    {
        //here add pattern
        QPen pen(mColor);
        pen.setWidthF(3.f);
        pen.setCapStyle(Qt::FlatCap);
        pen.setJoinStyle(Qt::RoundJoin);
        if (mConstType == SCgAlphabet::Var) {
                if (mPermType == SCgAlphabet::Permanent) {
                    pen.setDashPattern(SCgAlphabet::getMsPermVarMembershipDashPattern());
                }
                else {
                    pen.setDashPattern(SCgAlphabet::getMsTempVarMembershipDashPattern());
                }
            }
            else {
                if (mPermType == SCgAlphabet::Permanent) {
                    //leave standart pattern
                }
                else {
                    pen.setDashPattern(SCgAlphabet::getMsTempConstMembershipDashPattern());
                }
            }

        painter->setPen(pen);
        painter->drawRect(boundRect.adjusted(2, 2, -2, -2));
    }

    SCgObject::paint(painter, option, widget);

    // draw content corner
    if (mIsContentVisible)
    {
        QRectF rc = boundRect.adjusted(2, 2, -2, -2);
        QPolygonF polygon;
        polygon.append(rc.topLeft());
        polygon.append(QPointF(rc.left() + 10, rc.top()));
        polygon.append(QPointF(rc.left(), rc.top() + 10));

        QPainterPath path;
        path.addPolygon(polygon);
        path.closeSubpath();

        painter->fillPath(path, QBrush(mColor));

    }
}

void SCgNode::updateConnected()
{
    SCgObject::updateConnected();
    if (mBus && !mBus->isDead())
        mBus->positionChanged();
}

void SCgNode::setContent(const QString& mimeType, const QVariant& data,
                         const QString& fileName, SCgContent::ContType cType)
{
    SCgContent::setContent(mimeType, data, fileName, cType);
    updateContentViewer();
    emit(contentChanged());
}

void SCgNode::showContent()
{
    Q_ASSERT(!mIsContentVisible && mContentViewer);

    prepareGeometryChange();

    mIsContentVisible = true;
    updateConnected();

    mContentViewer->show();
    update();
}

void SCgNode::hideContent()
{
    Q_ASSERT(mIsContentVisible && mContentViewer);

    prepareGeometryChange();

    mIsContentVisible = false;
    updateConnected();

    mContentViewer->hide();
    update();
}

bool SCgNode::isContentVisible() const
{
    return mIsContentVisible;
}


void SCgNode::updateContentViewer()
{
    bool isCntVis = mIsContentVisible;

    if(isCntVis)
        hideContent();

    if (mContentViewer != 0)
    {
        delete mContentViewer;
        mContentViewer = 0;
    }

    if (!contentType() == SCgContent::Empty)
    {
        // creating new viewer
        if (!mContentViewer) mContentViewer = SCgContentFactory::createViewer(contentFormat());
        Q_ASSERT(mContentViewer);

        mContentViewer->setData(contentData());
        mContentViewer->setParentItem(this);

        if (isCntVis)
            showContent();
    }
    update();
}

bool SCgNode::isContentData() const
{
    return mContentViewer != 0;
}

SCgBus* SCgNode::bus() const
{
    return mBus;
}

void SCgNode::setBus(SCgBus *bus)
{
    mBus = bus;
}


void SCgNode::setIdtfValue(const QString &idtf)
{
    mIdtfValue = idtf;
    if (idtf != "")
    {
        if (!mTextItem)
        {
            mTextItem = new SCgNodeTextItem(idtf,this);

            QFont font("Times New Roman", 10, 10, false);
            font.setBold(true);
            font.setItalic(true);

            mTextItem->setFont(font);
            mTextItem->setParentItem(this);
            mTextItem->setZValue(7);
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_text_element_color_normal));
        }

        mTextItem->setPlainText(mIdtfValue);
    }
    else if (mTextItem)
    {
        delete mTextItem;
        mTextItem = 0;
    }

    positionChanged();
}

SCgNode::IdentifierPosition SCgNode::idtfPos() const
{
    if (!mTextItem)
        return DEFAULT_IDTF_POS;

    SCgNodeTextItem* pItem = static_cast<SCgNodeTextItem*>(mTextItem);
    Q_CHECK_PTR(pItem);

    if (pItem)
        return pItem->nodeTextPos();

    return DEFAULT_IDTF_POS;
}


void SCgNode::setIdtfPos(IdentifierPosition pos)
{
    if (!mTextItem)
        return;

    SCgNodeTextItem* pItem = static_cast<SCgNodeTextItem*>(mTextItem);
    Q_CHECK_PTR(pItem);

    if (pItem)
        pItem->setNodeTextPos(pos);
}
