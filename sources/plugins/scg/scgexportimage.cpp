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

#include "scgexportimage.h"
#include "scgscene.h"

#include <QImageWriter>

SCgExportImage::SCgExportImage(QObject *parent) :
    QObject(parent)
{
}

SCgExportImage::~SCgExportImage()
{

}

QStringList SCgExportImage::supportedFormats() const
{
    QList<QByteArray> src = QImageWriter::supportedImageFormats();
    QStringList res;
    foreach(const QByteArray& ext,src)
        res.push_back(ext.data());

    return res;
}

bool SCgExportImage::doExport(SCgScene *scene, const QString &fileName)
{
    QList<QGraphicsItem*> allItems = scene->items();
    foreach (QGraphicsItem *item, allItems)
    {
        item->setSelected(false);
        item->clearFocus();
    }
    QSize sz = scene->itemsBoundingRect().size().toSize();
    QSize imgSize(sz.width() + 10, sz.height() + 10);

    QImage img(imgSize, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    if (!img.isNull())
    {
        QPainter painter(&img);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.eraseRect(0, 0, imgSize.width(), imgSize.height());
        scene->renderToImage(&painter, QRect(5, 5, sz.width(), sz.height()), scene->itemsBoundingRect());
        return img.save(fileName);
    }

    return false;
}
