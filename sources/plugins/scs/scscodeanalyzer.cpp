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

const QRegExp SCsCodeAnalyzer::msIdentifierExp("([$]?[A-Za-z0-9_]+)");
const QRegExp SCsCodeAnalyzer::msIncludeExp("#include\\s+\"([^\"]+)\"");
QList<SCsCodeAnalyzer::BlockPattern> SCsCodeAnalyzer::msIgnoreBlockPatterns;

SCsCodeAnalyzer::SCsCodeAnalyzer(QObject *parent) :
    QObject(parent),
    mIncludesUpdated(false)
{
    mWatcher = new QFileSystemWatcher(this);
    connect(mWatcher, SIGNAL(fileChanged(QString)), this, SLOT(updateFile(QString)));

    SCsCodeAnalyzer::init();
}

void SCsCodeAnalyzer::parseFiles(const QSet<QString> &pathSet, const QDir &workDirectory)
{
    foreach(const QString &fileName, pathSet)
    {
        QFileInfo fileInfo(fileName);
        if (fileInfo.isAbsolute())
        {
            parseFile(fileName);
        }
        else
        {
            fileInfo.setFile(workDirectory, fileName);
            parseFile(fileInfo.absoluteFilePath());
        }
    }
}

void SCsCodeAnalyzer::fillModel(QStandardItemModel *model)
{
    model->clear();

    QSet<QString> identifiers = mDocumentIdentifiers + mIncludedIdentifiers;

    foreach(const QString &id, identifiers)
    {
        QStandardItem *item = new QStandardItem(id);
        model->appendRow(item);
    }
}

void SCsCodeAnalyzer::parseFile(const QString &filePath)
{
    if (mParsedFiles.contains(filePath))
        return;

    QFile file(filePath);

    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        mWatcher->addPath(filePath);
        mParsedFiles << filePath;

        QTextStream in(&file);
        QString text = in.readAll();

        QDir fileDirectory = QFileInfo(file).absoluteDir();
        file.close();

        QSet<QString> files;
        QSet<QString> identifiers;
        QList<BlockRange> emptyBlocks;

        processText(text, &emptyBlocks, &files, &identifiers);

        mIncludedIdentifiers += identifiers;

        parseFiles(files, fileDirectory);
    }
}

void SCsCodeAnalyzer::processText(const QString &text, QList<BlockRange> *emptyBlocks, QSet<QString> *includes, QSet<QString> *identifiers)
{
    extractEmptyBlocks(text, emptyBlocks);
    extractIncludes(text, includes, *emptyBlocks);
    extractIdentifiers(text, identifiers, *emptyBlocks);
}

void SCsCodeAnalyzer::extractEmptyBlocks(const QString &text, QList<BlockRange> *emptyBlocks)
{
    int pos = 0;
    while (pos != -1)
    {
        int startPos = std::numeric_limits<int>::max();
        int endPos = -1;
        const QRegExp *startExp;
        const QRegExp *endExp = NULL;

        foreach(const BlockPattern &range, msIgnoreBlockPatterns)
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
                *emptyBlocks << BlockRange(startPos, text.length());
                pos = -1;
            }
            else
            {
                *emptyBlocks << BlockRange(startPos, endPos + endExp->matchedLength());
                pos = endPos + endExp->matchedLength();
            }
        }
        else pos = -1;

    }
}

void SCsCodeAnalyzer::extractIdentifiers(const QString &text, QSet<QString> *identifiers, const QList<BlockRange> &emptyBlocks)
{
    int pos = 0;
    while ( (pos = msIdentifierExp.indexIn(text, pos)) != -1)
    {
        if (!isInEmptyBlock(pos, emptyBlocks))
        {
            *identifiers << msIdentifierExp.cap(1);
        }

        pos += msIdentifierExp.matchedLength();
    }
}

