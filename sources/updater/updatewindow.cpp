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
#include <QDomDocument>
#include <QFile>

#define UPDATE_LIST "http://www.ostis.net/download/updates/updates.xml"
#define UPDATE_FILE_PATH "_update.update"
#define UPDATE_CHECKSUM_PATH "_update.checksum"

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
    delete mUpdateDownloader;
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
    mUpdateDownloader->doDownload(UPDATE_LIST, "_updates.xml");
}

void UpdateWindow::resolveUpdate()
{
    static QString updatesFile = "_updates.xml";
    QDomDocument doc(updatesFile);

    QFile file(updatesFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Can't open file %1").arg(updatesFile));
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        QMessageBox::critical(this, tr("Error"), tr("Can't parse file %1").arg(updatesFile));
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();

    if (root.tagName() != "updates")
    {
        QMessageBox::critical(this, tr("Error"), tr("File %1 is invalid").arg(updatesFile));
        return;
    }

    // iterate all available updates and find for current version
    QDomElement update = root.firstChildElement("update");
    while (!update.isNull())
    {
        if (update.attribute("from") == mCurrentVersion)
        {
            mUpdatePath = update.firstChild().nodeValue();
            break;
        }

        update = update.nextSiblingElement("update");
    }

    // start downloading of update
    if (mUpdatePath.isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("There are no suitable update for version %1").arg(mCurrentVersion));
        return;
    }

    downloadUpdate();
}

void UpdateWindow::downloadUpdate()
{
    mCurrentWork = WT_GETUPDATE;

    mProgressDialog->setLabelText(tr("Download update..."));
    mUpdateDownloader->doDownload(mUpdatePath, UPDATE_FILE_PATH);
}

void UpdateWindow::downloadCheckSum()
{
    mCurrentWork = WT_GETCHECKSUM;

    mProgressDialog->setLabelText(tr("Download checksum..."));
    mUpdateDownloader->doDownload(mUpdatePath + ".checksum", UPDATE_CHECKSUM_PATH);
}

void UpdateWindow::readUpdate()
{
    // TODO: compare checksum


}

void UpdateWindow::workProgress(qint64 finished, qint64 total)
{
    mProgressDialog->setValue(finished);
    mProgressDialog->setMaximum(total);
}

void UpdateWindow::workFinished()
{
    mProgressDialog->setValue(0);
    mProgressDialog->hide();

    switch (mCurrentWork)
    {
    case WT_UPDATELIST:
        mUpdateButton->setEnabled(true);
        resolveUpdate();
        break;

    case WT_GETUPDATE:
        mUpdateButton->setEnabled(false);
        downloadCheckSum();
        break;

    case WT_GETCHECKSUM:
        readUpdate();
        break;
    }

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

    mProgressDialog->setValue(0);
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

