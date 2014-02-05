#ifndef SCNINPUTDIALOG_H
#define SCNINPUTDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

class SCnInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SCnInputDialog(QWidget *parent = 0);

    //! Set text of selected field
    void setExistingText(const QString &text);

    static QString convertFromCommonTextToSCn(const QString &commonText);
private:
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGridLayout *gridLayout;

signals:
    //! Give entered text after ok-button press
    void textRecieved(const QString &text);

public slots:
    //! Ok button handler
    void okButtonClicked();
    //! Cancel button handler
    void cancelButtonClicked();
};

#endif // SCNINPUTDIALOG_H
