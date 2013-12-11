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
#include "scsparserwrapper.h"
#include "scsasynchparser.h"

#include <QStandardItemModel>

const QRegExp SCsCodeAnalyzer::msIdentifierExp("([A-Za-z0-9_.#]+)");


SCsCodeAnalyzer::SCsCodeAnalyzer(QObject *parent) :
	  QObject(parent)
	, mUpdateModel(0)
    , mAsynchParser(0)
    , mIsBusy(false)
{
    mAsynchParser = new SCsAsynchParser(this);
    connect(mAsynchParser,SIGNAL(parseIdentifiersFinished()),SLOT(asynchUpdateExtractIdftFinished()));
}


void SCsCodeAnalyzer::fillModel(QStandardItemModel *model, const QSet<QString> &idtfs)
{
	Q_CHECK_PTR(model);

	if (!model)
		return;

	model->clear();

	foreach (const QString &id, idtfs)
	{
		QStandardItem *item = new QStandardItem(id);
		model->appendRow(item);
	}
}

void SCsCodeAnalyzer::ignoreUpdate(const QString &identifier)
{
	if (SCsCodeAnalyzer::isIdentifier(identifier))
	{
		mIgnoreIdentifiers << identifier;
	}
}


bool SCsCodeAnalyzer::isIdentifier(const QString &text)
{
	return SCsCodeAnalyzer::msIdentifierExp.exactMatch(text);
}




void SCsCodeAnalyzer::update(const QString &text, QStandardItemModel *model)
{
    if (mIsBusy)
		return;

	extractIdentifiers(text, mDocumentIdentifiers);

	mDocumentIdentifiers -= mIgnoreIdentifiers;

	fillModel(model, mDocumentIdentifiers);

	mIgnoreIdentifiers.clear();
}


void SCsCodeAnalyzer::asynchUpdate(const QString &text, QStandardItemModel *model)
{
	if (mIsBusy)
		return;

	if (text.isEmpty())
		return;

	mIsBusy = true;

	mUpdateModel = model;

    mAsynchParser->parseIdentifiers(text);

}

void SCsCodeAnalyzer::parse(const QString &text, QStandardItemModel *model)
{
	if (mIsBusy)
		return;

    if (text.isEmpty())
        return;

	mDocumentIdentifiers.clear();
	mIgnoreIdentifiers.clear();

	extractIdentifiers(text, mDocumentIdentifiers);

	fillModel(model, mDocumentIdentifiers);
}




void SCsCodeAnalyzer::extractIdentifiers(const QString &text, QSet<QString> &identifiers)
{
	SCsParser parser;

    QSharedPointer<SCsParserIdtfArray> idtf = parser.getIdentifier(text);

	identifiers = *idtf;
}


void SCsCodeAnalyzer::asynchUpdateExtractIdftFinished()
{
    Q_ASSERT(mAsynchParser->isParseIdentifiersResultPresent());

    if (!mAsynchParser->isParseIdentifiersResultPresent())
        return;

    QSharedPointer<SCsParserIdtfArray> idtfs = mAsynchParser->parseIdentifiersResult();

	*idtfs -= mIgnoreIdentifiers;

	fillModel(mUpdateModel, *idtfs);

	mIgnoreIdentifiers.clear();

	mIsBusy = false;
}
