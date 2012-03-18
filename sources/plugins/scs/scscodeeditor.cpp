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

SCsCodeEditor::SCsCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    this->lineNumberArea = new SCsLineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    this->updateLineNumberAreaWidth(0);
    this->highlightCurrentLine();
}

int SCsCodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + this->fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void SCsCodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void SCsCodeEditor::updateLineNumberArea(const QRect &rect, int dy)
 {
     if (dy)
         this->lineNumberArea->scroll(0, dy);
     else
         this->lineNumberArea->update(0, rect.y(), this->lineNumberArea->width(), rect.height());

     if (rect.contains(viewport()->rect()))
         this->updateLineNumberAreaWidth(0);
 }

void SCsCodeEditor::resizeEvent(QResizeEvent *e)
 {
     QPlainTextEdit::resizeEvent(e);

     QRect cr = this->contentsRect();
     this->lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), this->lineNumberAreaWidth(), cr.height()));
 }

void SCsCodeEditor::highlightCurrentLine()
 {
     QList<QTextEdit::ExtraSelection> extraSelections;

     if (!this->isReadOnly()) {
         QTextEdit::ExtraSelection selection;

         QColor lineColor = QColor(Qt::yellow).lighter(160);

         selection.format.setBackground(lineColor);
         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
         selection.cursor = textCursor();
         selection.cursor.clearSelection();
         extraSelections.append(selection);
     }

     this->setExtraSelections(extraSelections);
 }

void SCsCodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
 {
     QPainter painter(lineNumberArea);
     painter.fillRect(event->rect(), Qt::lightGray);
     QTextBlock block = this->firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();
     while (block.isValid() && top <= event->rect().bottom()) {
         if (block.isVisible() && bottom >= event->rect().top()) {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignRight, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
 }
