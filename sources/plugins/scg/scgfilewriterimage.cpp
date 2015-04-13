/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgfilewriterimage.h"
#include "scgscene.h"

#include <QImage>
#include <QPainter>
#include <QImageWriter>
#include <QSize>
#include <QRect>
#include <QWidget>
//#include <QSvgGenerator>

SCgFileWriterImage::SCgFileWriterImage()
{
}

bool SCgFileWriterImage::save(QString file_name, QObject *input)
{
    SCgScene *scene = qobject_cast<SCgScene*>(input);

    QSize sz = scene->itemsBoundingRect().size().toSize();

    QString isSVG = file_name.mid(file_name.length()-3);
    QImage img(sz,QImage::Format_ARGB32_Premultiplied);
    if (!img.isNull())
    {
        QPainter painter(&img);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.eraseRect(QRect(QPoint(0,0),sz));
        scene->renderToImage(&painter, QRect(QPoint(0,0), sz), scene->itemsBoundingRect());
        return img.save(file_name);
    }

    return false;
}

