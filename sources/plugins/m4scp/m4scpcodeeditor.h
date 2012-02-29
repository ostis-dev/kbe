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

#ifndef M4SCPCODEEDITOR_H
#define M4SCPCODEEDITOR_H

#include <QPlainTextEdit>
#include <QModelIndex>

class M4SCpCodeCompleter;

class LineNumberArea;

class M4SCpCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit M4SCpCodeEditor(QWidget *parent = 0);
    virtual ~M4SCpCodeEditor();
    
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    //! Return text under cursor
    QString textUnderCursor();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect &, int);

    //! Slot to insert completion
    void insertCompletion(QModelIndex index);

    void changeSelection();

private:
    LineNumberArea *lineNumberArea;

    int startSelectionBlockNumber;
    int endSelectionBlockNumber;


    //! Pointer to code completer
    M4SCpCodeCompleter *mCompleter;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(M4SCpCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    M4SCpCodeEditor *codeEditor;
    int startSelectionBlockNumber;
    int endSelectionBlockNumber;
};


#endif // M4SCPCODEEDITOR_H
