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

#include "feedbackdialog.h"
#include "smtp.h"

FeedBackDialog::FeedBackDialog():
        mLineEditSubject(0),
        mLineEditSender(0),
        mLineEditPassword(0),
        mTextEditMessage(0)
{
    setWindowTitle("Feedback");
    QLabel *mLabelSubject = new QLabel("Subject");
    QLabel *mLabelMessage = new QLabel("Message");
    QLabel *mLabelSender = new QLabel("From");
    QLabel *mLabelPassword = new QLabel("Password");
    mLineEditSubject = new QLineEdit();
    mLineEditSender = new QLineEdit();
    mLineEditPassword = new QLineEdit();
    mLineEditPassword->setEchoMode(QLineEdit::Password);
    mTextEditMessage = new QTextEdit();
    QPushButton *mButtonSend = new QPushButton("Send");
    QPushButton *mButtonCancel = new QPushButton("Cancel");
    QHBoxLayout *btHLayout = new QHBoxLayout();
    btHLayout->addWidget(mButtonSend);
    btHLayout->addWidget(mButtonCancel);
    QVBoxLayout *mVLayout = new QVBoxLayout();
    mVLayout->addWidget(mLabelSender);
    mVLayout->addWidget(mLineEditSender);
    mVLayout->addWidget(mLabelPassword);
    mVLayout->addWidget(mLineEditPassword);
    mVLayout->addWidget(mLabelSubject);
    mVLayout->addWidget(mLineEditSubject);
    mVLayout->addWidget(mLabelMessage);
    mVLayout->addWidget(mTextEditMessage);
    QVBoxLayout *mLayoutAll = new QVBoxLayout();
    mLayoutAll->addLayout(mVLayout);
    mLayoutAll->addLayout(btHLayout);
    setLayout(mLayoutAll);

    connect(mButtonCancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(mButtonSend,SIGNAL(clicked()),this,SLOT(clickButtonOk()));

}

void FeedBackDialog::clickButtonOk()
{
    if(mLineEditSubject->text().isEmpty() || mLineEditSender->text().isEmpty()
        || mTextEditMessage->toPlainText().isEmpty() || mLineEditPassword->text().isEmpty())
    {
        QMessageBox::critical(this,"ERROR","Not all fields are filled",QMessageBox::Ok);
        return;
    }
    QString host = mLineEditSender->text();
    host.replace(QRegExp(".*@"),"smtp.");
    Smtp *mail = new Smtp(host,25);
    mail->setLogin(mLineEditSender->text());
    mail->setPassword(mLineEditPassword->text());
    mail->setSender(mLineEditSender->text());
    mail->setRecipient("kbe@ostis.net");
    mail->setSubject(mLineEditSubject->text());
    mail->setBody(mTextEditMessage->toPlainText());
    mail->sendMail();
    close();
    QMessageBox::information(this,"Thank you","Thank you! Your message is important to us.",QMessageBox::Ok);
}
