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

#include "scshighlightingrulespool.h"
#include "stdhighlightingrule.h"

SCsHighlightingRulesPool* SCsHighlightingRulesPool::instance = 0;

SCsHighlightingRulesPool::SCsHighlightingRulesPool()
{

    QTextCharFormat commaFormat;
    QBrush brush = QBrush(qRgb(25,173,222));
    commaFormat.setForeground(brush);
    commaFormat.setFontWeight(QFont::Bold);
    QRegExp pattern = QRegExp("[\\.,;:]");
    this->rules.append(new StdHighlightingRule(pattern, commaFormat));

    this->initiScNodesRules();
    this->initScArcRules();

    QTextCharFormat format;
    format.setForeground(Qt::darkGreen);
    pattern = QRegExp("\".*\"");
    this->rules.append(new StdHighlightingRule(pattern, format));

    pattern = QRegExp("/\".*\"/");
    format.setForeground(Qt::green);
    this->rules.append(new StdHighlightingRule(pattern, format));

    format.setForeground(Qt::blue);
    pattern = QRegExp("#include");
    this->rules.append(new StdHighlightingRule(pattern, format));

    format.setForeground(Qt::gray);
    QRegExp start = QRegExp("//");
    QRegExp end = QRegExp("\\n");
    this->rules.append(new MultiLineCommentHighlightingRule(start, end, format));

    format.setForeground(Qt::gray);
    start = QRegExp("/\\*");
    end = QRegExp("\\*/");
    this->rules.append(new MultiLineCommentHighlightingRule(start, end, format));

}

void SCsHighlightingRulesPool::initiScNodesRules()
{
    QTextCharFormat format;

    // SCs link
    format.setForeground(QColor(0, 0, 139));// const
    this->rules.append(new StdHighlightingRule(QRegExp("$[A-Za-z]+[_]*[A-Za-z]*"), format));
    format.setForeground(QColor(0, 0, 205));// var
    this->rules.append(new StdHighlightingRule(QRegExp("$_[A-Za-z]+[_]*[A-Za-z]*"), format));
    format.setForeground(QColor(0, 0, 238));// meta
    this->rules.append(new StdHighlightingRule(QRegExp("$__[A-Za-z]+[_]*[A-Za-z]*"), format));

    // Attr
    format.setForeground(QColor(205, 205, 0));// const
    this->rules.append(new StdHighlightingRule(QRegExp("[A-Za-z_]+:"), format));
    format.setForeground(QColor(238, 238, 0));// var
    this->rules.append(new StdHighlightingRule(QRegExp("[A-Za-z_]+::"), format));
    format.setForeground(QColor(255, 255, 0));// meta
    this->rules.append(new StdHighlightingRule(QRegExp("[A-Za-z_]+:::"), format));

    // Set
    format.setForeground(QColor(255, 127, 0));// const
    this->rules.append(new StdHighlightingRule(QRegExp("[{}]"), format));
    format.setForeground(QColor(238, 118, 0));// var
    this->rules.append(new StdHighlightingRule(QRegExp("\\{\\."), format));
    this->rules.append(new StdHighlightingRule(QRegExp("\\.\\}"), format));
    format.setForeground(QColor(205, 102, 0));// meta
    this->rules.append(new StdHighlightingRule(QRegExp("\\{\\.\\."), format));
    this->rules.append(new StdHighlightingRule(QRegExp("\\.\\.\\}"), format));

    // Contour
    format.setForeground(QColor(122, 55, 139));// const
    this->rules.append(new StdHighlightingRule(QRegExp("[\\[\\]]"), format));
    format.setForeground(QColor(180, 82, 205));// var
    this->rules.append(new StdHighlightingRule(QRegExp("\\[\\."), format));
    this->rules.append(new StdHighlightingRule(QRegExp("\\.\\]"), format));
    format.setForeground(QColor(209, 95, 238));// meta
    this->rules.append(new StdHighlightingRule(QRegExp("\\[\\.\\."), format));
    this->rules.append(new StdHighlightingRule(QRegExp("\\.\\.\\]"), format));

}

void SCsHighlightingRulesPool::initScArcRules()
{
    QTextCharFormat format;

    // Pos
    format.setForeground(QColor(102, 205, 0)); // const
    this->rules.append(new StdHighlightingRule(QRegExp("\\-\\>"), format));
    format.setForeground(QColor(118, 238, 0)); // var
    this->rules.append(new StdHighlightingRule(QRegExp("\\-\\>\\>"), format));
    format.setForeground(QColor(127, 255, 0)); // meta
    this->rules.append(new StdHighlightingRule(QRegExp("\\-\\>\\>\\>"), format));

    // Neg
    format.setForeground(QColor(205, 0, 0)); // const
    this->rules.append(new StdHighlightingRule(QRegExp("/\\>"), format));
    format.setForeground(QColor(238, 0, 0)); // var
    this->rules.append(new StdHighlightingRule(QRegExp("/\\>\\>"), format));
    format.setForeground(QColor(255, 0, 0)); // meta
    this->rules.append(new StdHighlightingRule(QRegExp("/\\>\\>\\>"), format));

    // Fuzzy
    format.setForeground(QColor(205, 205, 0)); // const
    this->rules.append(new StdHighlightingRule(QRegExp("~\\>"), format));
    format.setForeground(QColor(238, 238, 0)); // var
    this->rules.append(new StdHighlightingRule(QRegExp("~\\>\\>"), format));
    format.setForeground(QColor(255, 255, 0)); // meta
    this->rules.append(new StdHighlightingRule(QRegExp("~\\>\\>\\>"), format));

}

QList<AbstractHighlightingRule*> SCsHighlightingRulesPool::getRules()
{
    return this->rules;
}

SCsHighlightingRulesPool::~SCsHighlightingRulesPool()
{
}
