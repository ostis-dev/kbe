/*#include "startpage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

StartPage::StartPage(QWidget *parent): QDialog(parent)
{
    setWindowTitle(tr("Welcome to KBE 3.1.0"));
    dontShow = new QCheckBox(tr("Don't show this again"));
    closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *downLayout = new QHBoxLayout();
    downLayout->addWidget(dontShow);
    downLayout->addWidget(closeButton);

    newFileButton = new QPushButton(tr("New File..."));
    newFileButton->setDefault(true);
    openFileButton = new QPushButton(tr("Open File..."));
    exitButton = new QPushButton(tr("Exit"));

    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    buttonsLayout->addWidget(newFileButton);
    buttonsLayout->addWidget(openFileButton);
    buttonsLayout->addWidget(exitButton);
    buttonsLayout->addLayout(downLayout);

    setLayout(buttonsLayout);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}


StartPage::~StartPage()
{

}

*/
