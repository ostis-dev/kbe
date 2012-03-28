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

#include <smtp.h>
#include <QMessageBox>

smtp::smtp(QString host, quint16 port)
{

    p_host = host;
    p_port = port;
    tcp = new QTcpSocket();
    t = new QTextStream(tcp);


    connect(tcp, SIGNAL(connected()),this, SLOT(on_connected()));
    connect(tcp, SIGNAL(readyRead()), this, SLOT(on_read()));
    connect(this, SIGNAL(status(QString)), this, SLOT(message_sended(QString)));
}

smtp::~smtp()
{
    delete tcp;
    delete t;
}


void smtp::send_Mail()
{
    tcp->abort();
    tcp->connectToHost(p_host, p_port);
    state = Init;
}

void smtp::on_connected()
{
    emit status("Connected to SMTP server");
}

void smtp::on_read()
{
    if( !tcp->canReadLine() )
        return;

    QString responseLine;

    do {
            responseLine = tcp->readLine();
            response += responseLine;
        } while( tcp->canReadLine() && responseLine[3] != ' ' );
    qDebug() << responseLine;
    responseLine.truncate( 3 );

    if ( state == Init && responseLine[0] == '2' )
        {

            *t << "HELO there\r\n";
            t->flush();
            state = Start;
        }
    else if (state == Start && responseLine[0] == '2')
        {
            *t << "AUTH LOGIN\r\n";
            t->flush();
            state = Login;
        }
    else if (state == Login && responseLine[0] == '3')
        {
            *t << encodeBase64(p_login) << "\r\n";
            t->flush();
            state = Pass;
        }
    else if (state == Pass && responseLine[0] == '3')
        {
            *t << encodeBase64(p_password) << "\r\n";
            t->flush();
            state = Mail;
        }
    else if ( state == Mail && responseLine[0] == '2' )
        {

            *t << "MAIL FROM: <" << p_mail_From << ">\r\n";
            t->flush();
            state = Rcpt;
        }
    else if ( state == Rcpt && responseLine[0] == '2' )
        {

            *t << "RCPT TO: <" << p_mail_to << ">\r\n";
            t->flush();
            state = Data;
        }
    else if ( state == Data && responseLine[0] == '2' )
        {
            *t << "DATA\r\n";
            t->flush();
            state = Body;
        }
    else if ( state == Body && responseLine[0] == '3' )
        {
            QString body;
            body = p_body;
            QString subject;
            subject = p_subject;
            message = QString( "From: %1\nTo: %2\nSubject: %3\n\n%4\n" ).arg(p_mail_From).arg(p_mail_to).arg(subject).arg(body);
            message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1("\r\n" ) );
            message.replace( QString::fromLatin1( "\r\n.\r\n" ), QString::fromLatin1( "\r\n..\r\n" ) );

            *t << message << "\n" << ".\r\n";
            t->flush();
            state = Quit;
        }
    else if ( state == Quit && responseLine[0] == '2' )
        {
            *t << "QUIT\r\n";
            state = Close;
            //t->flush();
            emit status( tr( "Message sent" ) );
        }
    else if ( state == Close )
        {

        }
    else
        {
            emit status(tr("Unknown answer from SMTP server"));
            state = Close;
        }
    response = "";
}

void smtp::set_Login(QString login)
{
    p_login = login;
}

void smtp::set_Password_for_login(QString password)
{
    p_password = password;
}

void smtp::set_Sender_mail(QString email)
{
    p_mail_From = email;
}

void smtp::set_Recipient_mail(QString email)
{
    p_mail_to = email;
}

void smtp::set_Body_text(QString text)
{
    p_body = text;
}

void smtp::set_Subject(QString subject)
{
    p_subject = subject;
}

QString smtp::encodeBase64( QString xml )
{
    QByteArray text;
    text.append(xml);
    return text.toBase64();
}

QString smtp::decodeBase64( QString xml )
{
    QByteArray xcode("");;
    xcode.append(xml);
    QByteArray precode(QByteArray::fromBase64(xcode));
    QString notetxt = precode.data();
    return notetxt;
}
