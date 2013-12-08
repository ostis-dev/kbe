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
