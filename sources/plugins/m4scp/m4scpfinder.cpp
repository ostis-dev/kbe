#include "m4scpfinder.h"

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QVector>
#include <QMessageBox>

M4SCpFinder::M4SCpFinder(M4SCpCodeEditor *doc) : QDialog(), mEditor(doc)
{
    setWindowTitle(tr("Find and replace"));
    labelFind = new QLabel(tr("Find text:"), this);
    labelReplace = new QLabel(tr("Replace:"), this);

    lineEditFind = new QLineEdit(this);
    lineEditReplace = new QLineEdit(this);

//    findPrevButton = new QPushButton(tr("Find Previous"), this);
//    findPrevButton->setDefault(false);
//    findPrevButton->setEnabled(false);

    findNextButton = new QPushButton(tr("Find Next"), this);
    findNextButton->setDefault(true);
    findNextButton->setEnabled(false);

    replaceButton = new QPushButton(tr("Replace"), this);
    replaceButton->setDefault(false);
    replaceButton->setEnabled(false);

    replaceAllButton = new QPushButton(tr("Replace all"), this);
    replaceAllButton->setDefault(false);
    replaceAllButton->setEnabled(false);

    closeButton = new QPushButton(tr("Cancel"), this);

    connect(lineEditFind, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString&)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeFindWindow()));
    connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNext()));
    connect(replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceText()));    
    connect(replaceButton, SIGNAL(clicked()), this, SLOT(oneReplace()) );


    QHBoxLayout *horizont1 = new QHBoxLayout();
    horizont1->addWidget(labelFind);
    horizont1->addWidget(lineEditFind);

    QHBoxLayout *horizont11 = new QHBoxLayout();
    horizont11->addWidget(labelReplace);
    horizont11->addWidget(lineEditReplace);

    QHBoxLayout *horizont2 = new QHBoxLayout();
//    horizont2->addWidget(findPrevButton);
    horizont2->addWidget(findNextButton);
    horizont2->addWidget(replaceButton);
    horizont2->addWidget(replaceAllButton);
    horizont2->addWidget(closeButton);

    QVBoxLayout *vertical = new QVBoxLayout();
    vertical->addLayout(horizont1);
    vertical->addLayout(horizont11);
    vertical->addLayout(horizont2);

    setLayout(vertical);
    index = 0;
}

void M4SCpFinder::enableFindButton(const QString &text)
{    
//    findPrevButton->setEnabled(!text.isEmpty());
    findNextButton->setEnabled(!text.isEmpty());
    replaceButton->setEnabled(!text.isEmpty());
    replaceAllButton->setEnabled(!text.isEmpty());

    findText();

}

void M4SCpFinder::findNext()
{
    QTextDocument *document = mEditor->document();
    QTextCursor newCursor(document);

    while (!newCursor.isNull() && !newCursor.atEnd())
    {
        newCursor = document->find(lineEditFind->text(), newCursor);
        if (newCursor.charFormat().background().color() == "#ffa500")
        {
            QTextCharFormat charFormat;
            charFormat.setBackground(QColor("yellow"));
            newCursor.setCharFormat(charFormat);

           int nextPos = 0;
            for(int i = 0; i < replaceIndexes.size() - 1; ++i)
            {
                if (replaceIndexes[i].first == newCursor )
                {
                    nextPos = ++i;
                    break;
                }
            }
            charFormat.setBackground(QColor("orange"));
            newCursor.setPosition(replaceIndexes[nextPos].second - lineEditFind->text().length(), QTextCursor::MoveAnchor);
            newCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, lineEditFind->text().length() );
            newCursor.setCharFormat(charFormat);
            index = nextPos;

            break;
        }
    }
}

void M4SCpFinder::findText()
{
    QTextDocument *document = mEditor->document();

    //снятие выделения с ранее найденного текста
    eraseBackground();

    // Выделение найденного текста
    QTextCursor newCursor(document);
    int i = 0;
    while (!newCursor.isNull() && !newCursor.atEnd())
    {
        newCursor = document->find(lineEditFind->text(), newCursor);
        i++;

        if ( !newCursor.isNull() )
        {           
            QTextCharFormat charFormat;
            if (i == 1) charFormat.setBackground(QColor("orange"));
            else charFormat.setBackground(QColor("yellow"));
            newCursor.setCharFormat(charFormat);

            pairIndexes.first = newCursor;
            pairIndexes.second = newCursor.position();
            replaceIndexes.push_back(pairIndexes);
        }
    }
}

void M4SCpFinder::eraseBackground()
{
     replaceIndexes.clear();

     QTextDocument * document = mEditor->document();
     QTextCursor newCursor(document);

     newCursor.setPosition( QTextCursor::Start - 1, QTextCursor::MoveAnchor );
     newCursor.movePosition( QTextCursor::End, QTextCursor::KeepAnchor );

     QTextCharFormat charFormat;
     charFormat.setBackground(QColor("white"));
     newCursor.setCharFormat(charFormat);
}

void M4SCpFinder::closeFindWindow()
{
     eraseBackground();
     close();
}

void M4SCpFinder::oneReplace()
{
    if (!replaceIndexes.isEmpty())
    {


    QTextDocument *document = mEditor->document();

    QString changeString = lineEditReplace->text();
    int ch = replaceIndexes[index].second - lineEditFind->text().length() ;
    document->setPlainText(document->toPlainText().replace(ch , lineEditFind->text().length() , changeString));

    findText();
    findNext();
    }
    else QMessageBox::warning(this, "Attention", "No search result");
}

void M4SCpFinder::replaceText()
{
     QTextDocument *document = mEditor->document();

     int  x = lineEditReplace->text().length() - lineEditFind->text().length();

     for(int i = 0; i < replaceIndexes.size(); ++i)
     {
         QString changeString = lineEditReplace->text();
         replaceIndexes[i].second += i * x - lineEditFind->text().length();
         document->setPlainText(document->toPlainText().replace(replaceIndexes[i].second , lineEditFind->text().length() , changeString));
     }

     replaceIndexes.clear();
}
//-------------------------------------------------------------------------------------
M4SCpFinder::~M4SCpFinder()
{

}


