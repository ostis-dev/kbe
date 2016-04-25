/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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


