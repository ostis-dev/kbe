/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QPlainTextEdit>
#include <QModelIndex>
#include <QGridLayout>
#include <QLabel>

class SCsCodeAnalyzer;
class SCsCodeAnalyzer;
class SCsCodeCompleter;
class SCsFindWidget;
class SCsErrorTableWidget;
class SCsCodeErrorAnalyzer;

class SCsCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    SCsCodeEditor(QWidget* parent = 0, SCsErrorTableWidget *errorTable = 0);
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

    void setDocumentPath(const QString &path);
   
protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);
    inline bool isLineWithError(int line);

    QString textUnderCursor();

    void updateErrorAnalyzer();

public slots:
	void setErrorsLines(const QSet<int> &lines);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void insertCompletion(QModelIndex index);
    void updateAnalyzer();
	void moveTextCursor(int line, int charPos);

private:
    QWidget *mLineNumberArea;
	SCsCodeAnalyzer *mAnalyzer;
    SCsCodeCompleter *mCompleter;
    SCsErrorTableWidget *mErrorTable;
	SCsCodeErrorAnalyzer *mErrorAnalyzer;

    QSet<int> mErrorLines;
    QPixmap mErrorPixmap;
	int mLastCursorPosition;
	bool mIsTextInsert;
};

class SCsLineNumberArea : public QWidget
{
public:
    SCsLineNumberArea(SCsCodeEditor *editor) : QWidget(editor)
    {
        mCodeEditor = editor;
    }

    QSize sizeHint() const
    {
        return QSize(mCodeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        mCodeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    SCsCodeEditor *mCodeEditor;

};

