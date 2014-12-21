#include "scgprint.h"

scgprint::scgprint(QObject *parent) :
    QObject(parent)
{
}

void scgprint::print(SCgScene *scene, QPrinter &printer)
{
    qreal heightCount = scene->itemsBoundingRect().height() / printer.height();
    qreal widthCount = scene->itemsBoundingRect().width() / printer.width();

    int heightPagesCount = (heightCount - (int)heightCount) > 0 ? (int)heightCount + 1 : (int)heightCount;
    int widthPagesCount = (widthCount - (int)widthCount) > 0 ? (int)widthCount + 1 : (int)widthCount;

    QPainter painter;

    QSize sz = scene->itemsBoundingRect().size().toSize();

    painter.begin(&printer);

    for (int xPage = 0; xPage < widthPagesCount; xPage++)
    {
        for (int yPage = 0; yPage < heightPagesCount; yPage++)
        {
            if (xPage > 0 || yPage > 0)
            {
                printer.newPage();
            }

            scene->renderToImage(&painter, QRect(0 - (printer.width() * xPage), 0 - (printer.height() * yPage), sz.width(), sz.height()), scene->itemsBoundingRect());
        }
    }

    painter.end();
}
