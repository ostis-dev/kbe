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

#include "scsparserexception.h"

SCsParserException::SCsParserException():
	mLine(-1), mPositionInLine(-1), mExceptionType(-1), mExceptionPlace(SCsParserException::UNDEFINED)
{

}



SCsParserException::SCsParserException(SCsParserException::ExceptionPlace place) :
	mLine(-1), mPositionInLine(-1), mExceptionType(-1), mExceptionPlace(place)
{

}

SCsParserException::SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType):
	 mLine(line)
	,mPositionInLine(positionInLine)
	,mExceptionType(exType)
	,mExceptionPlace(place)
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


SCsParserToken::SCsParserToken():
	mTokenType(0), mLine(-1), mPositionInLine(-1)
{
	
}


SCsParserToken::SCsParserToken(int tokenType):
	mTokenType(tokenType), mLine(-1), mPositionInLine(-1)
{

}


SCsParserToken::SCsParserToken(int tokenType, QString tokenText, int line, int positionInLine):
	mTokenType(tokenType), mLine(line), mPositionInLine(positionInLine)
{
	mTokenText = tokenText;
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