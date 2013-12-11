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
