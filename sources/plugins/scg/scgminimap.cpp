/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgminimap.h"
#include "scgview.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QScrollBar>
#include <QDragMoveEvent>
#include <QRubberBand>
#include <QPaintEvent>

SCgMinimap::SCgMinimap(SCgView *view, QWidget *parent) :
    QGraphicsView(parent),
    mView(view),
    mMarker(0)
{

    Q_ASSERT_X(view != 0,
               "SCgMinimap::SCgMinimap(QGraphicsScene *scene, QWidget *parent)",
               "Graphics scene is null");

    mMarker = new QRubberBand( QRubberBand::Rectangle, viewport());
    mMarker->show();

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::SmoothPixmapTransform);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(false);
    setMaximumSize(600,400);
    resize(150,150);

    setScene(mView->scene());

    //keep eye on sliders positions.
    connect(mView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateViewedArea(int)));
    connect(mView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateViewedArea(int)));
    //watching for the sceneRect changes
    connect(mView, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(sceneRectChanged(QRectF)));

    updateViewedArea();

    //Event filter handles only watched vews's resize events.
    mView->viewport()->installEventFilter(this);
}

SCgMinimap::~SCgMinimap()
{

}

bool SCgMinimap::eventFilter(QObject* watched, QEvent* event)
{
    if(event->type() == QEvent::Resize)
        updateViewedArea();

    return QGraphicsView::eventFilter(watched, event);
}

void SCgMinimap::updateViewedArea(int val)
{
    Q_UNUSED(val);

    QPointF topLeft = mapFromScene(mView->mapToScene(0,0));
    QPointF bottomRight = mapFromScene(mView->mapToScene(mView->viewport()->width(),mView->viewport()->height()));
    QRectF sceneR = mView->sceneRect();
    QRectF maxSize = QRectF(mapFromScene(sceneR.topLeft()), mapFromScene(sceneR.bottomRight()));
    QRectF resultRect = maxSize & QRectF(topLeft, bottomRight);
    mMarker->setGeometry(resultRect.toRect());
}


void SCgMinimap::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    sceneRectChanged(mView->sceneRect());
}

void SCgMinimap::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
        mView->centerOn(mapToScene(event->pos()));
}

void SCgMinimap::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (event->buttons() & Qt::LeftButton)
        mView->centerOn(mapToScene(event->pos()));
}

void SCgMinimap::sceneRectChanged(const QRectF &rect)
{
    setSceneRect(rect);
    fitInView(rect, Qt::KeepAspectRatio);
    updateViewedArea();
    update();
}

void SCgMinimap::drawBackground ( QPainter * painter, const QRectF & rect )
{
    Q_UNUSED(rect);
    painter->drawRect(mView->sceneRect());
}
