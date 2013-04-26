#include "scscodeerroranalyzer.h"
#include "scsparserwrapper.h"

#include "scserrortablewidget.h"
#include "scsparserexception.h"
#include <antlr3exception.h>

SCsCodeErrorAnalyzer::SCsCodeErrorAnalyzer(SCsErrorTableWidget *errorTable, QObject *parent /* = 0 */)
	:  QObject(parent), mErrorTable(errorTable)
{

}

void SCsCodeErrorAnalyzer::parse(QString &text)
{
	SCsParser psr;
	QVector<SCsParserException> exeptions =  psr.getExceptions(text);
	QSet<int> lines;
	for(int i=0; i<exeptions.size(); ++i)
		lines.insert(exeptions[i].line());

	emit errorLines(lines);

	showError(exeptions);
}


void SCsCodeErrorAnalyzer::showError(QVector<SCsParserException> &exceptions)
{

    if(mErrorTable == NULL)
        return;

	mErrorTable->clear();

	QVector<SCsParserException>::iterator it=exceptions.begin();
	while( it != exceptions.end())
	{
        QString description = getErrorDescription(*it);
        mErrorTable->addError(description,it->line(),it->positionInLine());
		it++;
	}

	if(!exceptions.isEmpty())
		mErrorTable->show();
	else
		mErrorTable->hide();

}


QString SCsCodeErrorAnalyzer::getErrorDescription(SCsParserException &ex)
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
