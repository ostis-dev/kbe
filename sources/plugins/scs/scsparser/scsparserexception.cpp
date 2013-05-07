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