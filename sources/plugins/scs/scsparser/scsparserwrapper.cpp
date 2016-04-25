/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "SCsCLexer.h"
#include "SCsCParser.h"

#include "scsparserwrapper.h"

#include <QFile>
#include <QTextCodec>

#include <QSet>



SCsParser::SCsParser(QObject *parent) :
    QObject(parent)
{

}

SCsParser::~SCsParser()
{

}


pANTLR3_INPUT_STREAM SCsParser::createInputStream(const std::string &text) const
{
    pANTLR3_INPUT_STREAM    input = 0;

#if defined( __WIN32__ ) || defined( _WIN32 )
    input = antlr3StringStreamNew((pANTLR3_UINT8)text.c_str(),ANTLR3_ENC_UTF8,text.length(),(pANTLR3_UINT8)"scs");
#elif defined( __APPLE_CC__)
    input = antlr3StringStreamNew((pANTLR3_UINT8)text.c_str(),ANTLR3_ENC_UTF8,text.length(),(pANTLR3_UINT8)"scs");
#else
    input = antlr3NewAsciiStringCopyStream((pANTLR3_UINT8)text.c_str(),text.length(),(pANTLR3_UINT8)"scs");
#endif
    return input;
}


QSharedPointer<SCsParserErrorLinesArray> SCsParser::getErrorLines(const QString &text) const
{

	QSharedPointer<SCsParserErrorLinesArray> errorLines = QSharedPointer<SCsParserErrorLinesArray>(new SCsParserErrorLinesArray());

	pANTLR3_INPUT_STREAM    input;
	pSCsCLexer lxr;
	pANTLR3_COMMON_TOKEN_STREAM	    tstream; 
	pSCsCParser psr;


    std::string strData = text.toStdString();
    input = createInputStream(strData);

    if (input == NULL)
	{
		return errorLines;
	}

	lxr = SCsCLexerNew(input);
	if (lxr == NULL)
	{
        input->free(input);
		return errorLines;
	}


	tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
	if (tstream == NULL)
	{
        lxr->free(lxr);
        input->free(input);
		return errorLines;
	}

	
	psr = SCsCParserNew(tstream);
	if (psr == NULL)
	{
        tstream->free(tstream);
        lxr->free(lxr);
        input->free(input);
		return errorLines;
	}

	psr->syntax(psr);

	_ParserException *psrEx = ParserHeadException();
	_LexerException *lxrEx = LexerHeadException();

	while (psrEx)
	{
		errorLines->insert(psrEx->mLine);
		psrEx = psrEx->pNextException;
	}

	while (lxrEx)
	{
		errorLines->insert(lxrEx->mLine);
		lxrEx = lxrEx->pNextException;
	}

	freeLexerExceptionList();
	freeParserExceptionList();

	psr->free(psr);
	tstream->free(tstream);
	lxr->free(lxr);
	input->free(input);

	return errorLines;
}



QSharedPointer<SCsParserExceptionArray> SCsParser::getExceptions(const QString &text) const
{

	QSharedPointer<SCsParserExceptionArray> exceptions = QSharedPointer<SCsParserExceptionArray>(new SCsParserExceptionArray());

	pANTLR3_INPUT_STREAM    input;
	pSCsCLexer lxr;
	pANTLR3_COMMON_TOKEN_STREAM	    tstream; 
	pSCsCParser psr;

    std::string strData = text.toStdString();
    input = createInputStream(strData);

	if (input == NULL)
	{
		return exceptions;
	}

	lxr = SCsCLexerNew(input);
	if (lxr == NULL)
	{
        input->free(input);
		return exceptions;
	}


	tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
	if (tstream == NULL)
	{
        input->free(input);
        lxr->free(lxr);
		return exceptions;
	}


	psr = SCsCParserNew(tstream);
	if (psr == NULL)
	{
        input->free(input);
        lxr->free(lxr);
        tstream->free(tstream);
		return exceptions;
	}

	psr->syntax(psr);

	_ParserException *psrEx = ParserHeadException();
	_LexerException *lxrEx = LexerHeadException();

	while (psrEx)
	{
		exceptions->push_back(SCsParserException(SCsParserException::PARSER, psrEx->mLine, psrEx->mCharPositionInLine, psrEx->mType));
		psrEx = psrEx->pNextException;
	}

	while (lxrEx)
	{
		exceptions->push_back(SCsParserException(SCsParserException::LEXER, lxrEx->mLine, lxrEx->mCharPositionInLine, lxrEx->mType));
		lxrEx = lxrEx->pNextException;
	}

	freeLexerExceptionList();
	freeParserExceptionList();

	psr->free(psr);
	tstream->free(tstream);
	lxr->free(lxr);
	input->free(input);

	return exceptions;
}


QSharedPointer<SCsParserTokenArray> SCsParser::getTokens(const QString &text) const
{

	QSharedPointer<SCsParserTokenArray> token = QSharedPointer<SCsParserTokenArray>(new SCsParserTokenArray());
	pANTLR3_INPUT_STREAM    input;
	pSCsCLexer lxr;
	pANTLR3_COMMON_TOKEN_STREAM	    tstream; 

    std::string strData = text.toStdString();
    input = createInputStream(strData);

	if (input == NULL)
	{
		return token;
	}

	lxr = SCsCLexerNew(input);
	if (lxr == NULL)
	{
        input->free(input);
		return token;
	}


	tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
	if (tstream == NULL)
	{
        input->free(input);
        lxr->free(lxr);
		return token;
	}


	pANTLR3_VECTOR tokens =  tstream->getTokens(tstream);

	pANTLR3_COMMON_TOKEN tok;
	pANTLR3_STRING tokText;
    for(uint i=0; i<tokens->count; i++)
	{
		tok = (pANTLR3_COMMON_TOKEN) tokens->elements[i].element; 
		tokText = tok->getText(tok);
		token->append(SCsParserToken(tok->getType(tok), QString((char*)tokText->chars), tok->getLine(tok), tok->getCharPositionInLine(tok)));
	}

	freeLexerExceptionList();
	freeParserExceptionList();

	tstream->free(tstream);
	lxr->free(lxr);
	input->free(input);

	return token;
}


QSharedPointer<SCsParserIdtfArray> SCsParser::getIdentifier(const QString &text) const
{
	QSharedPointer<SCsParserIdtfArray> idtf = QSharedPointer<SCsParserIdtfArray>(new SCsParserIdtfArray());

 	QSharedPointer<SCsParserTokenArray> token = getTokens(text);
 	QVector<SCsParserToken>::iterator it;

	for (it = token->begin(); it != token->end(); ++it)
	{
		if (it->tokenType() == NAME)
			idtf->insert(it->tokenText());
	}

	token->clear();

	return idtf;
}
