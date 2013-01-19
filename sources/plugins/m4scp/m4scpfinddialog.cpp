#include <QtGui>
#include "m4scpfinddialog.h"

M4SCpFindDialog::M4SCpFindDialog(M4SCpCodeEditor *editor, QWidget *parent):
    QDialog(parent),
    mEditor(editor)
{
    mForwardCounterClicked = 0;
    mBackwardCounterClicked = -1;

    mFindLabel = new QLabel(tr("&Find"), this);
    mFindLineEdit = new QLineEdit(this);
    mFindLabel->setBuddy(mFindLineEdit);

    mReplaceWithLabel = new QLabel(tr("R&eplace with"), this);
    mReplaceWithLineEdit = new QLineEdit(this);
    mReplaceWithLabel->setBuddy(mReplaceWithLineEdit);

    mForwardRadioButton = new QRadioButton(tr("F&orward"), this);
    mForwardRadioButton->setChecked(true);
    mBackwardRadioButton = new QRadioButton(tr("&Backward"), this);

    mDirectionGroupBox = new QGroupBox(tr("Direction"), this);
    QVBoxLayout *mDirectionLayout = new QVBoxLayout();
    mDirectionLayout->addWidget(mForwardRadioButton);
    mDirectionLayout->addWidget(mBackwardRadioButton);
    mDirectionGroupBox->setLayout(mDirectionLayout);

    mCaseSensitiveCheckBox = new QCheckBox(tr("&Case sensitive"), this);
    mWholeWordCheckBox = new QCheckBox(tr("&Whole word"), this);

    mOptionsGroupBox = new QGroupBox(tr("Options"), this);
    QVBoxLayout *mOptionsLayout = new QVBoxLayout();
    mOptionsLayout->addWidget(mCaseSensitiveCheckBox);
    mOptionsLayout->addWidget(mWholeWordCheckBox);
    mOptionsGroupBox->setLayout(mOptionsLayout);

    mFindButton = new QPushButton(tr("Fi&nd"), this);
    mReplaceButton = new QPushButton(tr("&Replace"), this);
    mReplaceAllButton = new QPushButton(tr("Replace &All"), this);
    mCloseButton = new QPushButton(tr("Close"), this);

    mStatusLabel = new QLabel(tr("String Not Found"), this);
    mStatusLabel->hide();

    QGridLayout *leftLayout = new QGridLayout();
    leftLayout->addWidget(mFindLabel, 0, 0);
    leftLayout->addWidget(mFindLineEdit, 0, 1);
    leftLayout->addWidget(mReplaceWithLabel, 1, 0);
    leftLayout->addWidget(mReplaceWithLineEdit, 1, 1);
    leftLayout->addWidget(mDirectionGroupBox, 2, 0, 1, 1);
    leftLayout->addWidget(mOptionsGroupBox, 2, 1, 1, 1);
    leftLayout->addWidget(mStatusLabel, 3, 0, 1, 2);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(mFindButton);
    rightLayout->addWidget(mReplaceButton);
    rightLayout->addWidget(mReplaceAllButton);
    rightLayout->addStretch();
    rightLayout->addWidget(mCloseButton);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);

    setLayout(layout);

    setWindowTitle(tr("Find/Replace"));

    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(mFindButton, SIGNAL(clicked()), this, SLOT(findInCode()));
    connect(mReplaceButton, SIGNAL(clicked()), this, SLOT(replaceInCode()));
    connect(mReplaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAllInCode()));
    connect(mFindLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));
    connect(mWholeWordCheckBox, SIGNAL(clicked()), this, SLOT(windowOpacity()));
    connect(mCaseSensitiveCheckBox, SIGNAL(clicked()), this, SLOT(windowOpacity()));
    connect(mForwardRadioButton, SIGNAL(clicked()), this, SLOT(directionChanged()));
    connect(mBackwardRadioButton, SIGNAL(clicked()), this, SLOT(directionChanged()));
}

M4SCpFindDialog::~M4SCpFindDialog()
{
    delete mFindLabel;
    delete mReplaceWithLabel;
    delete mFindLineEdit;
    delete mReplaceWithLineEdit;
    delete mForwardRadioButton;
    delete mBackwardRadioButton;
    delete mCaseSensitiveCheckBox;
    delete mWholeWordCheckBox;
    delete mDirectionGroupBox;
    delete mOptionsGroupBox;
    delete mFindButton;
    delete mReplaceButton;
    delete mReplaceAllButton;
    delete mCloseButton;
}

