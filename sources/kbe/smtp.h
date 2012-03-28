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

class smtp : public QObject
{
    Q_OBJECT

public:
    smtp(QString host, quint16 port);
    ~smtp();

    void set_Login(QString login);
    void set_Password_for_login(QString password);
    void set_Sender_mail(QString email);
    void set_Recipient_mail(QString email);
    void set_Body_text(QString text);
    void set_Subject(QString subject);
    void send_Mail();

private:

    QString p_host;
    quint32 p_port;
    QString p_login;
    QString p_password;
    QString p_mail_From;
    QString p_mail_to;
    QString p_body;
    QString p_subject;

    QString message;

    int state;
    QString response;

    QTcpSocket *tcp;
    QTextStream *t;
    QString encodeBase64( QString xml );
    QString decodeBase64( QString xml );



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
    void on_connected();
    void on_read();

signals:
    void error_code(QString error_text);
    void status( const QString & );
};

#endif // SMTP_H
