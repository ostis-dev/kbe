/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextDocument>
#include <QToolButton>

class SCsFindWidget : public QWidget
{
    Q_OBJECT
public:
    SCsFindWidget(QWidget *parent=0);
	~SCsFindWidget();
	void show();
	void show(const QString &text);
	void showAndClear();
	QString text() const;
	bool caseSensitive() const;
	bool wholeWord() const;
	void setPalette(bool found);

    QTextDocument::FindFlags getFlags() const;

    void find();

public slots:

signals:
	void escapePressed();
	void findNext();
	void findPrevious();
	void find(const QString &text);

protected:

private slots:
	void updateButtons();
	void textChanged(const QString &text);
	void caseSensitivityChanged(int);
	void wholeWordChanged(int);


private:
    QToolButton* setupToolButton(const QString& text, const QString& icon);
	bool eventFilter(QObject *object, QEvent *e);
    QLineEdit *mSearchEdit;
    QCheckBox *mCaseSensitiveCheck;
    QCheckBox *mFindWholeWordCheck;

    QToolButton *mFindNextButton;
    QToolButton *mFindPreviousButton;
    QToolButton *mCloseButton;
};
