#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen(const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = 0);
    explicit SplashScreen(QWidget *parent, const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = 0);
    virtual ~SplashScreen();
protected:
    void drawContents(QPainter *painter);
private:
    quint8 mAllProgress;
    quint8 mPluginLoadingProgress;
signals:
    
public slots:
    void setProgressAll(const quint8 progress);
    void setPluginProgress(const quint8 progress);
};

#endif // SPLASHSCREEN_H
