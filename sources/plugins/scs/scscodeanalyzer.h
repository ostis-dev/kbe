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





#endif // SCSCODEANALYZER_H
