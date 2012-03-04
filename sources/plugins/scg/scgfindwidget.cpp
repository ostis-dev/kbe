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

#include "scgfindwidget.h"
#include "scgplugin.h"
#include "scgwindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QToolButton>
#include <QAction>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QHideEvent>

SCgFindWidget::SCgFindWidget(QWidget *parent):
        QWidget(parent),
        mAppPalette(qApp->palette())
{
    installEventFilter(this);
    setFixedHeight(22);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    mCloseButton = setupToolButton("", "find-close.png");

    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(hide()));
    layout->addWidget(mCloseButton);

    mFindLabel = new QLabel(tr("Find:"), this);
    layout->addWidget(mFindLabel);

    mFindLine = new QLineEdit(this);
    mFindLine->setFixedWidth(200);
    connect(mFindLine, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(mFindLine, SIGNAL(returnPressed()), this, SIGNAL(findNext()));
    connect(mFindLine, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));
    layout->addWidget(mFindLine);

    mFindPreviousButton = setupToolButton(tr("Previous"), "find-previous.png");
    connect(mFindPreviousButton, SIGNAL(clicked()), this, SIGNAL(findPrevious()));
    layout->addWidget(mFindPreviousButton);

    mFindNextButton = setupToolButton(tr("Next"), "find-next.png");
    layout->addWidget(mFindNextButton);
    connect(mFindNextButton, SIGNAL(clicked()), this, SIGNAL(findNext()));

    mCaseSensitivityChaeck = new QCheckBox(tr("Case Sensitive"), this);
    connect(mCaseSensitivityChaeck, SIGNAL(stateChanged(int)), this, SLOT(caseSensitivityChanged(int)));
    layout->addWidget(mCaseSensitivityChaeck);

    mWrappedLabel = new QLabel(this);
    mWrappedLabel->setScaledContents(true);
    mWrappedLabel->setTextFormat(Qt::RichText);
    mWrappedLabel->setMinimumSize(QSize(0, 20));
    mWrappedLabel->setMaximumSize(QSize(110, 20));
    mWrappedLabel->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    mWrappedLabel->setText(tr("Search wrapped"));
    mWrappedLabel->hide();
    layout->addWidget(mWrappedLabel);

    layout->addStretch();

    hide();

    updateButtons();
}

SCgFindWidget::~SCgFindWidget()
{

}

void SCgFindWidget::show()
{
    QWidget::show();
    mFindLine->selectAll();
    mFindLine->setFocus(Qt::ShortcutFocusReason);
}

void SCgFindWidget::showAndClear()
{
    show();
    mFindLine->clear();
}

QString SCgFindWidget::text() const
{
    return mFindLine->text();
}

bool SCgFindWidget::caseSensitive() const
{
    return mCaseSensitivityChaeck->isChecked();
}

void SCgFindWidget::setPalette(bool found)
{
    QPalette palette = mFindLine->palette();
    palette.setColor(QPalette::Active, QPalette::Base, found ? Qt::white
        : QColor(255, 102, 102));
    mFindLine->setPalette(palette);
}

void SCgFindWidget::setTextWrappedVisible(bool visible)
{
    mWrappedLabel->setVisible(visible);
}

void SCgFindWidget::hideEvent(QHideEvent* event)
{
//    if (!event->spontaneous())
//        qApp->setPalette(mAppPalette);
}

void SCgFindWidget::showEvent(QShowEvent* event)
{
//    if (!event->spontaneous()) {
//        QPalette p = mAppPalette;
//        p.setColor(QPalette::Inactive, QPalette::Highlight,
//            p.color(QPalette::Active, QPalette::Highlight));
//        p.setColor(QPalette::Inactive, QPalette::HighlightedText,
//            p.color(QPalette::Active, QPalette::HighlightedText));
//        qApp->setPalette(p);
//    }
}

void SCgFindWidget::updateButtons()
{
    bool enable = !mFindLine->text().isEmpty();
    mFindNextButton->setEnabled(enable);
    mFindPreviousButton->setEnabled(enable);
}

void SCgFindWidget::caseSensitivityChanged(int val)
{
    emit find(mFindLine->text());
}

void SCgFindWidget::textChanged(const QString &text)
{
    emit find(text);
}

bool SCgFindWidget::eventFilter(QObject *object, QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        if ((static_cast<QKeyEvent*>(e))->key() == Qt::Key_Escape) {
            hide();
            emit escapePressed();
        }
    }
    return QWidget::eventFilter(object, e);
}

QToolButton* SCgFindWidget::setupToolButton(const QString &text, const QString &icon)
{
    QToolButton *toolButton = new QToolButton(this);

    toolButton->setText(text);
    toolButton->setAutoRaise(true);
    toolButton->setIcon(SCgWindow::findIcon(icon));
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    return toolButton;
}
