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

#include "scscodeanalyzer.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QStandardItemModel>
#include <QFileSystemWatcher>
#include <limits>

const QRegExp SCsCodeAnalyzer::identifierExp("([$]?[A-Za-z0-9_]+)");
const QRegExp SCsCodeAnalyzer::includeExp("#include \"([^\"]+)\"");
QList<SCsCodeAnalyzer::BlockPattern> SCsCodeAnalyzer::ignoreBlockPatterns;

SCsCodeAnalyzer::SCsCodeAnalyzer(QObject *parent) :
    QObject(parent),
    includesUpdated(false)
{
    mWatcher = new QFileSystemWatcher(this);
    connect(mWatcher, SIGNAL(fileChanged(QString)), this, SLOT(updateFile(QString)));

    SCsCodeAnalyzer::init();
}

void SCsCodeAnalyzer::parseFile(const QString &filePath)
{
    if (parsedFiles.contains(filePath))
        return;

    QFile file(filePath);

    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        mWatcher->addPath(filePath);
        parsedFiles << filePath;

        QTextStream in(&file);
        QString text = in.readAll();

        QDir fileDirectory = QFileInfo(file).absoluteDir();
        file.close();

        QSet<QString> files;
        QSet<QString> identifiers;

        extractIncludes(text, &files);
        extractIdentifiers(text, &identifiers);

        includedIdentifiers += identifiers;

        foreach(const QString &fileName, files)
        {
            QFileInfo fileInfo(fileName);
            if (fileInfo.isAbsolute())
            {
                parseFile(fileName);
            }
            else
            {
                fileInfo.setFile(fileDirectory, fileName);
                parseFile(fileInfo.absoluteFilePath());
            }
        }
    }
}

void SCsCodeAnalyzer::extractIdentifiers(const QString &text, QSet<QString> *identifiers, QList<Block> *emptyBlocks)
{
    QList<Block> ignoreBlocksPos;

    int pos = 0;
    while (pos != -1)
    {
        int startPos = std::numeric_limits<int>::max();
        int endPos = -1;
        const QRegExp *startExp;
        const QRegExp *endExp = NULL;

        foreach(const BlockPattern &range, ignoreBlockPatterns)
        {

            int currentPos = range.first.indexIn(text, pos);

            if (currentPos != -1 && currentPos < startPos)
            {                
                startExp = &range.first;
                endExp = &range.second;

                startPos = currentPos;
            }
        }

        if (endExp)
        {
            endPos = endExp->indexIn(text, startPos + startExp->matchedLength());

            if (endPos == -1)
            {                
                ignoreBlocksPos << Block(startPos, text.length());
                pos = -1;
            }
            else
            {
                ignoreBlocksPos << Block(startPos, endPos + endExp->matchedLength());
                pos = endPos + endExp->matchedLength();
            }
        }
        else pos = -1;

    }

    pos = 0;
    while ( (pos = identifierExp.indexIn(text, pos)) != -1)
    {
        bool include = true;
        foreach(const Block &block, ignoreBlocksPos)
            if (block.first <= pos && block.second >= pos)
            {
                include = false;
                break;
            }

        if (include)
        {
            *identifiers << identifierExp.cap(1);
            //qDebug() << identifierExp.cap(1);
        }

        pos += identifierExp.matchedLength();
    }

    if (emptyBlocks)
    {
        *emptyBlocks = ignoreBlocksPos;
    }
}

void SCsCodeAnalyzer::extractIncludes(const QString &text, QSet<QString> *includes)
{
    int pos = 0;
    while ( (pos = includeExp.indexIn(text, pos)) != -1 )
    {
        *includes << includeExp.cap(1);
        ++pos;
    }
}

void SCsCodeAnalyzer::parse(const QString &text, QStandardItemModel *model)
{
    model->clear();
    clearWatcher();
    documentIncludes.clear();
    documentEmptyBlocks.clear();
    documentIdentifiers.clear();

    parsedFiles.clear();
    includedIdentifiers.clear();

    parsedFiles << documentPath;

    extractIncludes(text, &documentIncludes);
    extractIdentifiers(text, &documentIdentifiers, &documentEmptyBlocks);

    foreach(const QString &fileName, documentIncludes)
    {
        QFileInfo fileInfo(fileName);
        if (fileInfo.isAbsolute())
        {
            parseFile(fileName);
        }
        else
        {
            fileInfo.setFile(documentDir, fileName);
            parseFile(fileInfo.absoluteFilePath());
        }
    }

    QSet<QString> identifiers = documentIdentifiers + includedIdentifiers;

    foreach(const QString &id, identifiers)
    {
        QStandardItem *item = new QStandardItem(id);
        model->appendRow(item);
    }
}

