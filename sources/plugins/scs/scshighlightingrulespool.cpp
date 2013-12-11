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
#include "scsstdhighlightingrule.h"

SCsHighlightingRulesPool* SCsHighlightingRulesPool::msInstance = 0;

SCsHighlightingRulesPool* SCsHighlightingRulesPool::getInstance()
{
    if(!SCsHighlightingRulesPool::msInstance)
    {
        SCsHighlightingRulesPool::msInstance = new SCsHighlightingRulesPool();
    }

    return SCsHighlightingRulesPool::msInstance;
}

SCsHighlightingRulesPool::SCsHighlightingRulesPool()
{
    QTextCharFormat commaFormat;
    QBrush brush = QBrush(Qt::black);
    commaFormat.setForeground(brush);
    QRegExp pattern = QRegExp("[\\.,;:=]");
    mRules.append(new SCsStdHighlightingRule(pattern, commaFormat));

    initiScNodesRules();
    initScArcRules();

    QTextCharFormat format;
    format.setForeground(QBrush(QColor(0, 128, 0)));
    pattern = QRegExp("\".*\"");
    mRules.append(new SCsStdHighlightingRule(pattern, format));

    pattern = QRegExp("/\".*\"/");
    format.setForeground(QBrush(QColor(0, 164, 0)));
    mRules.append(new SCsStdHighlightingRule(pattern, format));

    format.setForeground(Qt::blue);
    pattern = QRegExp("#include");
    mRules.append(new SCsStdHighlightingRule(pattern, format));

    format.setForeground(Qt::darkGray);
    QRegExp start = QRegExp("//");
    QRegExp end = QRegExp("\\n");
    mRules.append(new SCsMultiLineCommentHighlightingRule(start, end, format));

    format.setForeground(Qt::darkGray);
    start = QRegExp("/\\*");
    end = QRegExp("\\*/");
    mRules.append(new SCsMultiLineCommentHighlightingRule(start, end, format));

}

void SCsHighlightingRulesPool::initiScNodesRules()
{
    QTextCharFormat format;

    // Attr
    format.setForeground(QColor(255, 128, 64));// const
    mRules.append(new SCsStdHighlightingRule(QRegExp("[A-Za-z0-9_]+:"), format));
    format.setForeground(QColor(255, 128, 64));// var
    mRules.append(new SCsStdHighlightingRule(QRegExp("[A-Za-z0-9_]+::"), format));
    format.setForeground(QColor(255, 128, 64));// meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("[A-Za-z0-9_]+:::"), format));

    // Set
    format.setForeground(QColor(0, 0, 64));// const
    mRules.append(new SCsStdHighlightingRule(QRegExp("[{}]"), format));
    format.setForeground(QColor(0, 0, 64));// var
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\{\\."), format));
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\.\\}"), format));
    format.setForeground(QColor(0, 0, 64));// meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\{\\.\\."), format));
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\.\\.\\}"), format));

    // Contour
    format.setForeground(QColor(122, 55, 139));// const
    mRules.append(new SCsStdHighlightingRule(QRegExp("[\\[\\]]"), format));
    format.setForeground(QColor(180, 82, 205));// var
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\[\\."), format));
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\.\\]"), format));
    format.setForeground(QColor(209, 95, 238));// meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\[\\.\\."), format));
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\.\\.\\]"), format));

    // SCs link
    format.setForeground(QColor(0, 0, 139));// const
    mRules.append(new SCsStdHighlightingRule(QRegExp("$[A-Za-z0-9]+[_]*[A-Za-z]*"), format));
    format.setForeground(QColor(0, 0, 205));// var
    mRules.append(new SCsStdHighlightingRule(QRegExp("$_[A-Za-z0-9]+[_]*[A-Za-z]*"), format));
    format.setForeground(QColor(0, 0, 238));// meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("$__[A-Za-z0-9]+[_]*[A-Za-z]*"), format));

}

void SCsHighlightingRulesPool::initScArcRules()
{
    QTextCharFormat format;

    // Pos
    format.setForeground(QColor(255, 0, 128)); // const
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\-\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // var
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\-\\>\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("\\-\\>\\>\\>"), format));

    // Neg
    format.setForeground(QColor(255, 0, 128)); // const
    mRules.append(new SCsStdHighlightingRule(QRegExp("/\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // var
    mRules.append(new SCsStdHighlightingRule(QRegExp("/\\>\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("/\\>\\>\\>"), format));

    // Fuzzy
    format.setForeground(QColor(255, 0, 128)); // const
    mRules.append(new SCsStdHighlightingRule(QRegExp("~\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // var
    mRules.append(new SCsStdHighlightingRule(QRegExp("~\\>\\>"), format));
    format.setForeground(QColor(255, 0, 128)); // meta
    mRules.append(new SCsStdHighlightingRule(QRegExp("~\\>\\>\\>"), format));

}

QList<SCsAbstractHighlightingRule*> SCsHighlightingRulesPool::rules()
{
    return mRules;
}

SCsHighlightingRulesPool::~SCsHighlightingRulesPool()
{
}
