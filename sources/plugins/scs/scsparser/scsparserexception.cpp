/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scsparserexception.h"

SCsParserException::SCsParserException()
    : mExceptionPlace(SCsParserException::UNDEFINED)
    , mExceptionType(-1)
    , mLine(-1)
    , mPositionInLine(-1)
{

}



SCsParserException::SCsParserException(SCsParserException::ExceptionPlace place)
    : mExceptionPlace(place)
    , mExceptionType(-1)
    , mLine(-1)
    , mPositionInLine(-1)
{

}

SCsParserException::SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType)
    : mExceptionPlace(place)
    , mExceptionType(exType)
    , mLine(line)
    , mPositionInLine(positionInLine)

{

}


SCsParserException::SCsParserException(const SCsParserException& copy)
{
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
	mExceptionPlace = copy.mExceptionPlace;
	mExceptionType = copy.mExceptionType;
}

SCsParserException & SCsParserException::operator=(const SCsParserException &copy)
{
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
	mExceptionPlace = copy.mExceptionPlace;
	mExceptionType = copy.mExceptionType;

	return *this;
}


SCsParserException::~SCsParserException()
{

}


SCsParserToken::SCsParserToken()
    : mLine(-1)
    , mPositionInLine(-1)
    , mTokenType(0)
{
	
}


SCsParserToken::SCsParserToken(int tokenType)
    : mLine(-1)
    , mPositionInLine(-1)
    , mTokenType(tokenType)
{

}


SCsParserToken::SCsParserToken(int tokenType,const QString &tokenText, int line, int positionInLine)
    : mTokenText(tokenText)
    , mLine(line)
    , mPositionInLine(positionInLine)
    , mTokenType(tokenType)
{

}


SCsParserToken::SCsParserToken(const SCsParserToken& copy)
{
	mTokenText = copy.mTokenText;
	mTokenType = copy.mTokenType;
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
}


SCsParserToken& SCsParserToken::operator=(const SCsParserToken& copy)
{
	mTokenText = copy.mTokenText;
	mTokenType = copy.mTokenType;
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;

	return *this;
}



SCsParserToken::~SCsParserToken()
{

}
