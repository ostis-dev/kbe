/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QWidget>

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

