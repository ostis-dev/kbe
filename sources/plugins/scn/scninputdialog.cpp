#include "scninputdialog.h"

SCnInputDialog::SCnInputDialog(QWidget *parent) :
    QDialog(parent)
{
    lineEdit = new QLineEdit();
    lineEdit->setFocus();

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    gridLayout = new QGridLayout();
    gridLayout->addWidget(lineEdit, 0, 0, 1, 1);
    gridLayout->addWidget(okButton, 1, 0, 1, 1);
    gridLayout->addWidget(cancelButton, 1, 1, 1, 1);

    this -> setLayout(gridLayout);
    this -> setWindowTitle("Input SCn Dialog");

    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
}

void SCnInputDialog::setExistingText(const QString &text)
{
    lineEdit->setText(text);
}

void SCnInputDialog::okButtonClicked()
{
    QString SCnText = SCnInputDialog::convertFromCommonTextToSCn(lineEdit->text());
    emit textRecieved(SCnText);
    lineEdit->clear();
    this->close();
}

void SCnInputDialog::cancelButtonClicked()
{
    lineEdit->clear();
    this->close();
}

QString SCnInputDialog::convertFromCommonTextToSCn(const QString &commonText)
{
    QString scnText(commonText);
    scnText.replace("&forall;", QChar(8704));   // for all, U+2200 ISOtech
    scnText.replace("&exist;", QChar(8707));    // there exists, U+2203 ISOtech
    scnText.replace("&empty;", QChar(8709));    // empty set = null set = diameter, U+2205 ISOamso
    scnText.replace("->", QChar(8712));     // element of, U+2208 ISOtech
    scnText.replace("-|>", QChar(8713));    // not an element of, U+2209 ISOtech
    scnText.replace("!=", QChar(8800));         // not equal to, U+2260 ISOtech
    scnText.replace(">=", QChar(8805));         // greater-than or equal to, U+2265 ISOtech
    scnText.replace("<=", QChar(8804));         // less-than or equal to, U+2264 ISOtech
    scnText.replace("&sub;", QChar(8834));      // subset of, U+2282 ISOtech
    scnText.replace("&sup;", QChar(8835));      // superset of, U+2283 ISOtech
    scnText.replace("&nsub;", QChar(8836));     // not a subset of, U+2284 ISOamsn
    scnText.replace("&sube;", QChar(8838));     // subset of or equal to, U+2286 ISOtech
    scnText.replace("&supe;", QChar(8839));     // superset of or equal to, U+2287 ISOtech
    return scnText;
}
