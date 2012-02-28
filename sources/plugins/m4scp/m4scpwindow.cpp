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
    mEditor(0),
    mHighlighter(0)
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
}

M4SCpWindow::~M4SCpWindow()
{
    delete mHighlighter;
    delete mEditor;
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
    if (loader->load(fileName, mEditor->document()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        return true;
    }
    return false;
}


bool M4SCpWindow::saveToFile(const QString &fileName, AbstractFileWriter *writer)
{
    if (writer->save(fileName, mEditor->document()))
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
