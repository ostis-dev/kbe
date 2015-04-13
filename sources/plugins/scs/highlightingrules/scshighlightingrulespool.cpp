/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scshighlightingrulespool.h"
#include "scsstdhighlightingrule.h"
#include "scsmultilinehighlightingrule.h"

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
    QRegExp pattern;
	QRegExp start,end;

	QTextCharFormat format;
	// simply idtf
	format.setForeground(QColor(128, 0, 0));// const
	mRules.append(new SCsStdHighlightingRule(QRegExp("[A-Za-z0-9_.]+"), format));

    initScArcRules();

	// multi line comment
	format.setForeground(Qt::darkGray);
	start = QRegExp("/\\*");
	end = QRegExp("\\*/");
	mRules.append(new SCsMultiLinetHighlightingRule(start, end, format, SCsMultiLinetHighlightingRule::MultiLineCommentRuleState));


	//keyword
	format.setForeground(Qt::darkGray);
	pattern = QRegExp("/!\\*\\s*keyword:\\s*([a-zA-Z0-9_]+)\\s*\\*/");
	mRules.append(new SCsStdHighlightingRule(pattern,format));

	// single line comment
	format.setForeground(Qt::darkGray);
	//start = QRegExp("//[^\n]*");
	start = QRegExp("//.*$");
	end = QRegExp("$");
	mRules.append(new SCsMultiLinetHighlightingRule(start, end, format, SCsMultiLinetHighlightingRule::SingleLineRuleState));
	//mRules.append(new SCsStdHighlightingRule(start,format));

	
	// URL
	format.setForeground(QBrush(QColor(0, 128, 0)));
	pattern = QRegExp("\".*\"");
	mRules.append(new SCsStdHighlightingRule(pattern, format));

	// content
	format.setForeground(QColor(122, 55, 139));
	start = QRegExp("\\[");
	end = QRegExp("\\]");
	mRules.append(new SCsMultiLinetHighlightingRule(start,end, format, SCsMultiLinetHighlightingRule::ContentRuleState));

}

void SCsHighlightingRulesPool::initScArcRules()
{
    QTextCharFormat format;


    QStringList arcs;
    arcs          << "<>"
                  << ">"
                  << "<"
                  << "\\.\\.>"
                  << "<\\.\\."
                  << "->"
                  << "<-"
                  << "<=>"
                  << "=>"
                  << "<="
                  << "-\\|>"
                  << "<\\|-"
                  << "-/>"
                  << "</-"
                  << "~>"
                  << "<~"
                  << "~\\|>"
                  << "<\\|~"
                  << "~/>"
                  << "</~"
                  << "=" ;

    format.setForeground(QColor(255, 0, 128));
    QStringList::Iterator it;
    for( it = arcs.begin(); it != arcs.end(); ++it )
    {
        mRules.append(new SCsStdHighlightingRule(QRegExp(*it), format) );
        mRules.append(new SCsStdHighlightingRule(QRegExp("_"+*it), format) );
    }

}

QList<SCsAbstractHighlightingRule*> SCsHighlightingRulesPool::rules()
{
    return mRules;
}

SCsHighlightingRulesPool::~SCsHighlightingRulesPool()
{
}
