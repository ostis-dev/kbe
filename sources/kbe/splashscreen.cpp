#include "splashscreen.h"
#include <QStyle>
#include <QStyleOptionProgressBar>

#include <QDebug>

SplashScreen::SplashScreen(const QPixmap &pixmap, Qt::WindowFlags f) :
    QSplashScreen(pixmap, f),
    mAllProgress(0),
    mPluginLoadingProgress(0)
{
}

SplashScreen::SplashScreen(QWidget *parent, const QPixmap &pixmap, Qt::WindowFlags f) :
    QSplashScreen(parent, pixmap, f),
    mAllProgress(0),
    mPluginLoadingProgress(0)

{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::drawContents(QPainter *painter)
{
    qDebug()<<"redraw";
    QSplashScreen::drawContents(painter);
    QStyleOptionProgressBar opt1, opt2;
    opt1.direction = Qt::LeftToRight;
    opt1.minimum = 0;
    opt1.maximum = 100;
    opt1.progress = mAllProgress;
    QPoint topLeft = rect().adjusted(0, 0, 0, -55).bottomLeft();
    QSize progressSize = QSize(rect().width(), 15);
    QRect r = QRect(topLeft, progressSize);
    opt1.rect = r;
    style()->drawControl(QStyle::CE_ProgressBarGroove, &opt1, painter);
    style()->drawControl(QStyle::CE_ProgressBarContents, &opt1, painter);

    opt2.direction = Qt::LeftToRight;
    opt2.minimum = 0;
    opt2.maximum = 100;
    opt2.progress = mPluginLoadingProgress;
    opt2.rect = QRect(topLeft + QPoint(0, 18), progressSize);
    style()->drawControl(QStyle::CE_ProgressBarGroove, &opt2, painter);
    style()->drawControl(QStyle::CE_ProgressBarContents, &opt2, painter);
}

void SplashScreen::setProgressAll(const quint8 progress)
{
    mAllProgress = progress;
    repaint();
}

void SplashScreen::setPluginProgress(const quint8 progress)
{
    mPluginLoadingProgress = progress;
    qDebug()<<progress;
    repaint();
}
