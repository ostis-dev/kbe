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

#include "updatedownloader.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QTimer>
#include <QFile>
#include <QDebug>

UpdateDownloader::UpdateDownloader(QObject *parent) :
    QObject(parent),
    mNetworkManager(0),
    mNetworkReply(0)
{
    mNetworkManager = new QNetworkAccessManager(this);
}

UpdateDownloader::~UpdateDownloader()
{
    delete mNetworkManager;
}

void UpdateDownloader::doDownload(const QString &url, const QString &filePath)
{
    Q_ASSERT(mNetworkReply == 0);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Updater Tool", "Fetch updates");

    mNetworkReply = mNetworkManager->get(request);

    if (mNetworkReply == 0)
        return;

    mFile = new QFile(filePath);
    if(!mFile->open(QIODevice::WriteOnly))
    {
        delete mFile;
        mFile = 0;
        return;
    }

    connect(mNetworkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(mNetworkReply, SIGNAL(finished()), this, SLOT(downloadFinished()));

    emit started();
}

void UpdateDownloader::downloadReadyRead()
{
    Q_ASSERT(mFile != 0);
    mFile->write(mNetworkReply->readAll());
}

void UpdateDownloader::downloadFinished()
{
    downloadReadyRead();

    Q_ASSERT(mFile != 0);
    mFile->flush();
    mFile->close();

    bool _failed = false;

    if (mNetworkReply->error())
    {
        qDebug() << mNetworkReply->errorString();
        emit failed();
        _failed = true;
    }

    mNetworkReply->deleteLater();
    mNetworkReply = 0;

    // Need to call after network reply destroyed
    if (!_failed)
        emit finished();
}

void UpdateDownloader::downloadFailed()
{
    mNetworkReply->deleteLater();
    mNetworkReply = 0;

    emit failed();
}

void UpdateDownloader::downloadCanceled()
{
    mNetworkReply->abort();
    mNetworkReply = 0;
}
