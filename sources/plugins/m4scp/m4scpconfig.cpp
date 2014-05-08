#include "m4scpconfig.h"
#include "m4scpwindow.h"

M4SCpConfig::M4SCpConfig(QWidget *parent) :
    QWidget(parent)
{
    widget = new QWidget(this);
    sizeTextLabel = new QLabel("Size: ");
    sizeTextEdit = new QLineEdit(QString::number(mSizeTextDifault));
    sizeTextEdit->setAlignment(Qt::AlignRight);
    acceptSizeTextButton = new QPushButton("Accept");
    QHBoxLayout *sizeTextLayout = new QHBoxLayout();
    sizeTextLayout->addWidget(sizeTextLabel);
    sizeTextLayout->addWidget(sizeTextEdit);
    sizeTextLayout->addWidget(acceptSizeTextButton);
    sizeTextLayout->addSpacing(300);

    stylesList = new QComboBox();
    stylesList->addItem("Arial");
    stylesList->addItem("Times");
    stylesList->addItem("Cambria");
    stylesList->addItem("Calibri");

    QVBoxLayout *vertical = new QVBoxLayout();
    vertical->addLayout(sizeTextLayout);
    vertical->addWidget(stylesList);

    setLayout(vertical);

    connect(acceptSizeTextButton, SIGNAL(clicked()), this, SLOT(setSizeText()));
    connect(stylesList, SIGNAL(activated(int)), this, SLOT(setStyleText()));
}

int M4SCpConfig::mSizeText = 0;
QString M4SCpConfig::mStyleText = "";

void M4SCpConfig::setSizeText()
{
    mSizeText = sizeTextEdit->text().toInt();
}

void M4SCpConfig::setStyleText()
{
    mStyleText = stylesList->currentText();
}
