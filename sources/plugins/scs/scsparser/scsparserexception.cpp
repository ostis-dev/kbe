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
