#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QSettings>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

class ParametersDialog: public QDialog
{
    Q_OBJECT
public:
    explicit ParametersDialog(QWidget *parent);
    virtual ~ParametersDialog();

    QPushButton *buttonOk;
    QPushButton *buttonCancel;

public slots:

};

class GeneralParametersTab: public QWidget
{
    Q_OBJECT
public:
    GeneralParametersTab(QWidget *parent = 0);

public slots:
    void showStateChanged(int state);

protected:
    QSettings settings;
    QCheckBox *showStartupDialog;
    QComboBox *languageList;
};
#endif // PARAMETERSDIALOG_H
