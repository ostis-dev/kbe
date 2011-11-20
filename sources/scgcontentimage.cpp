#include "scgcontentimage.h"

#include "scgnode.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <config.h>

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
    else loadImage(Config::pathIcons.path()+"/document-open.png", &sourceImage, mChooseButton);

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
    QString filters("Windows Bitmap(*.bmp)\n"
                    "Graphic Interchange Format(*.gif)\n"
                    "Joint Photographic Experts Group(*.jpg; *.jpeg)\n"
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
    QString fileName = QFileDialog::getOpenFileName(this, title, "", filters);
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
