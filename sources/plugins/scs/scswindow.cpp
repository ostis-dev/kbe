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
#include "config.h"
#include "scsfileloader.h"
#include "scsfilewriter.h"
#include "scshighlightingrulespool.h"
#include "scscodeeditor.h"
#include "scssyntaxhighlighter.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QUndoStack>
#include <QDir>
#include <QFileInfo>

SCsWindow::SCsWindow(const QString& _windowTitle, QWidget *parent):
    QWidget(parent),
    mEditor(0),
    mHighlighter(0),
    mIsSaved(false)
{
    mEditor = new SCsCodeEditor();
    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    mHighlighter = new SCsSyntaxHighlighter(mEditor->document(), SCsHighlightingRulesPool::getInstance()->rules());
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->mEditor);
    setLayout(layout);
}

SCsWindow::~SCsWindow()
{
    delete this->mHighlighter;
    delete this->mEditor;
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
    res << "m4scp";
    return res;
}

bool SCsWindow::loadFromFile(const QString &fileName)
{
    SCsFileLoader loader;

    if(loader.load(fileName, mEditor->document()))
    {
        this->mFileName = fileName;
        this->setWindowTitle(this->mFileName + "[*]");
        this->mIsSaved = true;
        return true;
    }

    return false;
}

bool SCsWindow::saveToFile(const QString &fileName)
{
    SCsFileWriter writer;

    if (writer.save(fileName, mEditor->document()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        mIsSaved = true;
        return true;
    }
    else
        return false;
}

bool SCsWindow::isSaved() const
{
    return this->mIsSaved;
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
    return QIcon(":/media/icons/" + iconName);
}

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
