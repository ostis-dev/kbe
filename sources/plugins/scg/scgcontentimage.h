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
    QMap<QString, MimeAndSCgTypes> supportedExtentions();
};

#endif // SCGCONTENTIMAGE_H
