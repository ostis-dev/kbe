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
class QProgressDialog;
class QPushButton;

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
        WT_INSTALL
    } WorkType;

private:
    //! Pointer to text browser, that shows description
    QTextBrowser *mDescriptionBrowser;
    //! Pointer to work progress dialog
    QProgressDialog *mProgressDialog;
    //! Pointer to update button
    QPushButton *mUpdateButton;
    //! Pointer to start button
    QPushButton *mInstallButton;
    //! Pointer to cancel button
    QPushButton *mCancelButton;
    //! Current version
    QString mCurrentVersion;

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
