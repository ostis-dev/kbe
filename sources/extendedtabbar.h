#ifndef EXTENDEDTABBAR_H
#define EXTENDEDTABBAR_H

#include <QTabBar>

class ExtendedTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit ExtendedTabBar(QWidget *parent = 0);
    virtual ~ExtendedTabBar();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // EXTENDEDTABBAR_H
