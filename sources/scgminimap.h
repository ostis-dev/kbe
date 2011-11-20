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

#ifndef SCGMINIMAP_H
#define SCGMINIMAP_H

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

#endif // SCGMINIMAP_H
