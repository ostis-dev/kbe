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

#include "scgminimap.h"
#include "scgview.h"

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QHBoxLayout>
#include <QPaintEvent>
#include <QtWidgets/QGraphicsRectItem>
#include <QBrush>
#include <QtWidgets/QScrollBar>
#include <QDragMoveEvent>
#include <QtWidgets/QRubberBand>
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
    painter->drawRect(mView->sceneRect());
}
