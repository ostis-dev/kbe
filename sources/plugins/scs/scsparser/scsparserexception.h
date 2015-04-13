/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QString>
#include <QVector>
#include <QSet>

class SCsParserException
{
public:

	enum ExceptionPlace{
		PARSER,
		LEXER, 
		UNDEFINED
	};

	typedef int ExceptionType;
	SCsParserException();
    SCsParserException(SCsParserException::ExceptionPlace place);
	SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType);
	SCsParserException(const SCsParserException& copy);
	SCsParserException &operator=(const SCsParserException &copy);

	virtual ~SCsParserException();

	ExceptionPlace type() const { return mExceptionPlace; }
	int line() const { return mLine; }
	int positionInLine() const { return  mPositionInLine; }
	ExceptionType getExceptionType() const { return mExceptionType; }

private:
	ExceptionPlace mExceptionPlace;
	ExceptionType mExceptionType;
	int mLine;
	int mPositionInLine;

};

class SCsParserToken
{
public:
	
	enum Tokens 
	{
		UNKNOWN	
	};
	SCsParserToken();
	SCsParserToken(int tokenType);
    SCsParserToken(int tokenType, const QString &tokenText, int line, int positionInLine);
	SCsParserToken(const SCsParserToken& copy);
	SCsParserToken& operator=(const SCsParserToken& copy);
	virtual ~SCsParserToken();

	inline int tokenType(){ return mTokenType; }
	inline QString tokenText(){ return mTokenText; }
	inline int line(){ return mLine; }
	inline int positionInLine(){ return mPositionInLine; }

private:
	QString mTokenText;
	int mLine;
	int mPositionInLine;
	int mTokenType;
};

typedef QVector<SCsParserException> SCsParserExceptionArray;
typedef QVector<SCsParserToken> SCsParserTokenArray;
typedef QSet<int> SCsParserErrorLinesArray;
typedef QSet<QString> SCsParserIdtfArray;


