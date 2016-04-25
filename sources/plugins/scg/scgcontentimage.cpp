/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontentimage.h"

#include "scgnode.h"
#include "scgplugin.h"
#include "scgwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include "config.h"

static const QSize resultSize(200, 200);
QString mPath;

SCgContentImageViewer::SCgContentImageViewer(QGraphicsItem *parent) :
        SCgContentViewer(parent),
        mImageLabel(0)
{
    setMinimumSize(10, 10);
}

SCgContentImageViewer::~SCgContentImageViewer()
{

}

void SCgContentImageViewer::setData(const QVariant &data)
{
    SCgContentViewer::setData(data);

    if (!mImageLabel)
    {
        mImageLabel = new QLabel();
    }

    QImage tempImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    if (tempImage.loadFromData(data.toByteArray()))
    {
        mImageLabel->setPixmap(QPixmap::fromImage(tempImage));
        mImageLabel->setMinimumSize(tempImage.width(), tempImage.height());
        mImageLabel->setFixedSize(tempImage.width(), tempImage.height());
        mImageLabel->updateGeometry();
    }
    setWidget(mImageLabel);
}

SCgContentImageDialog::SCgContentImageDialog(SCgNode *node, QWidget *parent) :
        SCgContentDialog(node, parent),
        mChooseButton(0)
{    

    mChooseButton = new QToolButton();
    mChooseButton->setIconSize(resultSize);
    if (mNode->isContentData() && mNode->contentFormat() == "image")
    {
        QImage tempImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        tempImage.loadFromData(mNode->contentData().toByteArray());
        mChooseButton->setIcon(QPixmap::fromImage(tempImage));
    }
    else loadImage("", &sourceImage, mChooseButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mChooseButton);
    setLayout(mainLayout);

    sourceImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    connect(mChooseButton, SIGNAL(clicked()), this, SLOT(chooseSource()));

}

void SCgContentImageDialog::chooseSource()
{
    chooseImage(tr("Choose Source Image"), &sourceImage, mChooseButton);
}

void SCgContentImageDialog::chooseImage(const QString &title, QImage *image,
                                        QToolButton *button)
{
    QString filters("All suported (*.bmp *gif *.jpg *.jpeg *.mng *.png *.pbm"
                    "*.pgm *.ppm *.tiff *.xbm *.xpm *.svg)\n"
                    "Windows Bitmap(*.bmp)\n"
                    "Graphic Interchange Format(*.gif)\n"
                    "Joint Photographic Experts Group(*.jpg *.jpeg)\n"
                    "Multiple-image Network Graphics(*.mng)\n"
                    "Portable Network Graphics(*.png)\n"
                    "Portable Bitmap(*.pbm)\n"
                    "Portable Graymap(*.pgm)\n"
                    "Portable Pixmap(*.ppm)\n"
                    "Tagged Image File Format(*.tiff)\n"
                    "X11 Bitmap(*.xbm)\n"
                    "X11 Pixmap(*.xpm)\n"
                    "Scalable Vector Graphics(*.svg)\n"
                    "All Files(*.*)");
    QString fileName = QFileDialog::getOpenFileName(this, title, "",
                                                    filters, new QString(),
                                                    QFileDialog::DontUseNativeDialog);
    if (!fileName.isEmpty()){
        loadImage(fileName, image, button);        
        mPath = fileName;
    }
}

void SCgContentImageDialog::loadImage(const QString &fileName, QImage *image,
                                      QToolButton *button)
{
    image->load(fileName);
    button->setIcon(QPixmap::fromImage(*image));
}


void SCgContentImageDialog::apply()
{
}

void SCgContentImageDialog::contentInfo(SCgContent::ContInfo &info)
{
    if (mPath.size() > 0)
    {
        QFile f(mPath);
        f.open(QFile::ReadOnly);
        info.data = QVariant(f.readAll());
        f.close();

        info.mimeType = "image/" + mPath.mid(mPath.lastIndexOf('.')+1);
        info.fileName = mPath;
        info.type = SCgContent::Data;

    }
    else info.setEmpty();
}

SCgContentViewer* SCgContentImageFactory::createViewerInstance()
{
    return new SCgContentImageViewer();
}

SCgContentDialog* SCgContentImageFactory::createDialogInstance(SCgNode *node)
{
    return new SCgContentImageDialog(node);
}

QMap<QString, SCgContentFactory::MimeAndSCgTypes> SCgContentImageFactory::supportedExtentions() {
    QMap<QString, MimeAndSCgTypes> ext;

    ext["ico"] = qMakePair(QString("image/x-icon"), SCgContent::Data);
    ext["png"] = qMakePair(QString("image/png"), SCgContent::Data);
    ext["bmp"] = qMakePair(QString("image/bmp"), SCgContent::Data);
    ext["gif"] = qMakePair(QString("image/gif"), SCgContent::Data);
    ext["jpeg"] = qMakePair(QString("image/jpeg"), SCgContent::Data);
    ext["jpg"] = qMakePair(QString("image/jpeg"), SCgContent::Data);
    ext["jpe"] = qMakePair(QString("image/jpeg"), SCgContent::Data);
    ext["svg"] = qMakePair(QString("image/svg+xml"), SCgContent::Data);
    ext["tiff"] = qMakePair(QString("image/tiff"), SCgContent::Data);
    ext["tif"] = qMakePair(QString("image/tiff"), SCgContent::Data);
    ext["mng"] = qMakePair(QString("image/x-jng"), SCgContent::Data);
    ext["pbm"] = qMakePair(QString("image/pbm"), SCgContent::Data);
    ext["pgm"] = qMakePair(QString("image/x-pgm"), SCgContent::Data);
    ext["ppm"] = qMakePair(QString("image/x-ppm"), SCgContent::Data);
    ext["xbm"] = qMakePair(QString("image/x-xbm"), SCgContent::Data);
    ext["xpm"] = qMakePair(QString("image/x-xpixmap"), SCgContent::Data);
    return ext;
}
