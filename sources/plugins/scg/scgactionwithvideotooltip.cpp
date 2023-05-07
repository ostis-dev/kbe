#include "scgactionwithvideotooltip.h"

#include <QApplication>
#include <QToolTip>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>
#include <unistd.h>


ActionWithVideoTooTip::ActionWithVideoTooTip(const QString text, const QString& gifPath,QWidget *parent) : QWidget(parent)
{
    wid = new QWidget();
    wid->setWindowOpacity(0.8);
    movie = new QMovie(gifPath);
    label = new QLabel();
    QLabel* about = new QLabel();
    about->setText(text);
    about->setStyleSheet("color: white;");
    label->setFixedSize(330, 200);
    QVBoxLayout * mainLayout = new QVBoxLayout();
    label->setMovie(movie);

    mainLayout->addWidget(label);
    mainLayout->addWidget(about);
    wid->setLayout(mainLayout);
    wid->setWindowFlags(Qt::FramelessWindowHint);
    wid->setStyleSheet("background-color: black;");
    wid->hide();
}

//overriding event method to catch if tooltip requested
bool ActionWithVideoTooTip::event(QEvent *event)
{
    //filter events
    if (event->type() == QEvent::ToolTip){

    // Set the size of the widget to the size of the movie
    //set timeout before show
    sleep(0.4);
    // start animation
    movie->start();
    // get cursor position
    QPoint pl = QCursor::pos();
    //move widget avay from QAction
    wid->move(pl.rx()+15, pl.ry());
    wid->show();
    }
    if(event->type()==QEvent::Leave)
    {
        //hide widget when tooltip dont need anymore
        movie->stop();
        wid->hide();
    }
    // return parent method
    return QWidget::event(event);
}
