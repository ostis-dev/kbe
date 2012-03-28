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

#include "feedbackwidget.h"
#include "smtp.h"

FeedbackWidget::FeedbackWidget()
{
    setWindowTitle("Letter to developers");
    QLabel *subjectLabel = new QLabel("Subject");
    QLabel *messageLabel = new QLabel("Message");
    QLabel *fromLabel = new QLabel("From");
    QLabel *passwordLabel = new QLabel("Password");
    subjectEdit = new QLineEdit();
    fromEdit = new QLineEdit();
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    messageEdit = new QTextEdit();
    QPushButton *sendButton = new QPushButton("Send");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *btLayout = new QHBoxLayout();
    btLayout->addWidget(sendButton);
    btLayout->addWidget(cancelButton);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(fromLabel);
    layout->addWidget(fromEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(subjectLabel);
    layout->addWidget(subjectEdit);
    layout->addWidget(messageLabel);
    layout->addWidget(messageEdit);
    QVBoxLayout *allLayout = new QVBoxLayout();
    allLayout->addLayout(layout);
    allLayout->addLayout(btLayout);
    setLayout(allLayout);

    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(sendButton,SIGNAL(clicked()),this,SLOT(sendMessage()));
}

void FeedbackWidget::sendMessage()
{
    if(subjectEdit->text().isEmpty() || fromEdit->text().isEmpty()
        || messageEdit->toPlainText().isEmpty() || passwordEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"ERROR","Not all fields are filled",QMessageBox::Ok);
        return;
    }
    QString host = fromEdit->text();
    host.replace(QRegExp(".*@"),"smtp.");
    smtp *mail = new smtp(host,25);
    mail->set_Login(fromEdit->text());
    mail->set_Password_for_login(passwordEdit->text());
    mail->set_Sender_mail(fromEdit->text());
    mail->set_Recipient_mail("kbe@ostis.net");
    mail->set_Subject(subjectEdit->text());
    mail->set_Body_text(messageEdit->toPlainText());
    mail->send_Mail();
    close();
    QMessageBox::information(this,"Thank you","Thank you! Your message is important to us.",QMessageBox::Ok);
}
