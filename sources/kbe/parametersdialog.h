#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QSettings>
#include <QCheckBox>

class ParametersDialog: public QDialog
{
    Q_OBJECT
public:
    explicit ParametersDialog(QWidget *parent);
    virtual ~ParametersDialog();

private:


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
    //QSettings *settings;
    QCheckBox *showStartupDialog;
};


class M4SCpParametersTab: public QWidget
{
    Q_OBJECT
public:
    M4SCpParametersTab(QWidget *parent = 0);
};


class SCgParametersTab : public QWidget
 {
     Q_OBJECT

 public:
     SCgParametersTab(QWidget *parent = 0);
 };
#endif // PARAMETERSDIALOG_H
