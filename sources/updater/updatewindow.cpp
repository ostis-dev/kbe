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

#include "updatewindow.h"
#include "updatedownloader.h"
#include "updateextractor.h"
#include "updateinstaller.h"

#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include <QDomDocument>
#include <QFile>
#include <QLabel>
#include <QCryptographicHash>
#include <QTextStream>

#define UPDATE_LIST "http://www.ostis.net/download/updates/updates.xml"
#define UPDATE_FILE_PATH "_update.update"
#define UPDATE_CHECKSUM_PATH "_update.checksum"

UpdateWindow::UpdateWindow(const QString &version, QWidget *parent) :
    QWidget(parent),
    mProgressBar(0),
    mLabel(0),
    mProgressLabel(0),
    mCancelButton(0),
    mCurrentVersion(version),
    mCurrentWork(WT_UPDATELIST),
    mUpdateDownloader(0)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();

    mLabel = new QLabel(tr("Stage"), this);

    mProgressLabel = new QLabel(this);

    mProgressBar = new QProgressBar(this);

    mCancelButton = new QPushButton(tr("Cancel"), this);
    mCancelButton->setEnabled(false);

    hlayout->addWidget(mProgressBar);
    hlayout->addWidget(mCancelButton);

    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(workCanceled()));

    vlayout->addWidget(mLabel);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(mProgressLabel);

    setLayout(vlayout);

    startUpdate();
}

UpdateWindow::~UpdateWindow()
{
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

    mLabel->setText(tr("Download updates list"));
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

    mLabel->setText(tr("Download update..."));
    mUpdateDownloader->doDownload(mUpdatePath, UPDATE_FILE_PATH);
}

void UpdateWindow::downloadCheckSum()
{
    mCurrentWork = WT_GETCHECKSUM;

    mLabel->setText(tr("Download checksum..."));
    mUpdateDownloader->doDownload(mUpdatePath + ".checksum", UPDATE_CHECKSUM_PATH);
}

bool UpdateWindow::compareChecksums()
{
    QFile updateFile(UPDATE_FILE_PATH);
    if (!updateFile.open(QIODevice::ReadOnly))
        return false;
    QByteArray fileData = updateFile.readAll();
    QByteArray hashData = QCryptographicHash::hash(fileData,QCryptographicHash::Md5);
    QString updateFileHash = QString(hashData.toHex());
    QFile checksumFile(UPDATE_CHECKSUM_PATH);
    if (!checksumFile.open(QIODevice::ReadOnly))
        return false;
    QTextStream textStream(&checksumFile);
    QStringList list;
    while (true) {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            list.append(line);
    }
    QString originalHash = list.at(1);
    originalHash = originalHash.replace("md5: ","");
    if (originalHash != updateFileHash)
        return false;
    return true;
}

void UpdateWindow::readUpdate()
{
    mCurrentWork = WT_COMPARECHECKSUM;

    workStarted();

    if(!compareChecksums())
        workFailed();

    mCurrentWork = WT_READCONTENT;
    mLabel->setText(tr("Reading update..."));
    mProgressLabel->setText(QString());

    // unpack
    UpdateExtractor extractor;
    if (!extractor.extract(UPDATE_FILE_PATH, "_update_files"))
        workFailed();

    workFinished();
}

void UpdateWindow::installUpdate()
{
    mCurrentWork = WT_INSTALL;

    workStarted();

    mLabel->setText(tr("Install update"));

    // install
    UpdateInstaller installer("_update_files");
    if(!installer.installUpdate())
        workFailed();
    else workFinished();
}

void UpdateWindow::workProgress(qint64 finished, qint64 total)
{
    mProgressBar->setRange(0, total);
    mProgressBar->setValue(finished);
    mProgressLabel->setText(QString::number(finished/1024)+" kb / "+QString::number(total/1024) + " kb");
}

void UpdateWindow::workFinished()
{
    mCancelButton->setEnabled(false);

    switch (mCurrentWork)
    {
    case WT_UPDATELIST:
        resolveUpdate();
        break;

    case WT_GETUPDATE:
        downloadCheckSum();
        break;

    case WT_GETCHECKSUM:
        readUpdate();
        break;

    case WT_READCONTENT:
        installUpdate();
        break;

    case WT_INSTALL:
        QMessageBox::information(this, tr("Success!"), tr("Update completed."));
        close();
        break;
    default:
        break;
    }

}

void UpdateWindow::workStarted()
{
    mCancelButton->setEnabled(true);
}

void UpdateWindow::workFailed()
{
    switch(mCurrentWork) {
    case WT_UPDATELIST:
        QMessageBox::information(this, tr("Error"), tr("Unable to download updates list"));
        break;
    case WT_COMPARECHECKSUM:
        QMessageBox::information(this, tr("Error"), tr("Checksums don't match"));
        break;
    case WT_READCONTENT:
        QMessageBox::information(this, tr("Error"), tr("Archive isn't extracted"));
        break;
    case WT_INSTALL:
        QMessageBox::information(this, tr("Error"), tr("Update isn't installed"));
        break;
    }
    mProgressLabel->clear();
    close();
}

void UpdateWindow::workCanceled()
{
    switch(mCurrentWork)
    {
    case WT_UPDATELIST:
    case WT_GETUPDATE:
        mUpdateDownloader->downloadCanceled();
        break;
    default:
        break;
    }
    close();
}

