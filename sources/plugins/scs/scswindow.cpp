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

#include "scswindow.h"
#include "scshighlightingrulespool.h"
#include "scscodeeditor.h"
#include "scssyntaxhighlighter.h"
#include "scsfindwidget.h"
#include "scserrortablewidget.h"


#include <QHBoxLayout>
#include <QIcon>
#include <QUndoStack>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QShortcut>
#include <QTextCodec>

SCsWindow::SCsWindow(const QString& _windowTitle, QWidget *parent):
    QWidget(parent),
    mEditor(0),
    mHighlighter(0),
    mIsSaved(false),
    mErrorTable(0)
{


    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    mErrorTable = new SCsErrorTableWidget(this);

    mEditor = new SCsCodeEditor(this,mErrorTable);
    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    mFindWidget = new SCsFindWidget(this);
    connect(mFindWidget, SIGNAL(findNext()), this, SLOT(findNext()));
    connect(mFindWidget, SIGNAL(findPrevious()), this, SLOT(findPrevious()));
    connect(mFindWidget, SIGNAL(find(QString)), this, SLOT(findTextChanged(QString)));

    mHighlighter = new SCsSyntaxHighlighter(mEditor->document(), SCsHighlightingRulesPool::getInstance()->rules());



    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(mEditor);
    if( mErrorTable != NULL )
        layout->addWidget(mErrorTable);
    layout->addWidget(mFindWidget);

    layout->setStretch(0,5);
    layout->setStretch(1,2);
    layout->setStretch(2,2);
    setLayout(layout);

    QShortcut *shortcut = new QShortcut(QKeySequence::Find,this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(showTextSearch()));
    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(onEscapePressed()));


    connect(mEditor, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

SCsWindow::~SCsWindow()
{
    delete mHighlighter;
    delete mEditor;
}

QWidget* SCsWindow::widget()
{
    return this;
}

QToolBar* SCsWindow::toolBar()
{
    return 0;
}

QList<QWidget*> SCsWindow::widgetsForDocks()
{
    return QList<QWidget*>();
}

QStringList SCsWindow::supportedFormatsExt() const
{
    QStringList res;
    res << "scs";
    return res;
}

bool SCsWindow::loadFromFile(const QString &fileName)
{
    // read data from file
    QFile fileIn(fileName);

    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, tr("Error"),
                             tr("Can't open file %1:\n%2.")
                             .arg(fileName)
                             .arg(fileIn.errorString()));
        return false;
    }

    QTextStream in(&fileIn);
    mEditor->document()->setPlainText(in.readAll());
    mEditor->setDocumentPath(fileName);
    fileIn.close();

    mFileName = fileName;
    setWindowTitle(mFileName + "[*]");
    mIsSaved = true;

    emitEvent(EditorObserverInterface::ContentLoaded);

    return true;
}

bool SCsWindow::saveToFile(const QString &fileName)
{
    QFile fileOut(fileName);
    if (!fileOut.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(0, tr("error"),
                             tr("Can't save file %1:\n%2.")
                             .arg(fileName)
                             .arg(fileOut.errorString()));
        return false;
    }
    QTextStream out(&fileOut);
    out << mEditor->document()->toPlainText();
    fileOut.close();

    mFileName = fileName;
    setWindowTitle(mFileName + "[*]");
    mIsSaved = true;

    emitEvent(EditorObserverInterface::ContentSaved);

    return true;
}

bool SCsWindow::isSaved() const
{
    return mIsSaved;
}

void SCsWindow::_update()
{

}

QIcon SCsWindow::icon() const
{
    return findIcon("mime_type.png");
}

QIcon SCsWindow::findIcon(const QString &iconName)
{
    return QIcon(":/scs/media/icons/" + iconName);
}

void SCsWindow::textChanged()
{
    mIsSaved = false;
    emitEvent(EditorObserverInterface::ContentChanged);
}


void SCsWindow::findNext()
{
    mEditor->find(mFindWidget->text(), mFindWidget->getFlags());
}

void SCsWindow::findPrevious()
{
    mEditor->find(mFindWidget->text(), mFindWidget->getFlags() | QTextDocument::FindBackward);
}

void SCsWindow::findTextChanged(const QString &ttf)
{
    QTextCursor cursor = mEditor->document()->find(ttf, 0, mFindWidget->getFlags());
    if(!cursor.isNull())
        mEditor->setTextCursor(cursor);
}

void SCsWindow::showTextSearch()
{
    mFindWidget->show(mEditor->textCursor().selectedText());
}


void SCsWindow::onEscapePressed()
{
    if(mFindWidget->isVisible())
    {
        mFindWidget->hide();
    }
    else
        if( mErrorTable != NULL )
            if(mErrorTable->isVisible())
                mErrorTable->hide();
    mEditor->setFocus();
}


// ---------------------
SCsWindowFactory::SCsWindowFactory(QObject *parent) :
    QObject(parent)
{
}

SCsWindowFactory::~SCsWindowFactory()
{
}

const QString& SCsWindowFactory::name() const
{
    static QString name = "scs";
    return name;
}

EditorInterface* SCsWindowFactory::createInstance()
{
    return new SCsWindow("");
}

QStringList SCsWindowFactory::supportedFormatsExt()
{
    QStringList list;
    list << "scs";

    return list;
}

QIcon SCsWindowFactory::icon() const
{
    return SCsWindow::findIcon("mime_type.png");
}
