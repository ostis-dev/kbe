#ifndef M4SCPFINDDIALOG_H
#define M4SCPFINDDIALOG_H

#include <QDialog>
#include <m4scpcodeeditor.h>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QRadioButton;

class M4SCpFindDialog : public QDialog
{
    Q_OBJECT
public:
    M4SCpFindDialog(M4SCpCodeEditor *editor = 0, QWidget *parent = 0);
    ~M4SCpFindDialog();
    void clearLinesEdits();

private:
    QLabel *mFindLabel;
    QLabel *mReplaceWithLabel;
    QLineEdit *mFindLineEdit;
    QLineEdit *mReplaceWithLineEdit;
    QRadioButton *mForwardRadioButton;
    QRadioButton *mBackwardRadioButton;
    QGroupBox *mDirectionGroupBox;
    QGroupBox *mOptionsGroupBox;
    QPushButton *mFindButton;
    QPushButton *mReplaceButton;
    QPushButton *mReplaceAllButton;
    QPushButton *mCloseButton;
    QCheckBox *mCaseSensitiveCheckBox;
    QCheckBox *mWholeWordCheckBox;
    QLabel *mStatusLabel;

    QString mCodeString;
    M4SCpCodeEditor *mEditor;

    int mForwardCounterClicked;
    int mBackwardCounterClicked;

    void showMessage(QString message);

private slots:
    void findInCode();
    void replaceInCode();
    void replaceAllInCode();
    void textChanged();
    void windowOpacity();
    void directionChanged();

};

#endif // M4SCPFINDDIALOG_H
