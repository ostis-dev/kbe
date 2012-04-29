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

#include "scscodeeditor.h"

#include <QPainter>
#include <QTextBlock>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStandardItemModel>
#include "scscodeanalyzer.h"
#include "scscodecompleter.h"

SCsCodeEditor::SCsCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    mLineNumberArea = new SCsLineNumberArea(this);
    mAnalyzer = new SCsCodeAnalyzer(this);
    mCompleter = new SCsCodeCompleter(this);

    mCompleter->setWidget(this);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);
    mCompleter->setCaseSensitivity(Qt::CaseSensitive);
    mCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    connect(mCompleter, SIGNAL(activated(QModelIndex)), this, SLOT(insertCompletion(QModelIndex)));

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(updateAnalyzer()));


    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void SCsCodeEditor::setDocumentPath(const QString &path)
{
    mAnalyzer->setDocumentPath(path);
    mAnalyzer->parse( toPlainText(), (QStandardItemModel*)mCompleter->model() );
}

int SCsCodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void SCsCodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void SCsCodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
     if (dy)
         mLineNumberArea->scroll(0, dy);
     else
         mLineNumberArea->update(0, rect.y(), mLineNumberArea->width(), rect.height());

     if (rect.contains(viewport()->rect()))
         updateLineNumberAreaWidth(0);
}

void SCsCodeEditor::resizeEvent(QResizeEvent *e)
{
     QPlainTextEdit::resizeEvent(e);

     QRect cr = contentsRect();
     mLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void SCsCodeEditor::highlightCurrentLine()
{
     QList<QTextEdit::ExtraSelection> extraSelections;

     if (!isReadOnly())
     {
         QTextEdit::ExtraSelection selection;

         QColor lineColor = QColor(Qt::yellow).lighter(160);

         selection.format.setBackground(lineColor);
         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
         selection.cursor = textCursor();
         selection.cursor.clearSelection();
         extraSelections.append(selection);
     }

     setExtraSelections(extraSelections);
}

void SCsCodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
     QPainter painter(mLineNumberArea);
     painter.fillRect(event->rect(), Qt::lightGray);
     QTextBlock block = firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();
     while (block.isValid() && top <= event->rect().bottom())
     {
         if (block.isVisible() && bottom >= event->rect().top())
         {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, mLineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignRight, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
}

QString SCsCodeEditor::textUnderCursor()
{
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::WordLeft, QTextCursor::KeepAnchor);

    return tc.selectedText();
}

void SCsCodeEditor::keyPressEvent(QKeyEvent *e)
 {
    if (mCompleter->popup()->isVisible())
    {
        switch (e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
             e->ignore();
             return;
        default:
            break;
        }
     }

     bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E);
     if (!isShortcut)
         QPlainTextEdit::keyPressEvent(e);

     const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
     if (ctrlOrShift && e->text().isEmpty())
         return;

     bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
     QString completionPrefix = textUnderCursor();

     if (!isShortcut && ( hasModifier ||
                          e->text().isEmpty() ||
                          completionPrefix.length() < SCsCodeCompleter::MinCompletetionLength ||
                          !SCsCodeAnalyzer::isIdentifier(e->text().right(1)) ||
                          mAnalyzer->isInEmptyBlock(textCursor().position()) ))
     {
         mCompleter->popup()->hide();
         return;
     }

     if (completionPrefix != mCompleter->completionPrefix()) {
         mCompleter->setCompletionPrefix(completionPrefix);
         mCompleter->popup()->setCurrentIndex(mCompleter->completionModel()->index(0, 0));
     }
     QRect cr = cursorRect();
     cr.setWidth(mCompleter->popup()->sizeHintForColumn(0)
                 + mCompleter->popup()->verticalScrollBar()->sizeHint().width());
     mCompleter->complete(cr);
}

void SCsCodeEditor::insertCompletion(QModelIndex index)
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

void SCsCodeEditor::updateAnalyzer()
{
    QStandardItemModel* completerModel = static_cast<QStandardItemModel*>(mCompleter->model());

    QTextCursor tc = textCursor();
    tc.select( QTextCursor::WordUnderCursor );
    QString currentWord = tc.selectedText();

    mAnalyzer->ignoreUpdate(currentWord);
    mAnalyzer->update(toPlainText(), completerModel);
}
