#ifndef M4SCPFINDER_H
#define M4SCPFINDER_H

#include "m4scpcodeeditor.h"

#include <QVector>
#include <QPair>
#include <QDialog>
#include <QTextDocument>

class QLabel;
class QLineEdit;
class QPushButton;

class M4SCpFinder: public QDialog
{
    Q_OBJECT
public:
    M4SCpFinder(M4SCpCodeEditor *mEditor);
    virtual ~M4SCpFinder();

signals:
    void find(QString *str);

private slots:
    void enableFindButton(const QString &text);
    void closeFindWindow();
    void findNext();
    void replaceText();
    void oneReplace();

private:
    QLabel * labelFind;
    QLabel * labelReplace;
    QLineEdit * lineEditFind;
    QLineEdit * lineEditReplace;
    QPushButton * findPrevButton;
    QPushButton * findNextButton;
    QPushButton * replaceButton;
    QPushButton * replaceAllButton;
    QPushButton * closeButton;

    M4SCpCodeEditor *mEditor;
    int index;

    QPair<QTextCursor,int> pairIndexes;
    QVector<QPair<QTextCursor,int> > replaceIndexes;

    void eraseBackground();
    void findText();
};

#endif // M4SCPFINDER_H


