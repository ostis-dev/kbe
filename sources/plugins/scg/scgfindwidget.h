/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#ifndef FINDWIDGET_H_
#define FINDWIDGET_H_

#include <QtWidgets/QWidget>

class QCheckBox;
class QLabel;
class QLineEdit;
class QToolButton;

//! Simple find widget
class SCgFindWidget : public QWidget
{
    Q_OBJECT
public:
    SCgFindWidget(QWidget *parent = 0);

    ~SCgFindWidget();

    void show();
    void showAndClear();

    //! @return text in edit line.
    QString text() const;
    bool caseSensitive() const;

    /*! sets palette corresponding to @p found.
    *   (marks line edit red if element didn't found)
    */
    void setPalette(bool found);

    void setTextWrappedVisible(bool visible);

signals:
    void escapePressed();

    void findNext();
    void findPrevious();
    void find(const QString &text);

protected:
    void hideEvent(QHideEvent* event);
    void showEvent(QShowEvent * event);

private slots:
    void updateButtons();
    void textChanged(const QString &text);
    void caseSensitivityChanged(int);

private:
    bool eventFilter(QObject *object, QEvent *e);
    QToolButton* setupToolButton(const QString &text, const QString &icon);

private:
    QPalette mAppPalette;

    QLineEdit *mFindLine;
    QCheckBox *mCaseSensitivityChaeck;
    QLabel *mFindLabel;
    QLabel *mWrappedLabel;
    QToolButton *mFindNextButton;
    QToolButton *mCloseButton;
    QToolButton *mFindPreviousButton;
};

#endif /* FINDWIDGET_H_ */
