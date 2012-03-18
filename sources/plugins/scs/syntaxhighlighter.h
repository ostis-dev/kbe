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

#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QVector>
#include <QSyntaxHighlighter>
#include "abstracthighlightingrule.h"

class AbstractHighlightingRule;

class SyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SyntaxHighlighter(QTextDocument *parent, QList<AbstractHighlightingRule*> highlightingRules);
    void highlightBlock(const QString &text);
    void setFormating(int, int, QTextCharFormat);
    void setCurBlockState(int state);
    int prevBlockState();

private:
    QList<AbstractHighlightingRule*> highlightingRules;

};

#endif // SYNTAXHIGHLIGHTER_H
