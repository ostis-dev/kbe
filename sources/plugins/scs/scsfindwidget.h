/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCSCODEEDITORFINDWIDGET_H
#define SCSCODEEDITORFINDWIDGET_H

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

#endif // SCSCODEEDITORFINDWIDGET_H
