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
    //! Type that represents text block begin and end positions
    typedef QPair<int, int> BlockRange;

    explicit SCsCodeAnalyzer(QObject *parent = 0);

    /*! Set the path of document for to analyze
      * @param path Path to document
      */
    void setDocumentPath(const QString &path);

    /*! Parse contents of specified sc.s-text and fills autocompleter's model
      * @param text String that contains sc.s-text
      * @param model Pointer to autocomplete item model
      */
    void parse(const QString &text, QStandardItemModel *model);

    /*! Update autocompleter's model according to changes in document made by user
      * @param text String that contains sc.s-text of edited document
      * @param model Pointer to autocomplete item model
      */
    void update(const QString &text, QStandardItemModel *model);

    /*! Force to ignore the addition of an \p identifier during the next update
      * (identifier wouldn't be added to autocomleter item model)
      * @param identifier String that contains identifier
      */
    void ignoreUpdate(const QString &identifier);

    /*! Check whether the specified position is within the "empty block" of document
      * (inside block of comments, for example)
      * @param positon Character position in document
      */
    bool isInEmptyBlock(int position);
    bool isInEmptyBlock(int pos, const QList<BlockRange> &blocks);

    /*! Add pattern for ignored blocks
      * @param blockPattern Block pattern
      */
    static void addIgnoreBlock(const BlockPattern &blockPattern);

    //! Intialize patterns for "ignore blocks".
    static void init();

    /*! Check whether the specified \p text is an SCs identifier.
      * @param text Text to check
      */
    static bool isIdentifier(const QString &text);

protected:
    /*! Parse contents of specified .scs file: extracts all identifiers, includes
      * and recursively processes them. If file has already been processed, then does nothing
      * @param filePath Absolute path to file
      */
    void parseFile(const QString &filePath);

    /*! Parse set of files. Paths to files can be absolute and relative.
      * @param pathSet Set of file paths
      * @param workDirectory Current directory (for relative paths).
      */
    void parseFiles(const QSet<QString> &pathSet, const QDir &workDirectory);

    /*! Process \p text and extract all blocks
      * @param text sc.s-text to process
      * @param emptyBlocks List of empty blocks
      * @param includes Set of included files
      * @param identifiers Set of identifiers
      */
    void processText(const QString &text, QList<BlockRange> *emptyBlocks, QSet<QString> *includes, QSet<QString> *identifiers);
    void extractEmptyBlocks(const QString &text, QList<BlockRange> *emptyBlocks);
    void extractIdentifiers(const QString &text, QSet<QString> *identifiers, const QList<BlockRange> &emptyBlocks);
    void extractIncludes(const QString &text, QSet<QString> *includes, const QList<BlockRange> &emptyBlocks);

    //! Clear FileSystemWatcher list
    void clearWatcher();

    /*! Fills autocomplete items model with identifiers extracted from current document and its includes.
      * @param model Pointer to autocomplete item model
      */
    void fillModel(QStandardItemModel *model);

private:
    const static QRegExp msIdentifierExp;
    const static QRegExp msIncludeExp;
    static QList<BlockPattern> msIgnoreBlockPatterns;

    QSet<QString> mDocumentIncludes;
    QSet<QString> mDocumentIdentifiers;

    QSet<QString> mParsedFiles;
    QSet<QString> mIncludedIdentifiers;
    QSet<QString> mIgnoreIdentifiers;

    QList<BlockRange> mDocumentEmptyBlocks;
    QString mDocumentPath;
    QDir mDocumentDir;

    bool mIncludesUpdated;
    QFileSystemWatcher *mWatcher;

private slots:
    /*! Called when some of the included files of current document
        is modified.
      */
    void updateFile(const QString &file);

};

#endif // SCSCODEANALYZER_H
