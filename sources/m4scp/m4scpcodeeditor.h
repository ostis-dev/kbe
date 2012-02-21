#ifndef M4SCPCODEEDITOR_H
#define M4SCPCODEEDITOR_H

#include <QPlainTextEdit>

class M4SCpCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit M4SCpCodeEditor(QWidget *parent = 0);
    
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
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
};


#endif // M4SCPCODEEDITOR_H
