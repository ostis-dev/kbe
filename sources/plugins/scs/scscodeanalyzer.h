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

    /*! Sets the path of the opened file.
      @param path Absolute path to the file.
      */
    void setDocumentPath(const QString &path);

    /*! Parses contents of opened file and fills autocompleter's model.
      @param text Text of document.
      @param model Item model for autocompletion.
      */
    void parse(const QString &text, QStandardItemModel *model);

    /*! Updates autocompleter's model according to changes in document made by user.
      @param text Text of document.
      @param model Item model for autocompletion.
      */
    void update(const QString &text, QStandardItemModel *model);

    /*! Forces to ignore the addition of an identifier during the next update().
        identifier won't be added to autocomleter's model.
      @param identifier Identifier to ignore.
      */
    void ignoreUpdate(const QString &identifier);

    /*! Checks whether the specified position is within the "empty block" of document
       (inside block of comments, for example).
      @param pos Position in document.
      */

    bool inEmptyBlock(int pos);

    /*! Adds pattern for "empty blocks".
      @param blockPattern Block pattern.
      */
    static void addIgnoreBlock(const BlockPattern &blockPattern);

    /*! Intializes patterns for "empty blocks".
      */
    static void init();

    /*! Checks whether the specified text is an SCs identifier.
      @param text Text to check.
      */
    static bool isIdentifier(const QString &text);

protected:
    typedef QPair<int, int> Block;

    /*! Parses contents of specified .scs file:
        extracts all identifiers, includes and recursively processes them.
        If file has already been seen, does nothing.
      @param filePath Absolute path to file.
      */
    void parseFile(const QString &filePath);

    /*! Parses set of files. Paths to files can be absolute and relative.
      @param pathSet Set of paths to files.
      @param workDirectory Current directory (for relative paths).
      */
    void parseFiles(const QSet<QString> &pathSet, const QDir &workDirectory);

    /*! Extracts "empty blocks", includes, identifiers from text.
      @param text Contents of document.
      @param emptyBlocks List of empty blocks.
      @param includes Set of include files.
      @param identifiers Set of identifiers.
      */
    void processText(const QString &text, QList<Block> *emptyBlocks, QSet<QString> *includes, QSet<QString> *identifiers);
    void extractEmptyBlocks(const QString &text, QList<Block> *emptyBlocks);
    void extractIdentifiers(const QString &text, QSet<QString> *identifiers, const QList<Block> &emptyBlocks);
    void extractIncludes(const QString &text, QSet<QString> *includes, const QList<Block> &emptyBlocks);

    /*! Clears FileSystemWatcher list of files.
      */
    void clearWatcher();

    /*! Fills autocompleter's model with identifiers extracted from current document
        and its includes.
        @param model Item model for autocompletion.
      */
    void fillModel(QStandardItemModel *model);

    bool inEmptyBlock(int pos, const QList<Block> &blocks);

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
    /*! Called when some of the included files of current document
        is modified.
      */
    void updateFile(const QString &file);

};

#endif // SCSCODEANALYZER_H
