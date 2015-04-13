/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>

#include "scsparserexception.h"

class SCsErrorTableWidget;
class SCsParserException;
class SCsCodeEditor;
class SCsParseExceptionsAsynchTask;
class SCsAsynchParser;

class SCsCodeErrorAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit SCsCodeErrorAnalyzer(SCsCodeEditor* editor, SCsErrorTableWidget *errorTable);
    void parse(const QString &text);

private:
	void showError(const QVector<SCsParserException> &exceptions) const;
	QString getErrorDescription(const SCsParserException &ex) const;

    SCsAsynchParser* mAsynchParser;

	SCsErrorTableWidget* mErrorTable;
	SCsCodeEditor* mEditor;

signals:
    void errorLines(QSet<int> lines);

private slots:
	void parseExceptionFinished();
};


