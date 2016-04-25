/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scscparserdefs.h"

_ParserException *SCsCParserHeadException = NULL;
_LexerException *SCsCLexerHeadException  = NULL;
ANTLR3_BOOLEAN _ParserNeedReturn = ANTLR3_FALSE;
ANTLR3_BOOLEAN _ParserNeedRecover = ANTLR3_FALSE;

void ParserExceptionHandler(pANTLR3_BASE_RECOGNIZER recognizer,
	pANTLR3_UINT8 * tokenNames)
{
	pANTLR3_EXCEPTION     ex;
	_ParserException *p;
    pANTLR3_COMMON_TOKEN token;

	p = (_ParserException *) calloc(1,sizeof(_ParserException));

	ex      =   recognizer->state->exception;

	p->mLine = ex->line;
	p->mCharPositionInLine = ex->charPositionInLine;
	token = (pANTLR3_COMMON_TOKEN)ex->token;
	p->mType = (int) ex->type;

	p->pNextException = SCsCParserHeadException;
	SCsCParserHeadException = p;
}


void LexerExceptionHandler(pANTLR3_BASE_RECOGNIZER recognizer,
	pANTLR3_UINT8 * tokenNames)
{
	pANTLR3_EXCEPTION     ex;
	_LexerException *p;
    pANTLR3_COMMON_TOKEN token;

	p = (_LexerException *) calloc(1,sizeof(_LexerException));

	ex      =   recognizer->state->exception;

	p->mLine = ex->line;
	p->mCharPositionInLine = ex->charPositionInLine;
	token = (pANTLR3_COMMON_TOKEN)ex->token;
	p->mType = (int) ex->type;

	p->pNextException = SCsCLexerHeadException;
	SCsCLexerHeadException = p;
}


void freeParserExceptionList()
{
	_ParserException *next, *current;
	next = SCsCParserHeadException;
	current = SCsCParserHeadException;
	while (next)
	{
		current = next;
		next = next->pNextException;

		free(current);
	}
	SCsCParserHeadException = NULL;
}


void freeLexerExceptionList()
{
	_LexerException *next, *current;
	next = SCsCLexerHeadException;
	current = SCsCLexerHeadException;
	while (next)
	{
		current = next;
		next = next->pNextException;

		free(current);
	}
	SCsCLexerHeadException = NULL;
}

_ParserException* ParserHeadException()
{
	return SCsCParserHeadException;
}

_LexerException* LexerHeadException()
{
	return SCsCLexerHeadException;
}


void ParserExceptionRecover(pANTLR3_BASE_RECOGNIZER recognizer)
{

    _ParserNeedReturn = ANTLR3_TRUE;
    _ParserNeedRecover  = ANTLR3_TRUE;

    recognizer->state->error	= ANTLR3_FALSE;
    recognizer->state->failed	= ANTLR3_FALSE;
}

ANTLR3_BOOLEAN ParserNeedReturn()
{
	return _ParserNeedReturn;
}

void SetParserNeedReturn(ANTLR3_BOOLEAN value)
{
	_ParserNeedReturn = value;
}

void SetParserNeedRecover(ANTLR3_BOOLEAN value)
{
	_ParserNeedRecover = value;
}

ANTLR3_BOOLEAN ParserNeedRecover()
{
	return _ParserNeedRecover;
}
