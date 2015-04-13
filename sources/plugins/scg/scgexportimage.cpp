/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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
