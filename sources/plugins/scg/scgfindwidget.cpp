/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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
    Q_UNUSED(event);
}

void SCgFindWidget::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);
}

void SCgFindWidget::updateButtons()
{
    bool enable = !mFindLine->text().isEmpty();
    mFindNextButton->setEnabled(enable);
    mFindPreviousButton->setEnabled(enable);
}

void SCgFindWidget::caseSensitivityChanged(int val)
{
    Q_UNUSED(val);
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
