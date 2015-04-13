/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scssyntaxhighlighter.h"

#include <QTextCharFormat>

class SCsSyntaxHighlighter;

class SCsAbstractHighlightingRule
{
public:
    SCsAbstractHighlightingRule();
    SCsAbstractHighlightingRule(QTextCharFormat format);
    QTextCharFormat format();
    void setFormat(QTextCharFormat format);
    ~SCsAbstractHighlightingRule();
    virtual void assignFormat(SCsSyntaxHighlighter* highlighter, const QString& text);

private:
    QTextCharFormat mFormat;

};

