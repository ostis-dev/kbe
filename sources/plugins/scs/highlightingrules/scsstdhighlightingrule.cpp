/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scsstdhighlightingrule.h"

SCsStdHighlightingRule::SCsStdHighlightingRule()
{
}

SCsStdHighlightingRule::SCsStdHighlightingRule(QRegExp pattern, QTextCharFormat format)
    : SCsAbstractHighlightingRule(format)
{
    mPattern = pattern;
}

QRegExp SCsStdHighlightingRule::getPattern()
{
    return mPattern;
}

void SCsStdHighlightingRule::assignFormat(SCsSyntaxHighlighter *highliter, const QString& text)
{
    QRegExp expression(mPattern);
    int index = expression.indexIn(text);
    while (index >= 0)
    {
        int length = expression.matchedLength();
        highliter->setFormating(index,length, format());
        index = expression.indexIn(text, index + length);
    }
}
