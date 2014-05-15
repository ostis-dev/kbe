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

#ifndef SCGCONTENTVIDEO_H
#define SCGCONTENTVIDEO_H

#include "scgcontentviewer.h"
#include "scgcontentdialog.h"
#include "scgcontentfactory.h"
#include <Phonon>

class SCgNode;
class QToolButton;
class QPushButton;

class SCgContentVideoViewer : public SCgContentViewer {
Q_OBJECT

public:
    explicit SCgContentVideoViewer(QGraphicsItem *parent = 0);
    virtual ~SCgContentVideoViewer();

    //! @see SCgContentViewer::hide()
    void hide();

protected:
    void setData(const QVariant &data);
    Phonon::AudioOutput *mAO;
    Phonon::MediaObject *mMO;
    Phonon::VideoWidget *mVideoWidget;
};

class SCgContentVideoDialog : public SCgContentDialog {
Q_OBJECT
public:
    explicit SCgContentVideoDialog(SCgNode *node, QWidget *parent = 0);
    virtual ~SCgContentVideoDialog(){}

protected:
    void apply();

    //! @see    SCgContentDialog::contentInfo()
    void contentInfo(SCgContent::ContInfo &info);

private:
    Phonon::MediaObject sourceVideo;
    QToolButton *mChooseButton;
    //! Path to video file
    QString mPath;

    void chooseVideo(const QString &title, Phonon::MediaObject *video, QToolButton *button);
    void loadVideo(const QString &fileName, Phonon::MediaObject *video, QToolButton *button);

private slots:
    void chooseSource();

};

class SCgContentVideoFactory : public SCgContentFactory {

public:
    SCgContentViewer* createViewerInstance();
    SCgContentDialog* createDialogInstance(SCgNode *node);

};

#endif // SCGCONTENTVIDEO_H
