/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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

