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

#ifndef UPDATEDOWNLOADER_H
#define UPDATEDOWNLOADER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

/*! Class that download update package and check it.
  */
class UpdateDownloader : public QObject
{
    Q_OBJECT
public:
    explicit UpdateDownloader(QObject *parent = 0);
    virtual ~UpdateDownloader();

    /*! Download file from specified \p url
      * @param url Url to download file
      * @param filePath Path to save downloaded file
      */
    void doDownload(const QString &url, const QString &filePath);

private:
    //! Pointer to network manager
    QNetworkAccessManager *mNetworkManager;
    //! Pointer to used for download network reply
    QNetworkReply *mNetworkReply;
    //! Pointer to output file for download
    QFile *mFile;

signals:
    //! Signal that emits on download start
    void started();
    //! Signal on download finished
    void finished();
    //! Signal on download failed
    void failed();
    //! Signal that emits current donwload progress
    void downloadProgress(qint64 bytesRecieved, qint64 bytesTotal);

public slots:

    void downloadReadyRead();
    void downloadFinished();
    void downloadFailed();
    void downloadCanceled();

};

#endif // UPDATEDOWNLOADER_H
