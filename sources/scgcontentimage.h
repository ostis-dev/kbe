#ifndef SCGCONTENTIMAGE_H
#define SCGCONTENTIMAGE_H

#include "scgcontentdialog.h"
#include "scgcontentfactory.h"
#include "scgcontentviewer.h"


class SCgNode;
class QToolButton;
class QLabel;

class SCgContentImageViewer : public SCgContentViewer
{
Q_OBJECT

public:
    explicit SCgContentImageViewer(QGraphicsItem *parent = 0);
    virtual ~SCgContentImageViewer();

protected:

    void setData(const QVariant &data);

    //! Widget to show image
    QLabel *mImageLabel;

};

// ---------------------------------------------------
class SCgContentImageDialog : public SCgContentDialog

{
Q_OBJECT

public:
    explicit SCgContentImageDialog(SCgNode *node, QWidget *parent = 0);
    virtual ~SCgContentImageDialog(){}

private slots:
    void chooseSource();

protected:
    void apply();

    //! @see    SCgContentDialog::contentInfo()
    void contentInfo(SCgContent::ContInfo &info);


private:

    void chooseImage(const QString &title, QImage *image, QToolButton *button);
    void loadImage(const QString &fileName, QImage *image, QToolButton *button);
    QPoint imagePos(const QImage &image) const;

    QImage sourceImage;

    //! Choose image area
    QToolButton *mChooseButton;
};

// ---------------------------------------------------
class SCgContentImageFactory : public SCgContentFactory
{
public:
    virtual ~SCgContentImageFactory(){}

    SCgContentViewer* createViewerInstance();
    SCgContentDialog* createDialogInstance(SCgNode *node);
    QMap<QString, QString> supportedExtentions();
};

#endif // SCGCONTENTIMAGE_H
