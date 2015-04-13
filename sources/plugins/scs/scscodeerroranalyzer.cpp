/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scscodeerroranalyzer.h"
#include "scscodeeditor.h"

#include "scserrortablewidget.h"
#include "scsasynchparser.h"
#include <antlr3exception.h>

SCsCodeErrorAnalyzer::SCsCodeErrorAnalyzer(SCsCodeEditor* editor, SCsErrorTableWidget *errorTable)
	:  QObject(editor)
    , mAsynchParser(0)
    , mErrorTable(errorTable)
	, mEditor(editor)
{
	Q_CHECK_PTR(mEditor);

    mAsynchParser = new SCsAsynchParser(this);

    connect(mAsynchParser,SIGNAL(parseExceptionsFinished()),SLOT(parseExceptionFinished()));
}

void SCsCodeErrorAnalyzer::parse(const QString &text)
{
    if (mAsynchParser->doWork() || text.isEmpty())
        return;

    mAsynchParser->parseExceptions(text);
}


void SCsCodeErrorAnalyzer::showError(const QVector<SCsParserException> &exceptions) const
{

    if (mErrorTable == NULL)
        return;

	mErrorTable->clear();

	QVector<SCsParserException>::const_iterator it;
	for (it = exceptions.begin(); it != exceptions.end(); ++it)
	{
        QString description = getErrorDescription(*it);
        mErrorTable->addError(description, it->line(), it->positionInLine());
	}

	if (!exceptions.isEmpty())
		mErrorTable->show();
	else
		mErrorTable->hide();

}


QString SCsCodeErrorAnalyzer::getErrorDescription(const SCsParserException &ex) const
{
	QString descr;
	SCsParserException::ExceptionType type = ex.getExceptionType();

	switch(type)
	{
		case ANTLR3_RECOGNITION_EXCEPTION:
			descr = tr("Token in the input that was not predicted");
			break;
		case ANTLR3_MISMATCHED_TOKEN_EXCEPTION:
			descr = tr("Was expecting one token and found a different one");
			break;
		case ANTLR3_NO_VIABLE_ALT_EXCEPTION:
			descr = tr("Could not find a valid alternative from the input");
			break;
		case ANTLR3_MISMATCHED_SET_EXCEPTION:
			descr = tr("Character in a set was not found");
			break;
		case ANTLR3_EARLY_EXIT_EXCEPTION:
			descr = tr("Found elements less");
			break;
		case ANTLR3_FAILED_PREDICATE_EXCEPTION:
			descr = tr("Failed predicate");
			break;
		case ANTLR3_REWRITE_EARLY_EXCEPTION:
			descr = tr("Rewrite early exception");
			break;
		case ANTLR3_UNWANTED_TOKEN_EXCEPTION:
			descr = tr("Unwanted token");
			break;
		case ANTLR3_MISSING_TOKEN_EXCEPTION:
			descr = tr("Missing token");
			break;

	}

	return descr;
}


void SCsCodeErrorAnalyzer::parseExceptionFinished()
{
    Q_ASSERT(mAsynchParser->isParseExceptionsResultPresent());

    if (!mAsynchParser->isParseExceptionsResultPresent())
        return;

    QSharedPointer<SCsParserExceptionArray> exceptions = mAsynchParser->parseExceptionsResult();

    if (exceptions.isNull())
        return;

    QSet<int> lines;
    for (int i=0; i<exceptions->size(); ++i)
        lines.insert(exceptions->at(i).line());

    emit errorLines(lines);

    showError(*exceptions);

}
