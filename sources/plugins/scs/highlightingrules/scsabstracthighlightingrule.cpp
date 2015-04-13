/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scsabstracthighlightingrule.h"

SCsAbstractHighlightingRule::SCsAbstractHighlightingRule()
{
}

SCsAbstractHighlightingRule::SCsAbstractHighlightingRule(QTextCharFormat format)
{
    mFormat = format;
}

SCsAbstractHighlightingRule::~SCsAbstractHighlightingRule()
{

}

void SCsAbstractHighlightingRule::assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text)
{
    Q_UNUSED(highlighter);
    Q_UNUSED(text);
}

void SCsAbstractHighlightingRule::setFormat(QTextCharFormat format)
{
    mFormat = format;
}

QTextCharFormat SCsAbstractHighlightingRule::format()
{
    return mFormat;
}
