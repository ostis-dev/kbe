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

#ifndef M4SCPSYNTAXHIGHLIGHTER_H
#define M4SCPSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class M4SCpSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    M4SCpSyntaxHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text);
private:
    void createSCpOperatorFormat();
    void createSCpAttributesFormat();
    void createSCpOriginsFormat();
    void createOthersFormat();
    void createBracketsFormat();

    void saveFormat(QTextCharFormat format, QStringList patterns);
private:

    struct M4SCpHighlightingRule
    {
         QRegExp pattern;
         QTextCharFormat format;
    };
    QVector<M4SCpHighlightingRule> highlightingRules;
    QTextCharFormat multiLineCommentFormat;
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

};

#endif // M4SCPSYNTAXHIGHLIGHTER_H
