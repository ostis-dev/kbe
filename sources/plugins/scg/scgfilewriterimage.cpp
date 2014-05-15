/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
    QRect rect = scene->itemsBoundingRect().toRect();

    QString isSVG = file_name.mid(file_name.length()-3);
   /* if(isSVG=="svg"){
         QSvgGenerator generator;
         generator.setFileName(file_name);
         generator.setSize(sz);
         generator.setViewBox(rect);
         //generator.setTitle(tr("SVG image for GWF"));
         generator.setDescription(tr("An SVG drawing created by Knowledge base Editor."));
         QPainter painter(&generator);
         painter.setRenderHint(QPainter::Antialiasing,true);
         scene->render(&painter,QRect(QPoint(0,0), sz),scene->itemsBoundingRect());
         return true;
     }
    else*/{
        QImage img(sz,QImage::Format_ARGB32_Premultiplied);
        if (!img.isNull())
        {
            QPainter painter(&img);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.eraseRect(QRect(QPoint(0,0),sz));
            scene->renderToImage(&painter, QRect(QPoint(0,0), sz), scene->itemsBoundingRect());
            return img.save(file_name);
        }
    }
    return false;
}

