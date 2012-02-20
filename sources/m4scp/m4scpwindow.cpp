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
#include "../abstractfileloader.h"
#include "../abstractfilewriter.h"
#include "../config.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QUndoStack>
#include <QDir>
#include <QFileInfo>



M4SCpWindow::M4SCpWindow(const QString& _windowTitle, QWidget *parent):
    BaseWindow("SCpWindow", _windowTitle, parent),
    editor(0),
    highlighter(0)
{
    editor = new M4SCpCodeEditor();
    QFont font;
    font.setStyleHint(QFont::Serif);
    font.setPointSize(11);
    editor->setFont(font);
    editor->setPalette(QPalette(QPalette::Background, Qt::white));
    highlighter = new M4SCpSyntaxHighlighter(editor->document());
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(editor);
    setLayout(layout);
}

M4SCpWindow::~M4SCpWindow(){
    delete highlighter;
    delete editor;
}

bool M4SCpWindow::isSaved() const
{
    return true;
}

void M4SCpWindow::createToolBar()
{

}


bool M4SCpWindow::loadFromFile(const QString &fileName, AbstractFileLoader *loader)
{
    if (loader->load(fileName, editor->document()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        return true;
    }
    return false;
}


bool M4SCpWindow::saveToFile(const QString &fileName, AbstractFileWriter *writer)
{
    if (writer->save(fileName, editor->document()))
    {
        if(writer->type() == AbstractFileWriter::WT_Save)
        {
            mFileName = fileName;
            setWindowTitle(mFileName + "[*]");
            mUndoStack->setClean();
        }
        return true;
    }else
        return false;
}

void M4SCpWindow::_update()
{

}

QIcon M4SCpWindow::icon() const
{
    return findIcon("mime_type.png");
}

QIcon M4SCpWindow::findIcon(const QString &iconName) const
{
    QDir dir(Config::pathMedia);
    dir.cd("scg/icons");
    return QIcon(QFileInfo(dir, iconName).absoluteFilePath());
}
