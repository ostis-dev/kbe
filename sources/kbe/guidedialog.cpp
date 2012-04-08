#include "guidedialog.h"
#include <QtGui>
#include <QSettings>
#include "config.h"

GuideDialog::GuideDialog(QWidget *parent) :
    QDialog(parent)
{
        QPushButton *mButtonOk = new QPushButton("OK");
        QString mStringText = QString::fromLocal8Bit("<table><tr valign=\"middle\"><td align=\"left\"><img src=\"%1\"></td>"
                                   "<td><font color=\"blue\"><b>Knowledge Base source Editor</b></font> is an application,<br>"
                                   "that aims to assist in creating and editing snippets of knowledge bases of intelligent systems"
                                   "the design is based on technology OSTIS(<font color=\"blue\">http://www.ostis.net</b></font>)"
                                   "The basis of the editor of the principle of visualization of the data stored in the knowledge base,"
                                   "which greatly simplifies the process of editing and speeds up the process of designing a knowledge base.</td></tr></table>")
                .arg(QFileInfo(Config::pathIcons, "help-about-logo.png").absoluteFilePath());
        QTextBrowser *mTextBrowser = new QTextBrowser();
        mTextBrowser->setText(mStringText);
        QPushButton *mButtonCancel = new QPushButton("Cancel");
        mCheckBox = new QCheckBox("Don't show this again next time");
        QVBoxLayout *mVLayout = new QVBoxLayout();
        QHBoxLayout *mHLayout = new QHBoxLayout();
        mHLayout->addWidget(mButtonOk);
        mHLayout->addWidget(mButtonCancel);
        mVLayout->addWidget(mTextBrowser);
        mVLayout->addWidget(mCheckBox);
        mVLayout->addLayout(mHLayout);
        this->setLayout(mVLayout);
        setWindowTitle("Start Guide");
        connect(mButtonOk,SIGNAL(clicked()),this,SLOT(setSetting()));
        connect(mButtonCancel,SIGNAL(clicked()),this,SLOT(close()));
        QSettings settings;
        if (settings.value("dontShowWindowOnStart").toBool())
            mCheckBox->setChecked(true);
        resize(420,300);
}

void GuideDialog::setSetting()
{
    QSettings *settings = new QSettings();
    settings->setValue("dontShowWindowOnStart",mCheckBox->isChecked());
    close();
}