void M4SCpFindDialog::findInCode()
{
    if(mStatusLabel->isVisible())
        mStatusLabel->hide();
    QString code = mEditor->document()->toPlainText();
    QString findText = mFindLineEdit->text();
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if(mCaseSensitiveCheckBox->isChecked())
        cs = Qt::CaseSensitive;
    if(!code.contains(findText, cs))
    {
        showMessage("String Not Found");
        return;
    }
    int index = -1;
    if(mForwardRadioButton->isChecked())
        index = code.indexOf(findText, mForwardCounterClicked, cs);
    if(mBackwardRadioButton->isChecked())
        index = code.lastIndexOf(findText, mBackwardCounterClicked, cs);
    if(index==-1)
    {
        if(mForwardRadioButton->isChecked())
        {
            mForwardCounterClicked = 0;
            index = code.indexOf(findText, mForwardCounterClicked, cs);
        }
        if(mBackwardRadioButton->isChecked())
        {
            mBackwardCounterClicked = -1;
            index = code.lastIndexOf(findText, mBackwardCounterClicked, cs);
        }
        showMessage("Wrapped search");
    }
    if(mWholeWordCheckBox->isChecked())
    {
        QTextEdit *textEdit = new QTextEdit(code);
        if(!textEdit->find(findText, QTextDocument::FindWholeWords))
        {
            showMessage("Wrapped search");
            return;
        }
        else
        {
            if(mForwardRadioButton->isChecked())
            {
                index = code.indexOf(QRegExp("\\b"+findText+"\\b"), mForwardCounterClicked);
                mForwardCounterClicked = index+findText.size();
            }
            if(mBackwardRadioButton->isChecked())
            {
                index = code.lastIndexOf(QRegExp("\\b"+findText+"\\b"), mBackwardCounterClicked);
                mBackwardCounterClicked=index-1;
            }
            if(index==-1)
            {
                if(mForwardRadioButton->isChecked())
                {
                    mForwardCounterClicked = 0;
                    index = code.indexOf(findText, mForwardCounterClicked, cs);
                }
                if(mBackwardRadioButton->isChecked())
                {
                    mBackwardCounterClicked = -1;
                    index = code.lastIndexOf(findText, mBackwardCounterClicked, cs);
                }
                showMessage("Wrapped search");
            }
        }
    }
    QTextCursor cursor = mEditor->textCursor();
    cursor.setPosition(index);
    cursor.setPosition(index+findText.size(), QTextCursor::KeepAnchor);
    mEditor->setTextCursor(cursor);
    if(mForwardRadioButton->isChecked())
        mForwardCounterClicked = index+findText.size();
    if(mBackwardRadioButton->isChecked())
        mBackwardCounterClicked=index-1;
    setWindowOpacity(0.85);
}

void M4SCpFindDialog::replaceInCode()
{
    if(mStatusLabel->isVisible())
        mStatusLabel->hide();
    QString code = mEditor->document()->toPlainText();
    QString findText = mFindLineEdit->text();
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if(mCaseSensitiveCheckBox->isChecked())
        cs = Qt::CaseSensitive;
    if(!code.contains(findText, cs))
    {
        showMessage("String Not Found");
        return;
    }
    int index = code.indexOf(findText, cs);
    if(mWholeWordCheckBox->isChecked())
    {
        QTextEdit *textEdit = new QTextEdit(code);
        if(!textEdit->find(findText, QTextDocument::FindWholeWords))
        {
            showMessage("Wrapped search");
            return;
        }
        else
            index = code.indexOf(QRegExp("\\b"+findText+"\\b"));
    }

    code.replace(index,findText.size(),mReplaceWithLineEdit->text());
    mEditor->setPlainText(code);
    showMessage("Match replaced");
}

void M4SCpFindDialog::replaceAllInCode()
{
    if(mStatusLabel->isVisible())
        mStatusLabel->hide();
    QString code = mEditor->document()->toPlainText();
    QString findText = mFindLineEdit->text();
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if(mCaseSensitiveCheckBox->isChecked())
        cs = Qt::CaseSensitive;
    if(!code.contains(findText, cs))
    {
        showMessage("String Not Found");
        return;
    }
    if(mWholeWordCheckBox->isChecked())
    {
        QTextEdit *textEdit = new QTextEdit(code);
        if(!textEdit->find(findText, QTextDocument::FindWholeWords))
        {
            showMessage("Wrapped search");
            return;
        }
        else
        {
            while(textEdit->find(findText, QTextDocument::FindWholeWords))
            {
                int index = code.indexOf(QRegExp("\\b"+findText+"\\b"));
                code.replace(index, findText.size(), mReplaceWithLineEdit->text());
                textEdit = new QTextEdit(code);
            }
        }
    }
    else
        code.replace(findText, mReplaceWithLineEdit->text(), cs);
    mEditor->setPlainText(code);
    showMessage("All match replaced");
}

void M4SCpFindDialog::textChanged()
{
    mForwardCounterClicked = 0;
    mBackwardCounterClicked = -1;
    mStatusLabel->hide();
    setWindowOpacity(1);
}

void M4SCpFindDialog::clearLinesEdits()
{
    mForwardCounterClicked = 0;
    mBackwardCounterClicked = -1;
    setWindowOpacity(1);
    mFindLineEdit->clear();
    mReplaceWithLineEdit->clear();
    mForwardRadioButton->setChecked(true);
    mCaseSensitiveCheckBox->setChecked(false);
    mWholeWordCheckBox->setChecked(false);
}

void M4SCpFindDialog::windowOpacity()
{
    mForwardCounterClicked = 0;
    mBackwardCounterClicked = -1;
    setWindowOpacity(1);
    if(mStatusLabel->isVisible())
        mStatusLabel->hide();
}

void M4SCpFindDialog::showMessage(QString message)
{
    mStatusLabel->setText(message);
    mStatusLabel->show();
    QApplication::beep();
}

void M4SCpFindDialog::directionChanged()
{
    setWindowOpacity(1);
    if(mBackwardRadioButton->isChecked())
        mBackwardCounterClicked = mForwardCounterClicked-1;
    if(mForwardRadioButton->isChecked())
        mForwardCounterClicked = mBackwardCounterClicked+mFindLineEdit->text().size();
    if(mStatusLabel->isVisible())
        mStatusLabel->hide();
}
