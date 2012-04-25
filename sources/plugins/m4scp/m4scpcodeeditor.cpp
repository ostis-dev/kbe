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
#include "m4scpblockdata.h"
#include "m4scpcodecompleter.h"
#include "m4scpsyntax.h"

#include <QPainter>
#include <QTextBlock>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QTextDocumentFragment>

M4SCpCodeEditor::M4SCpCodeEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    startSelectionBlockNumber(-1),
    endSelectionBlockNumber(-1),
    lineNumberAreaVisible(true),
    foldAreaVisible(true),
    mCompleter(0)

{
    setLineWrapMode(QPlainTextEdit::NoWrap);
    extraArea = new ExtraArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateExtraAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateExtraArea(QRect,int)));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(changeSelection()));
    connect(this, SIGNAL(textChanged()),this,SLOT(updateBlockLevels()));

    updateExtraAreaWidth();

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
    delete extraArea;
    delete mCompleter;
}

int M4SCpCodeEditor::extraAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = lineNumberAreaVisible ? 3 + fontMetrics().width(QLatin1Char('9')) * digits : 0;

    space += foldAreaVisible ? foldAreaWidht: 0;

    return space;
}

void M4SCpCodeEditor::updateExtraAreaWidth()
{
    setViewportMargins(extraAreaWidth(), 0, 0, 0);
}

void M4SCpCodeEditor::updateExtraArea(const QRect &rect, int dy)
{
    if (dy)
        extraArea->scroll(0, dy);
    else
        extraArea->update(0, rect.y(), extraArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateExtraAreaWidth();
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
    extraArea->setGeometry(QRect(cr.left(), cr.top(), extraAreaWidth(), cr.height()));
}

void M4SCpCodeEditor::keyPressEvent(QKeyEvent *e)
{
    if(BlockData::data(textCursor().block())->isFolded() && e->key()==Qt::Key_Return)
    {
        moveCursor(QTextCursor::PreviousBlock,QTextCursor::MoveAnchor);
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

    if (e->modifiers() == Qt::ShiftModifier &&
            (e->key() == Qt::Key_PageDown || e->key() == Qt::Key_PageUp))
    {
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

void M4SCpCodeEditor::extraAreaPaintEvent(QPaintEvent *event)
{

    QPainter painter(extraArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    BlockData *blockData;

    int level=0,curLevel;
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();

    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {

        blockData=BlockData::data(block);

        if (block.isVisible() && bottom >= event->rect().top()) {

            if(lineNumberAreaVisible){

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
                painter.drawText(0, top, extraArea->width()- (foldAreaVisible ? foldAreaWidht :0), fontMetrics().height(),
                                 Qt::AlignRight, number);
            }

            if(foldAreaVisible){
                curLevel=blockData->getFoldingLevel();
                int x=extraAreaWidth()-foldAreaWidht;
                if(curLevel>level){
                    drawIcon(&painter,x, top+2, blockData->isFolded() );
                }else
                    if(curLevel>0)
                        painter.drawLine(x+7,top,x+7,bottom);
                if(curLevel<level && level>0 && block.previous().isVisible()){
                    painter.drawLine(x+7,top,x+foldAreaWidht,top);
                }
                level=curLevel;
            }
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

void M4SCpCodeEditor::updateBlockLevels()
{
    //TODO  redefine this method in analyzer

    QString text;
    int i, level=0;
    for(QTextBlock it=document()->begin();it!=document()->end();it=it.next()){
        text=it.text();
        for(i=0;i<text.length();i++){
            if (text[i]=='(') {
                level++;
            }
            if (text[i]==')'&& level>0) {
                level--;
            }
        }
        BlockData::data(it)->setFoldingLevel(level);
    }
}

QRect M4SCpCodeEditor::drawIcon(QPainter *painter, int x,int y, bool folded)
{

    QRect iconRect(x+1,y+1,12,12);

    painter->drawRect(iconRect);
    painter->drawLine(x+3,y+7,x+11,y+7);

    if(folded){
        painter->drawLine(x+7,y+3,x+7,y+11);
    }

    return iconRect;
}

void M4SCpCodeEditor::foldOrUnfold(int blockNumber)
{
    QTextBlock block=document()->findBlockByNumber(blockNumber);
    BlockData *bd=BlockData::data(block);

    int level,curLevel;

    level=curLevel=bd->getFoldingLevel();
    if(!level) return;
    bool state=bd->isFolded();

    while(block.previous().isValid())
    {
         bd=BlockData::data(block.previous());
         curLevel=bd->getFoldingLevel();
         if(level>curLevel) break;
         block =  block.previous();
    }

    curLevel=level;
    BlockData::data(block)->setFolded(!state);

    while (block.next().isValid())
    {
        block=block.next();
        bd=BlockData::data(block);
        curLevel=bd->getFoldingLevel();

        if(curLevel<level)
            break;

        if(curLevel>level)
        {
            if(BlockData::data(block.previous())->getFoldingLevel() >= curLevel
                    && bd->isFolded())
                continue;
        }else
            bd->setFolded(!state);

        block.setLineCount(state ? 1 : 0 );
        block.setVisible(state);
    }
    if(!state) moveCursorFromFoldedBlocks();
}

void M4SCpCodeEditor::moveCursorFromFoldedBlocks()
{
    QTextCursor cursor= textCursor();
    QTextBlock block=cursor.block();

    if(block.isVisible())
        return;

    while(!block.isVisible())
    {
          block=block.previous();
          moveCursor(QTextCursor::PreviousBlock,QTextCursor::MoveAnchor);
    }
}

void M4SCpCodeEditor::extraAreaMousePressEvent(QMouseEvent *event)
{

    QTextCursor cursor=cursorForPosition(QPoint(0, event->pos().y()));
    if(event->pos().x() > (extraArea->width()-foldAreaWidht)  && foldAreaVisible )
    {

        foldOrUnfold(cursor.blockNumber());
        viewport()->update();
        extraArea->update();
    }
    if(event->pos().x() < (extraArea->width() - (foldAreaVisible ? foldAreaWidht : 0)) && lineNumberAreaVisible )
    {
        setTextCursor(cursor);
        moveCursor(QTextCursor::EndOfBlock,QTextCursor::KeepAnchor);
    }

}

