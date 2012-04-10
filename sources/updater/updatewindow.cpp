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

#include "updatewindow.h"
#include "updatedownloader.h"

#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressDialog>
#include <QMessageBox>
#include <QTimer>

UpdateWindow::UpdateWindow(const QString &version, QWidget *parent) :
    QWidget(parent),
    mDescriptionBrowser(0),
    mProgressDialog(0),
    mUpdateButton(0),
    mInstallButton(0),
    mCancelButton(0),
    mCurrentVersion(version),
    mCurrentWork(WT_UPDATELIST),
    mUpdateDownloader(0)
{

    QVBoxLayout *layout = new QVBoxLayout(this);

    mDescriptionBrowser = new QTextBrowser(this);

    layout->addWidget(mDescriptionBrowser);

    QHBoxLayout *hlayout = new QHBoxLayout(this);

    mUpdateButton = new QPushButton(tr("Update"), this);
    mInstallButton = new QPushButton(tr("Install"), this);
    mCancelButton = new QPushButton(tr("Cancel"), this);
    mCancelButton->setEnabled(false);
    mInstallButton->setEnabled(false);

    hlayout->addWidget(mUpdateButton);
    hlayout->addWidget(mInstallButton);
    hlayout->addWidget(mCancelButton);

    connect(mUpdateButton, SIGNAL(clicked()), this, SLOT(startUpdate()));

    layout->addLayout(hlayout);

    setLayout(layout);

    mProgressDialog = new QProgressDialog(this);

    connect(mProgressDialog, SIGNAL(canceled()), this, SLOT(workCanceled()));
}

UpdateWindow::~UpdateWindow()
{
    delete mProgressDialog;
}

void UpdateWindow::workProgress(qint64 finished, qint64 total)
{
    mProgressDialog->setValue(finished);
    mProgressDialog->setMaximum(total);
}

void UpdateWindow::workFinished()
{
    mProgressDialog->hide();

    if (mCurrentWork == WT_UPDATELIST)
        mUpdateButton->setEnabled(true);
}

void UpdateWindow::workStarted()
{
    mProgressDialog->exec();
}

void UpdateWindow::workFailed()
{
    if (mCurrentWork == WT_UPDATELIST)
    {
        QMessageBox::information(this, "Error", tr("Unable to download updates list"));
        mUpdateButton->setEnabled(true);
    }

    mProgressDialog->hide();
}

void UpdateWindow::workCanceled()
{
    if (mCurrentWork == WT_UPDATELIST)
    {
        mUpdateDownloader->downloadCanceled();
        mUpdateButton->setEnabled(true);
    }
}

void UpdateWindow::startUpdate()
{
    // try to download new update
    mUpdateDownloader = new UpdateDownloader(this);
    connect(mUpdateDownloader, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(workProgress(qint64, qint64)));
    connect(mUpdateDownloader, SIGNAL(started()), this, SLOT(workStarted()));
    connect(mUpdateDownloader, SIGNAL(failed()), this, SLOT(workFailed()));
    connect(mUpdateDownloader, SIGNAL(finished()), this, SLOT(workFinished()));

    mUpdateButton->setEnabled(false);

    mProgressDialog->setLabelText(tr("Download updates list"));
    QTimer::singleShot(0, mUpdateDownloader, SLOT(downloadUpdatesList()));
    //mUpdateDownloader->downloadUpdatesList();
}
