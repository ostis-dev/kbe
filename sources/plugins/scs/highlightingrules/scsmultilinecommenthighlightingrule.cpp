/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#include "scsmultilinecommenthighlightingrule.h"

SCsMultiLineCommentHighlightingRule::SCsMultiLineCommentHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format)
    : SCsAbstractHighlightingRule(format)
{
    mStart = start;
    mEnd = end;
}

void SCsMultiLineCommentHighlightingRule::assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text)
{
     highlighter->setCurBlockState(0);

     int startIndex = 0;
     if (highlighter->prevBlockState() != 1)
         startIndex = text.indexOf(mStart);

     while (startIndex >= 0)
     {
        int endIndex = text.indexOf(mEnd, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            highlighter->setCurBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            +mEnd.matchedLength();
        }

        highlighter->setFormating(startIndex, commentLength, format());
        startIndex = text.indexOf(mStart,
                                  startIndex + commentLength);
     }
}
