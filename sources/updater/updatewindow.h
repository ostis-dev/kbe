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

#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <QWidget>

class QTextBrowser;
class QProgressBar;
class QPushButton;
class QLabel;

class UpdateDownloader;

class UpdateWindow : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateWindow(const QString &version, QWidget *parent = 0);
    virtual ~UpdateWindow();
    
    typedef enum
    {
        WT_UPDATELIST = 0,
        WT_GETUPDATE,
        WT_GETCHECKSUM,
        WT_READCONTENT,
        WT_INSTALL
    } WorkType;

protected:
    /*! Parse updates list and trying to resolve if there are any suitable update
      * for current version. If it exists, then start download.
      */
    void resolveUpdate();

    //! Start update downloading.
    void downloadUpdate();

    //! Download checksum for update
    void downloadCheckSum();

    //! Reads downloaded update and show information about it
    void readUpdate();

private:
    //! Pointer to progress bar that shows update progress
    QProgressBar *mProgressBar;
    //! Pointer to label that shows current update stage
    QLabel *mLabel;
    //! Pointer to cancel button
    QPushButton *mCancelButton;
    //! Current version
    QString mCurrentVersion;
    //! Path to founded on server update file
    QString mUpdatePath;

    //! Current work
    WorkType mCurrentWork;

    UpdateDownloader *mUpdateDownloader;

signals:
    
public slots:
    //! Slot that recieves current work progress
    void workProgress(qint64 finished, qint64 total);
    //! Slot that calls on current work finished
    void workFinished();
    //! Slot that calls on any work started
    void workStarted();
    //! Slot that calls on any work failed
    void workFailed();
    //! Slot that calls on cancel button click in progress dialog
    void workCanceled();

private slots:

    void startUpdate();
};

#endif // UPDATEWINDOW_H
