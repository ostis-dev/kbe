/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scsmultilinehighlightingrule.h"

SCsMultiLinetHighlightingRule::SCsMultiLinetHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format, BlockRuleState state)
	: SCsAbstractHighlightingRule(format)
{
	mStart = start;
	mEnd = end;
	mState = state;
}

void SCsMultiLinetHighlightingRule::assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text)
{

	int state = highlighter->curBlockState();
	if (state>0 && state!= mState )
		return;

	highlighter->setCurBlockState(0);

	int startIndex = 0;
	if (highlighter->prevBlockState() != mState )
		startIndex = mStart.indexIn(text);;

	while (startIndex >= 0) {
		int endIndex = mEnd.indexIn(text, startIndex);
		int nLength;
		if (endIndex == -1) {
			highlighter->setCurBlockState(mState);
			nLength = text.length() - startIndex;
		} else {
			nLength = endIndex - startIndex
				+ mEnd.matchedLength();
		}
		highlighter->setFormating(startIndex, nLength, format());
		startIndex = mStart.indexIn(text, startIndex + nLength);
	}

}
