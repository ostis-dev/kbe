/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scsabstracthighlightingrule.h"

#include <QVector>
#include <QSyntaxHighlighter>


class SCsAbstractHighlightingRule;

class SCsSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SCsSyntaxHighlighter(QTextDocument *parent, QList<SCsAbstractHighlightingRule*> highlightingRules);
    void highlightBlock(const QString &text);
    void setFormating(int, int, QTextCharFormat);
    void setCurBlockState(int state);
    int prevBlockState();
	int curBlockState();

private:
    QList<SCsAbstractHighlightingRule*> mHighlightingRules;

};


