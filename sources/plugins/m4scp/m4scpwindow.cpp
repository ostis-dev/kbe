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

#include "m4scpwindow.h"
#include "m4scpcodeeditor.h"
#include "m4scpsyntaxhighlighter.h"
#include "m4scpplugin.h"

#include "m4scpfileloader.h"
#include "m4scpfilewriter.h"

#include "config.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QUndoStack>
#include <QDir>
#include <QFileInfo>


M4SCpWindow::M4SCpWindow(const QString& _windowTitle, QWidget *parent):
    QWidget(parent),
    mEditor(0),
    mHighlighter(0),
    mIsSaved(false)
{
    mEditor = new M4SCpCodeEditor();
    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    mHighlighter = new M4SCpSyntaxHighlighter(mEditor->document());
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(mEditor);
    setLayout(layout);

    connect(mEditor, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

M4SCpWindow::~M4SCpWindow()
{
    delete mHighlighter;
    delete mEditor;
}

QWidget* M4SCpWindow::widget()
{
    return this;
}

QToolBar* M4SCpWindow::toolBar()
{
    return 0;
}

QList<QWidget*> M4SCpWindow::widgetsForDocks()
{
    return QList<QWidget*>();
}

QStringList M4SCpWindow::supportedFormatsExt() const
{
    QStringList res;
    res << "m4scp";
    return res;
}

bool M4SCpWindow::loadFromFile(const QString &fileName)
{    
    M4SCpFileLoader loader;

    if (loader.load(fileName, mEditor->document()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        mIsSaved = true;

        emitEvent(EditorObserverInterface::ContentLoaded);

        return true;
    }

    return false;
}


bool M4SCpWindow::saveToFile(const QString &fileName)
{
    M4SCpFileWriter writer;

    if (writer.save(fileName, mEditor->document()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        mIsSaved = true;

        emitEvent(EditorObserverInterface::ContentSaved);

        return true;
    }else
        return false;
}

bool M4SCpWindow::isSaved() const
{
    return mIsSaved;
}

void M4SCpWindow::_update()
{

}

QIcon M4SCpWindow::icon() const
{
    return findIcon("mime_type.png");
}

QIcon M4SCpWindow::findIcon(const QString &iconName)
{
    return QIcon(":/media/icons/" + iconName);
}

void M4SCpWindow::textChanged()
{
    mIsSaved = false;
    emitEvent(EditorObserverInterface::ContentChanged);
}


// ---------------
M4SCpWindowFactory::M4SCpWindowFactory(QObject *parent) :
    QObject(parent)
{

}

M4SCpWindowFactory::~M4SCpWindowFactory()
{

}

const QString& M4SCpWindowFactory::name() const
{
    static QString name = "m4scp";
    return name;
}

EditorInterface* M4SCpWindowFactory::createInstance()
{
    return new M4SCpWindow("");
}

QStringList M4SCpWindowFactory::supportedFormatsExt()
{
    QStringList list;
    list << "m4scp";

    return list;
}
