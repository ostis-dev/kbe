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

#ifndef SCSCODEANALYZER_H
#define SCSCODEANALYZER_H

#include <QObject>
#include <QStringList>
#include <QRegExp>
#include <QDir>
#include <QList>
#include <QPair>
#include <QSet>
#include <QMap>

class QStandardItemModel;
class QFileSystemWatcher;

class SCsCodeAnalyzer : public QObject
{
    Q_OBJECT    

public:    
    typedef QPair<QRegExp, QRegExp> BlockPattern;

    explicit SCsCodeAnalyzer(QObject *parent = 0);
    void setDocumentPath(const QString &path);

    void parse(const QString &text, QStandardItemModel *model);
    void update(const QString &text, QStandardItemModel *model);
    void ignoreUpdate(const QString &identifier);

    bool inEmptyBlock(int pos);

    static void addIgnoreBlock(const BlockPattern &blockPattern);
    static void init();
    static bool isIdentifier(const QString &text);

protected:
    typedef QPair<int, int> Block;

    void parseFile(const QString &filePath);

    void extractIdentifiers(const QString &text, QSet<QString> *identifiers, QList<Block> *emptyBlocks = NULL);
    void extractIncludes(const QString &text, QSet<QString> *identifiers);
    void clearWatcher();

private:
    const static QRegExp msIdentifierExp;
    const static QRegExp msIncludeExp;
    static QList<BlockPattern> msIgnoreBlockPatterns;

    QSet<QString> mDocumentIncludes;
    QSet<QString> mDocumentIdentifiers;

    QSet<QString> mParsedFiles;
    QSet<QString> mIncludedIdentifiers;
    QSet<QString> mIgnoreIdentifiers;

    QList<Block> mDocumentEmptyBlocks;
    QString mDocumentPath;
    QDir mDocumentDir;

    bool mIncludesUpdated;
    QFileSystemWatcher *mWatcher;

private slots:
    void updateFile(const QString &file);

};

#endif // SCSCODEANALYZER_H
