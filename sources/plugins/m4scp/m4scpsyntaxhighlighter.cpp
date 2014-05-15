/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#include "m4scpsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QColor>

M4SCpSyntaxHighlighter::M4SCpSyntaxHighlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
{
    createSCpOperatorFormat();
    createSCpAttributesFormat();
    createSCpOriginsFormat();
    createBracketsFormat();
    createOthersFormat();
}

void M4SCpSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const M4SCpHighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index,length, rule.format);
            index = expression.indexIn(text, index + length);
        }
        setCurrentBlockState(0);
        int startIndex = 0;
             if (previousBlockState() != 1)
                 startIndex = commentStartExpression.indexIn(text);
        while (startIndex >= 0) {
            int endIndex = commentEndExpression.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
              setCurrentBlockState(1);
              commentLength = text.length() - startIndex;
            } else {
              commentLength = endIndex - startIndex
                              + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
    }
}

void M4SCpSyntaxHighlighter::createSCpOperatorFormat()
{
    QTextCharFormat m4scpOperatorFormat;
    m4scpOperatorFormat.setForeground(Qt::blue);

    QStringList m4scpOperators;
    m4scpOperators
      << "\\badd\\b"         << "\\badd_to_queue\\b" << "\\bcall\\b"
      << "\\bcontAssign\\b"  << "\\bcontErase\\b"    << "\\bdiv\\b"
      << "\\beraseElStr3\\b" << "\\beraseElStr5\\b"  << "\\beraseSetStr3\\b"
      << "\\bgenElStr3\\b"   << "\\bgenElStr5\\b"    << "\\bgsub\\b"
      << "\\bidtfErase\\b"   << "\\bidtfMove\\b"     << "\\bifCoin\\b"
      << "\\bifFormCont\\b"  << "\\bifFormIdtf\\b"   << "\\bifGr\\b"
      << "\\bifNumber\\b"    << "\\bifString\\b"     << "\\bifType\\b"
      << "\\binit\\b"        << "\\bmult\\b"         << "\\bnop\\b"
      << "\\bprint\\b"       << "\\bprintEl\\b"      << "\\bprintNl\\b"
      << "\\bprogram\\b"     << "\\bprogramSCP\\b"   << "\\breturn\\b"
      << "\\bsearchElStr5\\b"<< "\\bsearchSetStr3\\b"<< "\\bsearchSetStr5\\b"
      << "\\bselectNStr5\\b" << "\\bselectYStr3\\b"  << "\\bselectYStr5\\b"
      << "\\bcallReturn\\b"  << "\\beraseEl\\b"      << "\\bgenEl\\b"
      << "\\bidtfAssign\\b"  << "\\bifEq\\b"         << "\\bifGrEq\\b"
      << "\\bifVarAssign\\b" << "\\bpow\\b"          << "\\bprocedure\\b"
      << "\\bsearchElStr3\\b"<<"\\bselectNStr3\\b"   << "\\bsub\\b"

      << "\\bsys_close_segment\\b"       << "\\bsys_create_segment\\b"
      << "\\bsys_get_default_segment\\b" << "\\bsys_get_location\\b"
      << "\\bsys_open_dir_uri\\b"        << "\\bsys_open_segment\\b"
      << "\\bsys_send_message\\b"        << "\\bsys_set_default_segment\\b"
      << "\\bsys_spin_segment\\b"        << "\\bsys_unlink\\b"
      << "\\bvarAssign\\b"               << "\\bvarErase\\b"
      << "\\bwait_erase_element\\b"      << "\\bwait_gen_input_arc\\b"
      << "\\bwait_input_arc\\b"          << "\\bwait_output_arc\\b"
      << "\\bend\\b"                     << "\\bwait_recieve_message\\b"
      << "\\bsys_get_autosegment\\b"     << "\\bsys_open_dir\\b"
      << "\\bsys_open_segment_uri\\b"    << "\\bsys_set_event_handler\\b"
      << "\\bsys_wait\\b"                << "\\bwaitReturn\\b"
      << "\\bwait_gen_output_arc\\b";

    M4SCpHighlightingRule rule;
    saveFormat(m4scpOperatorFormat,m4scpOperators);
    QTextCharFormat labelFormat;
    QBrush brush = QBrush(qRgb(255, 0, 128));
    labelFormat.setForeground(brush);
    rule.pattern = QRegExp("\\label\\b");
    rule.format = labelFormat;
    highlightingRules.append(rule);
}

