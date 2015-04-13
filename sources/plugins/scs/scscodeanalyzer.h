/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QStringList>
#include <QRegExp>
#include <QDir>
#include <QList>
#include <QPair>
#include <QSet>
#include <QMap>

class QStandardItemModel;
class SCsParseExtractIdftAsynchTask;
class SCsAsynchParser;


class SCsCodeAnalyzer : public QObject
{
    Q_OBJECT    

public:    

	explicit SCsCodeAnalyzer(QObject *parent = 0);

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

	void asynchUpdate(const QString &text, QStandardItemModel *model);

    /*! Force to ignore the addition of an \p identifier during the next update
      * (identifier wouldn't be added to autocomleter item model)
      * @param identifier String that contains identifier
      */
    void ignoreUpdate(const QString &identifier);

	/*! Check whether the specified \p text is an SCs identifier.
      * @param text Text to check
      */
    static bool isIdentifier(const QString &text);

protected:
    void fillModel(QStandardItemModel *model, const QSet<QString> &idtfs);
	void extractIdentifiers(const QString &text, QSet<QString> &identifiers);

private slots:
	void asynchUpdateExtractIdftFinished();

private:
	const static QRegExp msIdentifierExp;
    QSet<QString> mDocumentIdentifiers;
    QSet<QString> mIgnoreIdentifiers;
	QStandardItemModel* mUpdateModel;
    SCsAsynchParser* mAsynchParser;
    bool mIsBusy;
};

