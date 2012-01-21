#include "extendedtabbar.h"
#include <QDropEvent>

ExtendedTabBar::ExtendedTabBar(QWidget *parent) :
    QTabBar(parent)
{
    setAcceptDrops(true);
}

ExtendedTabBar::~ExtendedTabBar() {}

void ExtendedTabBar::contextMenuEvent(QContextMenuEvent *event) {
    QTabBar::contextMenuEvent(event);
}

void ExtendedTabBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) emit tabCloseRequested(currentIndex());
    QTabBar::mousePressEvent(event);
}
