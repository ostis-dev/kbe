#ifndef SCGPRINT_H
#define SCGPRINT_H

#include <QObject>
#include <QPrinter>
#include "scgscene.h"

class scgprint : public QObject
{
    Q_OBJECT
public:
    explicit scgprint(QObject *parent = 0);

    void print(SCgScene *, QPrinter &);

private:
    SCgScene *scene;

signals:

public slots:

};

#endif // SCGPRINT_H