void SCsCodeAnalyzer::extractIncludes(const QString &text, QSet<QString> *includes, const QList<BlockRange> &emptyBlocks)
{
    int pos = 0;
    while ( (pos = msIncludeExp.indexIn(text, pos)) != -1 )
    {
        if (!isInEmptyBlock(pos, emptyBlocks))
        {
            *includes << msIncludeExp.cap(1);
        }

        pos += msIncludeExp.matchedLength();
    }
}

void SCsCodeAnalyzer::parse(const QString &text, QStandardItemModel *model)
{
    clearWatcher();
    mDocumentIncludes.clear();
    mDocumentEmptyBlocks.clear();
    mDocumentIdentifiers.clear();

    mParsedFiles.clear();
    mIncludedIdentifiers.clear();

    mParsedFiles << mDocumentPath;

    processText(text, &mDocumentEmptyBlocks, &mDocumentIncludes, &mDocumentIdentifiers);
    parseFiles(mDocumentIncludes, mDocumentDir);

    fillModel(model);
}

void SCsCodeAnalyzer::update(const QString &text, QStandardItemModel *model)
{
    QSet<QString> newIdentifiers;
    QSet<QString> newIncludes;

    processText(text, &mDocumentEmptyBlocks, &newIncludes, &newIdentifiers);

    newIdentifiers -= mIgnoreIdentifiers - mDocumentIdentifiers;

    bool includesChanged = newIncludes != mDocumentIncludes;

    if (mIncludesUpdated || includesChanged)
    {
        clearWatcher();

        mDocumentIdentifiers = newIdentifiers;
        mDocumentIncludes = newIncludes;

        mParsedFiles.clear();
        mIncludedIdentifiers.clear();

        mParsedFiles << mDocumentPath;

        parseFiles(mDocumentIncludes, mDocumentDir);

        fillModel(model);

        mIncludesUpdated = false;

    }
    else
    {

        QSet<QString> identifiersToAdd = newIdentifiers - mDocumentIdentifiers;

        foreach(const QString &id, identifiersToAdd)
            if (!mIncludedIdentifiers.contains(id))
            {
                QStandardItem *item = new QStandardItem(id);
                model->appendRow(item);
            }

        QSet<QString> identifiersToRemove = mDocumentIdentifiers - newIdentifiers;

        foreach(const QString &id, identifiersToRemove)
            if (!mIncludedIdentifiers.contains(id))
            {
                QList<QStandardItem*> items = model->findItems(id);
                foreach(QStandardItem* item, items)
                {
                    delete model->takeItem(item->row());
                }
            }

        mDocumentIdentifiers = newIdentifiers;
        mDocumentIncludes = newIncludes;
    }

    mIgnoreIdentifiers.clear();
}

void SCsCodeAnalyzer::ignoreUpdate(const QString &identifier)
{
    if (SCsCodeAnalyzer::isIdentifier(identifier))
    {
        mIgnoreIdentifiers << identifier;
    }
}

void SCsCodeAnalyzer::setDocumentPath(const QString &path)
{
    mDocumentPath = path;
    mDocumentDir = QFileInfo(path).absoluteDir();
}

bool SCsCodeAnalyzer::isInEmptyBlock(int pos, const QList<BlockRange> &blocks)
{
    foreach(const BlockRange &block, blocks)
        if (block.first < pos && block.second >= pos)
            return true;

    return false;
}

bool SCsCodeAnalyzer::isInEmptyBlock(int pos)
{
    return isInEmptyBlock(pos, mDocumentEmptyBlocks);
}


void SCsCodeAnalyzer::addIgnoreBlock(const BlockPattern &blockPattern)
{
    SCsCodeAnalyzer::msIgnoreBlockPatterns.append(blockPattern);
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
    return SCsCodeAnalyzer::msIdentifierExp.exactMatch(text);
}

void SCsCodeAnalyzer::clearWatcher()
{
    if (!mParsedFiles.empty())
    {
        mWatcher->removePaths(mParsedFiles.toList());
    }
}

void SCsCodeAnalyzer::updateFile(const QString &file)
{
    Q_UNUSED(file)

    mIncludesUpdated = true;
}
