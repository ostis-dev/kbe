/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scscodeeditor.h"

#include <QPainter>
#include <QTextBlock>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QDebug>
#include "scscodeanalyzer.h"
#include "scscodecompleter.h"
#include "scsfindwidget.h"
#include "scserrortablewidget.h"
#include "scscodeerroranalyzer.h"

#include "scsparserwrapper.h"

#define SPACE_FOR_ERROR_LABEL 20

SCsCodeEditor::SCsCodeEditor(QWidget *parent, SCsErrorTableWidget *errorTable)
    : QPlainTextEdit(parent)
    , mErrorTable(errorTable)
    , mLastCursorPosition(0)
    , mIsTextInsert(false)
{
    mLineNumberArea = new SCsLineNumberArea(this);
	mAnalyzer = new SCsCodeAnalyzer(this);
    mCompleter = new SCsCodeCompleter(this);
    mErrorAnalyzer = new SCsCodeErrorAnalyzer(this, mErrorTable);

    mCompleter->setWidget(this);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);
    mCompleter->setCaseSensitivity(Qt::CaseSensitive);
    mCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    mErrorPixmap = QPixmap(":scs/media/icons/error.png").scaledToHeight(15);

    connect(mCompleter, SIGNAL(activated(QModelIndex)), this, SLOT(insertCompletion(QModelIndex)));

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(updateAnalyzer()));
	connect(mErrorAnalyzer,SIGNAL(errorLines(QSet<int>)),this,SLOT(setErrorsLines(QSet<int>)));

    if (mErrorTable != NULL)
        connect(mErrorTable, SIGNAL(errorAt(int,int)), this, SLOT(moveTextCursor(int,int)));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

void SCsCodeEditor::setDocumentPath(const QString &path)
{
    Q_UNUSED(path);
	mAnalyzer->parse(toPlainText(), (QStandardItemModel*)mCompleter->model());
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

    return space + SPACE_FOR_ERROR_LABEL;
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
             if (isLineWithError(blockNumber+1))
                 painter.drawPixmap(4,top+2,mErrorPixmap);
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
    if ((e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Tab)
            || e->key() == Qt::Key_Backtab)
    {
        e->ignore();
        return;
    }

//     if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_F)
//     {
//         mFinder->show();
//         mFinder->setFocus();
//         mCompleter->popup()->update();
//         return;
//     }

	if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_R)
        updateErrorAnalyzer();

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

//     if (e->key() == Qt::Key_Escape && mFinder->isVisible())
//     {
//          mFinder->hide();
//          return;
//     }

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
                          completionPrefix.length() < SCsCodeCompleter::MinCompletetionLength /* ||
						  !SCsCodeAnalyzer::isIdentifier(e->text().right(1))  ||
						  mAnalyzer->isInEmptyBlock(textCursor().position())*/ ))
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

	mIsTextInsert = true;
}

void SCsCodeEditor::updateAnalyzer()
{

    QStandardItemModel* completerModel = static_cast<QStandardItemModel*>(mCompleter->model());

    QTextCursor tc = textCursor();

    tc.select( QTextCursor::WordUnderCursor );
    QString currentWord = tc.selectedText();

    mLastCursorPosition = tc.position();
    mAnalyzer->ignoreUpdate(currentWord);

    mAnalyzer->asynchUpdate(toPlainText(), completerModel);
}

void SCsCodeEditor::updateErrorAnalyzer()
{

	QString text = document()->toPlainText();

	mErrorAnalyzer->parse(text);

	//update();
}



bool SCsCodeEditor::isLineWithError(int line)
{
    return mErrorLines.contains(line);
}

void SCsCodeEditor::setErrorsLines(const QSet<int> &lines)
{
    mErrorLines = lines;
	update();
}


void SCsCodeEditor::moveTextCursor(int line, int charPos)
{

    if (charPos<0)
		charPos = 0;

    if (line < 0)
        line = 0;

    QTextCursor cursor = textCursor();
	cursor.movePosition(QTextCursor::Start);
	
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line-1);
    if (cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor))
    {
        if (cursor.columnNumber() < charPos)
            charPos = 0;
    }
    cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, charPos+1);

	setTextCursor(cursor);
	setFocus(Qt::ShortcutFocusReason);
}
