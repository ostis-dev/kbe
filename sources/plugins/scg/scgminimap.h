/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QGraphicsView>

class SCgView;

class QGraphicsScene;
class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QDragMoveEvent;
class QRubberBand;

class SCgMinimap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SCgMinimap(SCgView *view, QWidget *parent = 0);

    virtual ~SCgMinimap();
protected:
    void resizeEvent(QResizeEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    bool eventFilter(QObject* watched, QEvent* event);

    void drawBackground (QPainter* painter, const QRectF & rect);

    signals:

protected slots:
    //! Scene rect changed event
    void sceneRectChanged(const QRectF & rect);
    //! called, if visible area has changed.
    void updateViewedArea(int val = 0);

private:
    SCgView* mView;
    //TODO: Better subclass QRubberBand and set its own palette(green) instead.
    QRubberBand* mMarker;
};