void SCsCodeAnalyzer::update(const QString &text, QStandardItemModel *model)
{
    QSet<QString> newIdentifiers;
    QSet<QString> newIncludes;

    extractIncludes(text, &newIncludes);
    extractIdentifiers(text, &newIdentifiers, &documentEmptyBlocks);

    newIdentifiers -= ignoreIdentifiers - documentIdentifiers;

    bool includesChanged = newIncludes != documentIncludes;

    if (includesUpdated || includesChanged)
    {
        model->clear();
        clearWatcher();

        documentIdentifiers = newIdentifiers;
        documentIncludes = newIncludes;

        parsedFiles.clear();
        includedIdentifiers.clear();

        parsedFiles << documentPath;

        foreach(const QString &fileName, documentIncludes)
        {
            QFileInfo fileInfo(fileName);
            if (fileInfo.isAbsolute())
            {
                parseFile(fileName);
            }
            else
            {
                fileInfo.setFile(documentDir, fileName);
                parseFile(fileInfo.absoluteFilePath());
            }
        }

        QSet<QString> identifiers = documentIdentifiers + includedIdentifiers;

        foreach(const QString &id, identifiers)
        {
            QStandardItem *item = new QStandardItem(id);
            model->appendRow(item);
        }

        includesUpdated = false;

    }
    else
    {

        QSet<QString> identifiersToAdd = newIdentifiers - documentIdentifiers;

        foreach(const QString &id, identifiersToAdd)
            if (!includedIdentifiers.contains(id))
            {
                QStandardItem *item = new QStandardItem(id);
                model->appendRow(item);
            }

        QSet<QString> identifiersToRemove = documentIdentifiers - newIdentifiers;

        foreach(const QString &id, identifiersToRemove)
            if (!includedIdentifiers.contains(id))
            {
                QList<QStandardItem*> items = model->findItems(id);
                foreach(QStandardItem* item, items)
                {
                    delete model->takeItem(item->row());
                }
            }

        documentIdentifiers = newIdentifiers;
        documentIncludes = newIncludes;
    }

    ignoreIdentifiers.clear();
}

void SCsCodeAnalyzer::ignoreUpdate(const QString &identifier)
{
    if (SCsCodeAnalyzer::isIdentifier(identifier))
    {
        ignoreIdentifiers << identifier;
    }
}

void SCsCodeAnalyzer::setDocumentPath(const QString &path)
{
    documentPath = path;
    documentDir = QFileInfo(path).absoluteDir();
}

bool SCsCodeAnalyzer::inEmptyBlock(int pos)
{
    foreach(const Block &block, documentEmptyBlocks)
        if (block.first < pos && block.second >= pos)
            return true;

    return false;
}


void SCsCodeAnalyzer::addIgnoreBlock(const BlockPattern &blockPattern)
{
    SCsCodeAnalyzer::ignoreBlockPatterns.append(blockPattern);
}

void SCsCodeAnalyzer::init()
{
    static bool initialized = false;

    if (!initialized)
    {
        SCsCodeAnalyzer::addIgnoreBlock(SCsCodeAnalyzer::BlockPattern(QRegExp("/\""), QRegExp("\"/")));
        SCsCodeAnalyzer::addIgnoreBlock(SCsCodeAnalyzer::BlockPattern(QRegExp("\""), QRegExp("\"")));
        SCsCodeAnalyzer::addIgnoreBlock(SCsCodeAnalyzer::BlockPattern(QRegExp("/\\*"), QRegExp("\\*/")));
        SCsCodeAnalyzer::addIgnoreBlock(SCsCodeAnalyzer::BlockPattern(QRegExp("//"), QRegExp("\\n")));
        SCsCodeAnalyzer::addIgnoreBlock(SCsCodeAnalyzer::BlockPattern(QRegExp("#include"), QRegExp(".")));

        initialized = true;
    }
}

bool SCsCodeAnalyzer::isIdentifier(const QString &text)
{
    return SCsCodeAnalyzer::identifierExp.exactMatch(text);
}

void SCsCodeAnalyzer::clearWatcher()
{
    if (!parsedFiles.empty())
    {
        mWatcher->removePaths(parsedFiles.toList());
    }
}

void SCsCodeAnalyzer::updateFile(const QString &file)
{
    Q_UNUSED(file)

    includesUpdated = true;
}
