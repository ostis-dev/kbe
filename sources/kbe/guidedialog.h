#ifndef GUIDEDIALOG_H
#define GUIDEDIALOG_H

#include <QDialog>
#include <QCheckBox>

class GuideDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GuideDialog(QWidget *parent = 0);
private:
    QCheckBox *mCheckBox;

private slots:
    void setSetting();

};

#endif // GUIDEDIALOG_H
