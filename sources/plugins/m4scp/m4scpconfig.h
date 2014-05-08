#ifndef M4SCPCONFIG_H
#define M4SCPCONFIG_H

#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QComboBox>

class M4SCpConfig : public QWidget
{
    Q_OBJECT
public:
    explicit M4SCpConfig(QWidget *parent = 0);

    static int mSizeText;
    static QString mStyleText;
    static const int mSizeTextDifault = 11;

private:
    QLineEdit *sizeTextEdit;
    QLabel *sizeTextLabel;
    QPushButton *acceptSizeTextButton;
    QWidget *widget;
    QComboBox *stylesList;

signals:

public slots:
    void setSizeText();
    void setStyleText();

};


#endif // M4SCPCONFIG_H
