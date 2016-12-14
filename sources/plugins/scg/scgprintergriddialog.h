/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>

class QVBoxLayout;
class QCheckBox;
class QGroupBox;
class QFormLayout;
class QLabel;
class QComboBox;
class QDialogButtonBox;

class SCgPrinterGridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SCgPrinterGridDialog(QWidget *parent = 0);
    ~SCgPrinterGridDialog();

    bool isPrinterGridEnabled() const;
    QSizeF paperSize() const;

private:
    QVBoxLayout *mVerticalLayout;
    QCheckBox *mEnableCheckbox;
    QGroupBox *mGroupBox;
    QFormLayout *mFormLayout;
    QLabel *mSizeLabel;
    QComboBox *mPagePaperSizeComboBox;
    QLabel *mOrientationLabel;
    QComboBox *mPagePaperOrientationComboBox;
    QDialogButtonBox *mButtonBox;

    int mPagePaperSizeIndex;
    int mPagePaperOrientationIndex;
    bool mIsPrintGridEnabled;

private slots:
    void onEnableCheckboxStateChanged(bool toggled);
    void onPressAccepted();
    void onPressRejected();
};


