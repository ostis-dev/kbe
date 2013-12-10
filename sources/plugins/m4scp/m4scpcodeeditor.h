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
#include <QShortcut>

class M4SCpCodeCompleter;

class ExtraArea;

class M4SCpCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit M4SCpCodeEditor(QWidget *parent = 0);
    virtual ~M4SCpCodeEditor();
    
    void extraAreaPaintEvent(QPaintEvent *event);
    void extraAreaMousePressEvent(QMouseEvent *event);
    int extraAreaWidth();

protected:
    //! Return text under cursor
    QString textUnderCursor();


    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void updateExtraAreaWidth();
    void updateExtraArea(const QRect &, int);
    void updateBlockLevels();

    //! Slot to insert completion
    void insertCompletion(QModelIndex index);

    void changeSelection();

private:
    ExtraArea *extraArea;

    int startSelectionBlockNumber;
    int endSelectionBlockNumber;

    bool lineNumberAreaVisible;

    bool foldAreaVisible;
    const static int foldAreaWidht=15;

    //! Pointer to code completer
    M4SCpCodeCompleter *mCompleter;

    QRect drawIcon(QPainter *, int y,int height, bool folded);
    void foldOrUnfold (int blockNumber);
    void moveCursorFromFoldedBlocks();
};

class ExtraArea : public QWidget
{
public:
    ExtraArea(M4SCpCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->extraAreaWidth(), 0);
    }



protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->extraAreaPaintEvent(event);
    }
    void mousePressEvent(QMouseEvent *event){
        codeEditor->extraAreaMousePressEvent( event);
    }

private:
    M4SCpCodeEditor *codeEditor;


    int startSelectionBlockNumber;
    int endSelectionBlockNumber;
};


#endif // M4SCPCODEEDITOR_H
