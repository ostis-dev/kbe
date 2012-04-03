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

#include <Smtp.h>
#include <QMessageBox>

Smtp::Smtp(QString host, quint16 port)
{

    mStringHost = host;
    mPort = port;
    tcp = new QTcpSocket();
    t = new QTextStream(tcp);

    connect(tcp, SIGNAL(connected()),this, SLOT(onConnected()));
    connect(tcp, SIGNAL(readyRead()), this, SLOT(onRead()));

}

Smtp::~Smtp()
{
    delete tcp;
    delete t;
}


void Smtp::sendMail()
{
    tcp->abort();
    tcp->connectToHost(mStringHost, mPort);
    state = Init;
}

void Smtp::onConnected()
{
    emit status("Connected to Smtp server");
}

void Smtp::onRead()
{
    if( !tcp->canReadLine() )
        return;

    QString mStringResponseLine;

    do {
            mStringResponseLine = tcp->readLine();
            mStringResponse += mStringResponseLine;
        } while( tcp->canReadLine() && mStringResponseLine[3] != ' ' );
    qDebug() << mStringResponseLine;
    mStringResponseLine.truncate( 3 );

    if ( state == Init && mStringResponseLine[0] == '2' )
        {

            *t << "HELO there\r\n";
            t->flush();
            state = Start;
        }
    else if (state == Start && mStringResponseLine[0] == '2')
        {
            *t << "AUTH LOGIN\r\n";
            t->flush();
            state = Login;
        }
    else if (state == Login && mStringResponseLine[0] == '3')
        {
            *t << encodeBase64(mStringLogin) << "\r\n";
            t->flush();
            state = Pass;
        }
    else if (state == Pass && mStringResponseLine[0] == '3')
        {
            *t << encodeBase64(mStringPassword) << "\r\n";
            t->flush();
            state = Mail;
        }
    else if ( state == Mail && mStringResponseLine[0] == '2' )
        {

            *t << "MAIL FROM: <" << mStringSender << ">\r\n";
            t->flush();
            state = Rcpt;
        }
    else if ( state == Rcpt && mStringResponseLine[0] == '2' )
        {

            *t << "RCPT TO: <" << mStringRecipient << ">\r\n";
            t->flush();
            state = Data;
        }
    else if ( state == Data && mStringResponseLine[0] == '2' )
        {
            *t << "DATA\r\n";
            t->flush();
            state = Body;
        }
    else if ( state == Body && mStringResponseLine[0] == '3' )
        {
            QString message = QString( "From: %1\nTo: %2\nSubject: %3\n\n%4\n" ).arg(mStringSender).arg(mStringRecipient).arg(mStringSubject).arg(mStringBody);
            message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1("\r\n" ) );
            message.replace( QString::fromLatin1( "\r\n.\r\n" ), QString::fromLatin1( "\r\n..\r\n" ) );

            *t << message << "\n" << ".\r\n";
            t->flush();
            state = Quit;
        }
    else if ( state == Quit && mStringResponseLine[0] == '2' )
        {
            *t << "QUIT\r\n";
            state = Close;
            emit status( tr( "Message sent" ) );
        }
    else if ( state == Close )
        {

        }
    else
        {
            emit status(tr("Unknown answer from Smtp server"));
            state = Close;
        }
    mStringResponse = "";
}

void Smtp::setLogin(QString login)
{
    mStringLogin = login;
}

void Smtp::setPassword(QString password)
{
    mStringPassword = password;
}

void Smtp::setSender(QString email)
{
    mStringSender = email;
}

void Smtp::setRecipient(QString email)
{
    mStringRecipient = email;
}

void Smtp::setBody(QString text)
{
    mStringBody = text;
}

void Smtp::setSubject(QString subject)
{
    mStringSubject = subject;
}

QString Smtp::encodeBase64( QString xml )
{
    QByteArray text;
    text.append(xml);
    return text.toBase64();
}
