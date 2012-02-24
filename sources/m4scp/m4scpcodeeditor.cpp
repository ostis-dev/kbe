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

#include "m4scpcodeeditor.h"
#include "m4scpcodecompleter.h"
#include "m4scpsyntax.h"

#include <QPainter>
#include <QTextBlock>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QTextDocumentFragment>
#include <QDebug>

M4SCpCodeEditor::M4SCpCodeEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    startSelectionBlockNumber(-1),
    endSelectionBlockNumber(-1),
    mCompleter(0)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(changeSelection()));

    updateLineNumberAreaWidth();

    // create auto completer
    mCompleter = new M4SCpCodeCompleter(this);
    mCompleter->initDictionary();
    mCompleter->setWidget(this);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);
    mCompleter->setCaseSensitivity(Qt::CaseSensitive);
    mCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    connect(mCompleter, SIGNAL(activated(QModelIndex)), this, SLOT(insertCompletion(QModelIndex)));
}

M4SCpCodeEditor::~M4SCpCodeEditor()
{
    delete lineNumberArea;
    delete mCompleter;
}

int M4SCpCodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void M4SCpCodeEditor::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void M4SCpCodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

QString M4SCpCodeEditor::textUnderCursor()
{
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::WordLeft, QTextCursor::KeepAnchor);

    return tc.selectedText();
}

void M4SCpCodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void M4SCpCodeEditor::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ShiftModifier && (e->key() == Qt::Key_PageDown || Qt::Key_PageUp)) {
        QPlainTextEdit::keyPressEvent(e);
        emit selectionChanged();
        e->accept();
        return;
    }
    if (mCompleter->popup()->isVisible())
    {
        if (e->key() == Qt::Key_Escape ||
                e->key() == Qt::Key_Enter ||
                e->key() == Qt::Key_Return ||
                e->key() == Qt::Key_Tab ||
                e->key() == Qt::Key_Backtab)
        {
            e->ignore();
            return;
        }
    }

    bool isShortcut = (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Space);
    if (!isShortcut)
        QPlainTextEdit::keyPressEvent(e);

    bool ctrlOrShift = e->modifiers() == Qt::ControlModifier || e->modifiers() == Qt::ShiftModifier;
    if (ctrlOrShift && e->text().isEmpty())
        return;

    bool hasModifier = ((e->modifiers() != Qt::NoModifier) && !ctrlOrShift);

    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier ||
                        e->text().isEmpty() ||
                        completionPrefix.length() < 1 ||
                        M4SCpSyntax::eow().contains(e->text().right(1))))
    {
        mCompleter->popup()->hide();
        return;
    }

    if (completionPrefix != mCompleter->completionPrefix())
    {
        mCompleter->setCompletionPrefix(completionPrefix);
        mCompleter->popup()->setCurrentIndex(mCompleter->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(mCompleter->popup()->sizeHintForColumn(0) +
                mCompleter->popup()->verticalScrollBar()->sizeHint().width());
    mCompleter->complete(cr);
}

void M4SCpCodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();

    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();

    int bottom = top + (int) blockBoundingRect(block).height();;
    while (block.isValid() && top <= event->rect().bottom()) {

        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(block.blockNumber() + 1);
            painter.setPen(Qt::black);
            if (block.blockNumber() <= endSelectionBlockNumber &&
                block.blockNumber() >= startSelectionBlockNumber &&
                    startSelectionBlockNumber != -1 && endSelectionBlockNumber != -1) {
                painter.setBackground(QBrush(Qt::darkGray));
                painter.setBackgroundMode(Qt::OpaqueMode);
            }
            else {
                painter.setBackground(QBrush(Qt::lightGray));
                painter.setBackgroundMode(Qt::OpaqueMode);
            }
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top +  blockBoundingRect(block).height();
    }
}

void M4SCpCodeEditor::insertCompletion(QModelIndex index)
{
    QTextCursor tc = textCursor();

    QString templ = mCompleter->completionModel()->data(index, Qt::UserRole).toString();
    if (templ.isEmpty()) templ = mCompleter->completionModel()->data(index, Qt::DisplayRole).toString();
    quint32 extra = templ.length() - mCompleter->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(templ.right(extra));
    setTextCursor(tc);
}


void M4SCpCodeEditor::changeSelection() {
    QTextCursor cur = textCursor();
    startSelectionBlockNumber = document()->findBlock(cur.selectionStart()).blockNumber();
    endSelectionBlockNumber = document()->findBlock(cur.selectionEnd() - 1).blockNumber();
    if (cur.selection().isEmpty()) {
        startSelectionBlockNumber = -1;
        endSelectionBlockNumber = -1;
    }
}
