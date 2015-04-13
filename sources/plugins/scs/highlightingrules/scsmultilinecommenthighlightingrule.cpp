/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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
