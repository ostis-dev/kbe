/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QTextDocument>

#include <QDebug>

#include "scsfindwidget.h"
#include "scscodeeditor.h"


SCsFindWidget::SCsFindWidget(QWidget *parent/* =0 */):
    QWidget(parent)
{
	//installEventFilter(this);

    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    this->setFont(font);
	setMaximumHeight(35);


	mSearchEdit = new QLineEdit(this);
	mSearchEdit->setMinimumWidth(80);
	
	connect(mSearchEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
	connect(mSearchEdit, SIGNAL(returnPressed()), this, SIGNAL(findNext()));
	connect(mSearchEdit, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));


    mFindPreviousButton = setupToolButton(tr("Previous"), ":scs/media/icons/find-previous.png");
    connect(mFindPreviousButton, SIGNAL(clicked()), this, SIGNAL(findPrevious()));
    mFindNextButton = setupToolButton(tr("Next"), ":scs/media/icons/find-next.png");
    connect(mFindNextButton, SIGNAL(clicked()), this, SIGNAL(findNext()));

    mCaseSensitiveCheck = new QCheckBox(tr("Case sensitive"),this);
    mFindWholeWordCheck = new QCheckBox(tr("Whole word"),this);


	connect(mCaseSensitiveCheck, SIGNAL(stateChanged(int)), this, SLOT(caseSensitivityChanged(int)));
	connect(mFindWholeWordCheck, SIGNAL(stateChanged(int)), this, SLOT(wholeWordChanged(int)));

    mCloseButton = setupToolButton("", ":scs/media/icons/find-close.png");
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(hide()));
    mCloseButton->setFixedHeight(28);
    mCloseButton->setFixedWidth(28);

    QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(0,0,0,0);
    layout->addWidget(mCloseButton);
    layout->addWidget(mSearchEdit);
    layout->addWidget(mFindPreviousButton);
    layout->addWidget(mFindNextButton);
    layout->addWidget(mCaseSensitiveCheck);
    layout->addWidget(mFindWholeWordCheck);

    layout->setContentsMargins(QMargins(0,5,20,0));

	layout->addStretch();

    setLayout(layout);

	hide();
}

SCsFindWidget::~SCsFindWidget()
{

}

QTextDocument::FindFlags SCsFindWidget::getFlags() const
{
    QTextDocument::FindFlags searchFlags;

    if (mCaseSensitiveCheck->isChecked())
    {
        searchFlags |= QTextDocument::FindCaseSensitively;
    }
    if (mFindWholeWordCheck->isChecked())
    {
        searchFlags |= QTextDocument::FindWholeWords;
    }

    return searchFlags;
}


void SCsFindWidget::show()
{
	QWidget::show();
    mSearchEdit->selectAll();
	mSearchEdit->setFocus(Qt::ShortcutFocusReason);
	
}


void SCsFindWidget::show(const QString &text)
{
	QWidget::show();
	mSearchEdit->setText(text);
	mSearchEdit->selectAll();
	mSearchEdit->setFocus(Qt::ShortcutFocusReason);
}


void SCsFindWidget::showAndClear()
{
	show();
	mSearchEdit->clear();
}


QString SCsFindWidget::text() const
{
	return mSearchEdit->text();
}


bool SCsFindWidget::caseSensitive() const
{
	return mCaseSensitiveCheck->isChecked();
}

bool SCsFindWidget::wholeWord() const
{
	return mFindWholeWordCheck->isChecked();
}


void SCsFindWidget::setPalette(bool found)
{
	QPalette palette = mSearchEdit->palette();
	palette.setColor(QPalette::Active, QPalette::Base, found ? Qt::white
		: QColor(255, 102, 102));
	mSearchEdit->setPalette(palette);
}



void SCsFindWidget::updateButtons()
{
	bool enable = !mSearchEdit->text().isEmpty();
	mFindNextButton->setEnabled(enable);
	mFindPreviousButton->setEnabled(enable);
}



void SCsFindWidget::caseSensitivityChanged(int val)
{
    Q_UNUSED(val)
	emit find(mSearchEdit->text());
}


void SCsFindWidget::wholeWordChanged(int val)
{
    Q_UNUSED(val)
	emit find(mSearchEdit->text());
}


void SCsFindWidget::textChanged(const QString &text)
{
	emit find(text);
}


bool SCsFindWidget::eventFilter(QObject *object, QEvent *e)
{
	if (e->type() == QEvent::KeyPress) {
		if ((static_cast<QKeyEvent*>(e))->key() == Qt::Key_Escape) {
			hide();
			emit escapePressed();
		}
	}
	return QWidget::eventFilter(object, e);
}


QToolButton* SCsFindWidget::setupToolButton(const QString &text, const QString &icon)
{
    QToolButton *toolButton = new QToolButton(this);

    toolButton->setText(text);
    toolButton->setAutoRaise(true);
    toolButton->setIcon(QIcon(icon));
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    return toolButton;
}
