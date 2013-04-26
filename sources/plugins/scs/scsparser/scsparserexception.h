#ifndef SCSPARSEREXCEPTION_H
#define SCSPARSEREXCEPTION_H


#include <QString>

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

	ExceptionPlace type(){ return mExceptionPlace; }
	int line() { return mLine; }
	int positionInLine() { return  mPositionInLine; }
	ExceptionType getExceptionType() { return mExceptionType; }

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
	SCsParserToken(int tokenType, QString tokenText, int line, int positionInLine);
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



#endif // SCSPARSEREXCEPTION_H
