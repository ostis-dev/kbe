/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scssyntaxhighlighter.h"

SCsSyntaxHighlighter::SCsSyntaxHighlighter(QTextDocument *parent, QList<SCsAbstractHighlightingRule*> highlightingRules)
    : QSyntaxHighlighter(parent)
{
    mHighlightingRules = highlightingRules;
}

void SCsSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (SCsAbstractHighlightingRule* rule, mHighlightingRules)
    {
        rule->assignFormat(this, text);
    }
}

void SCsSyntaxHighlighter::setFormating(int index, int length, QTextCharFormat format)
{
    setFormat(index, length, format);
}

void SCsSyntaxHighlighter::setCurBlockState(int state)
{
    setCurrentBlockState(state);
}

int SCsSyntaxHighlighter::prevBlockState()
{
    return previousBlockState();
}


int SCsSyntaxHighlighter::curBlockState()
{
	return currentBlockState();
}
