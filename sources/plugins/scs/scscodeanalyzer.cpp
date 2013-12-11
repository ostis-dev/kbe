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

#include "../scs/scsparser/scsparserwrapper.h"

const QRegExp SCsCodeAnalyzer::msIdentifierExp("([A-Za-z0-9_.#]+)");


SCsCodeAnalyzer::SCsCodeAnalyzer(QObject *parent) :
QObject(parent)
{
	
}


void SCsCodeAnalyzer::fillModel(QStandardItemModel *model)
{
	model->clear();

	QSet<QString> identifiers = mDocumentIdentifiers;

	foreach(const QString &id, identifiers)
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
	extractIdentifiers(text, &mDocumentIdentifiers);

	mDocumentIdentifiers -= mIgnoreIdentifiers;

	fillModel(model);

	mIgnoreIdentifiers.clear();
}



void SCsCodeAnalyzer::parse(const QString &text, QStandardItemModel *model)
{
	mDocumentIdentifiers.clear();
	mIgnoreIdentifiers.clear();

	extractIdentifiers(text, &mDocumentIdentifiers);

	fillModel(model);
}




void SCsCodeAnalyzer::extractIdentifiers(const QString &text, QSet<QString> *identifiers)
{
	SCsParser parser;

	*identifiers = parser.getIdentifier(text);
}
