#pragma once

#include <QDialog>

class QBoxLayout;

class SCgTypeSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    SCgTypeSelectionDialog(const QString& type, QWidget* parent = 0);

    QString getChosenType() const;

public slots:
    void onChooseType();

private:
    void addTypeButton(const QIcon& icon, const QString& text, QBoxLayout* layout);

    QString mChosenType;
};
