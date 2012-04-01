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

#ifndef SMTP_H
#define SMTP_H

#include <QTcpSocket>
#include <QTextStream>

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp(QString host, quint16 port);
    ~Smtp();

    void setLogin(QString login);
    void setPassword(QString password);
    void setSender(QString email);
    void setRecipient(QString email);
    void setBody(QString text);
    void setSubject(QString subject);
    void sendMail();

private:

    QString mStringHost;
    quint32 mPort;
    QString mStringLogin;
    QString mStringPassword;
    QString mStringSender;
    QString mStringRecipient;
    QString mStringBody;
    QString mStringSubject;

    QString mStringMessage;

    int state;
    QString mStringResponse;

    QTcpSocket *tcp;
    QTextStream *t;
    QString encodeBase64( QString xml );



    enum State {
            Init,
            Start,
            Login,
            Pass,
            Mail,
            Rcpt,
            Data,
            Body,
            Quit,
            Close
        };


private slots:
    void onConnected();
    void onRead();

signals:
    void errorCode(QString errorText);
    void status( const QString & );
};

#endif // SMTP_H