void M4SCpSyntaxHighlighter::createSCpOriginsFormat()
{
    QStringList m4scpOrdinals;
    m4scpOrdinals
       << "\\b1_\\b"    << "\\b2_\\b" << "\\b3_\\b" << "\\b4_\\b"    << "\\b5_\\b"
       << "\\b7_\\b"    << "\\b8_\\b" << "\\b9_\\b" << "\\bset1_\\b" << "\\bset2_\\b"
       << "\\bset4_\\b" << "\\bset5_" << "\\bset6_" << "\\bset7_\\b" << "\\bset8_\\b"
       << "\\b6_\\b"    << "\\bset3_\\b" << "\\bset9_\\b" ;

    QTextCharFormat m4scpOrdinalsFormat;
    //m4scpOrdinalsFormat.setFontWeight(QFont::Bold);
    m4scpOrdinalsFormat.setForeground(Qt::black);

    saveFormat(m4scpOrdinalsFormat, m4scpOrdinals);
}

void M4SCpSyntaxHighlighter::createSCpAttributesFormat()
{
    QStringList m4scpAttributes;
    m4scpAttributes
        << "\\barc_\\b"     << "\\bconst_\\b"  << "\\belse_\\b"  << "\\bsegc_9_\\b"
        << "\\bfuz_\\b"     << "\\bgoto_\\b"   << "\\bin_\\b"    << "\\bsegc_4_\\b"
        << "\\bmetavar_\\b" << "\\bneg_\\b"    << "\\bnode_\\b"  << "\\bout_\\b"
        << "\\bprm_\\b"     << "\\bsegc_1_\\b" << "\\bsegc_2_\\b"<< "\\bsegc_3_\\b"
        << "\\bsegc_5_\\b"  << "\\bsegc_6_\\b" << "\\bsegc_7_\\b"<< "\\bsegc_8_\\b"
        << "\\bthen_\\b"    << "\\bundf_\\b"   << "\\bvar_\\b"   <<"\\belem_\\b"
        << "\\bf_\\b"       << "\\binit_\\b"   << "\\bpos_\\b";
    QTextCharFormat m4scpAttributesFormat;
    m4scpAttributesFormat.setForeground(QBrush(qRgb(255, 128, 64)));

    saveFormat(m4scpAttributesFormat, m4scpAttributes);
    m4scpAttributes.clear();

    m4scpAttributes<< "\\bassign_\\b" << "\\bfixed_\\b"<< "\\bf_\\b";
    m4scpAttributesFormat.setForeground(Qt::red);
    saveFormat(m4scpAttributesFormat, m4scpAttributes);
 }

void M4SCpSyntaxHighlighter::saveFormat(QTextCharFormat format,QStringList patterns)
{
    M4SCpHighlightingRule rule;
    foreach (const QString &pattern, patterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = format;
         highlightingRules.append(rule);
    }
}
void M4SCpSyntaxHighlighter::createBracketsFormat()
{
    QTextCharFormat bracketsFormat;
    QBrush brush = QBrush(qRgb(0, 64, 0));
    bracketsFormat.setForeground(brush);
    //bracketsFormat.setFontWeight(QFont::Bold);
    M4SCpHighlightingRule rule;

    rule.pattern = QRegExp("[])[(){}]");
    rule.format = bracketsFormat;
    highlightingRules.append(rule);
}
void M4SCpSyntaxHighlighter::createOthersFormat()
{
    M4SCpHighlightingRule rule;
    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(QBrush(QColor(0, 128, 0)));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    QTextCharFormat includeFormat;
    includeFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("#include");
    rule.format = includeFormat;
    highlightingRules.append(rule);

    QTextCharFormat comaFormat;
    comaFormat.setForeground(Qt::black);
    rule.pattern = QRegExp("[,;:]");
    rule.format = comaFormat;
    highlightingRules.append(rule);

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkGray);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGray);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}
