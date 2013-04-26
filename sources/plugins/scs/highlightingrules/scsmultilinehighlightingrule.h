#ifndef SCSMULTILINEHIGHLIGHTINGRULE_H
#define SCSMULTILINEHIGHLIGHTINGRULE_H

#include "scsabstracthighlightingrule.h"


	


class SCsMultiLinetHighlightingRule : public SCsAbstractHighlightingRule
{
public:

	enum BlockRuleState
	{
		  MultiLineCommentRuleState = 1
		, ContentRuleState          = 2
		, SingleLineRuleState       = 3
	};



	SCsMultiLinetHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format, BlockRuleState state);
	virtual void assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text);

private:
	BlockRuleState mState;
	QRegExp mStart;
	QRegExp mEnd;

};



#endif // SCSMULTILINEHIGHLIGHTINGRULE_H