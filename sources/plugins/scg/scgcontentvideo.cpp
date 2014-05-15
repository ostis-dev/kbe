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
#include "scgcontentvideo.h"
#include "scgnode.h"

#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <phonon>

static const QSize rezultSize (200,200);

SCgContentVideoViewer::SCgContentVideoViewer(QGraphicsItem *parent) :
        SCgContentViewer(parent),
        mAO(0),
        mMO(0),
        mVideoWidget(0)
{
    setMinimumSize(10,10);
}

SCgContentVideoViewer::~SCgContentVideoViewer() {
    if (mAO) delete mAO;
    if (mMO) delete mMO;
    if (mVideoWidget) delete mVideoWidget;
}

void SCgContentVideoViewer::setData(const QVariant &data)
{
    SCgContentViewer::setData(data);

    QWidget* main = new QWidget();

    if (!mMO) mMO = new Phonon::MediaObject(main);
    if (!mAO) mAO = new Phonon::AudioOutput(Phonon::VideoCategory, main);

    if (!mVideoWidget) mVideoWidget = new Phonon::VideoWidget(main);

    Phonon::createPath(mMO, mAO);
    Phonon::createPath(mMO, mVideoWidget);

    QPushButton *butPlay = new QPushButton("&Play");
    QPushButton *butPause = new QPushButton("&Pause");
    Phonon::SeekSlider *slider = new Phonon::SeekSlider(main);

    slider->setMediaObject(mMO);

    connect(butPlay, SIGNAL(clicked()), mMO, SLOT(play()));
    connect(butPause, SIGNAL(clicked()), mMO, SLOT(pause()));
    QString st = data.toString();
    mMO->setCurrentSource(Phonon::MediaSource(st));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(butPlay);
    hLayout->addWidget(butPause);
    hLayout->addWidget(slider);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(mVideoWidget);
    vLayout->addLayout(hLayout);

    main->setLayout(vLayout);
    setWidget(main);

    mMO->stop();
}

void SCgContentVideoViewer::hide()
{
    QGraphicsProxyWidget::hide();
    mMO->stop();
}

//-----------------------------------------------------------------------------
SCgContentVideoDialog::SCgContentVideoDialog (SCgNode *node, QWidget *parent) :
        SCgContentDialog(node, parent),
        mChooseButton(0)
{
    mChooseButton = new QToolButton(this);
    mChooseButton->setIconSize(rezultSize);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mChooseButton);
    setLayout(mainLayout);

    QImage icon;
    icon.load("../media/icons/document-open.png");
    mChooseButton->setIcon(QPixmap::fromImage(icon));
    connect(mChooseButton, SIGNAL(clicked()), this, SLOT(chooseSource()));

}

void SCgContentVideoDialog::chooseSource() {
    chooseVideo(tr("Choose Source Video"), &sourceVideo, mChooseButton);
}

void SCgContentVideoDialog::chooseVideo(const QString &title, Phonon::MediaObject *video,
                                        QToolButton *button) {
    QString filters("Audio Video Interleave(*.avi)\n"
                    "DivX(*.divx)\n"
                    "Matroska Video(*.mkv)\n"
                    "Quick Time Movie(*.mov)\n"
                    "MPEG(*.mp2; *.mp4; *.mpg; *.mpeg; *.mpeg4)\n"
                    "Windows Media Video(*.wmv)\n"
                    "All Files(*.*)");
    QString fileName = QFileDialog::getOpenFileName(this, title, "", filters);
    if (!fileName.isEmpty()) {
        loadVideo(fileName, video, button);
        mPath = fileName;
    }
}

void SCgContentVideoDialog::loadVideo(const QString &fileName, Phonon::MediaObject *video,
                                      QToolButton *button) {
    video->setCurrentSource(Phonon::MediaSource(fileName));

}

void SCgContentVideoDialog::apply()
{
}

void SCgContentVideoDialog::contentInfo(SCgContent::ContInfo &info)
{
    if (mPath.size() > 0) {
        info.data = QVariant(mPath);
        info.mimeType = "video/" + mPath.mid(mPath.lastIndexOf('.')+1);;
        info.fileName = mPath;
        info.type = SCgContent::Data;
    }
    else info.setEmpty();
}
//-----------------------------------------------------------------
SCgContentViewer* SCgContentVideoFactory::createViewerInstance() {
    return new SCgContentVideoViewer();
}

SCgContentDialog* SCgContentVideoFactory::createDialogInstance(SCgNode *node) {
    return new SCgContentVideoDialog(node);
}
