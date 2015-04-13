/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scsabstracthighlightingrule.h"

class SCsMultiLineCommentHighlightingRule : public SCsAbstractHighlightingRule
{
public:
    SCsMultiLineCommentHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format);
    virtual void assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text);

private:
    QRegExp mStart;
    QRegExp mEnd;

};

