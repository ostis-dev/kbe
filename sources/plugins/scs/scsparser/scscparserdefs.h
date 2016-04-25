/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include    <antlr3.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct _ParserException_struct _ParserException;
	typedef struct _LexerException_struct  _LexerException;

	struct _ParserException_struct{
		int mLine;
		int mCharPositionInLine;
		int mType;
		_ParserException* pNextException;
	};


	struct _LexerException_struct{
		int mLine;
		int mCharPositionInLine;
		int mType;
		_LexerException* pNextException;
	};

	void freeParserExceptionList();

	void freeLexerExceptionList();

	void ParserExceptionHandler(pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);
	void LexerExceptionHandler(pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);

	void ParserExceptionRecover(pANTLR3_BASE_RECOGNIZER recognizer);
	_ParserException* ParserHeadException();
	_LexerException*  LexerHeadException();
    ANTLR3_BOOLEAN ParserNeedReturn();
    void SetParserNeedReturn(ANTLR3_BOOLEAN value);
    ANTLR3_BOOLEAN ParserNeedRecover();
    void SetParserNeedRecover(ANTLR3_BOOLEAN value);

#ifdef __cplusplus
}
#endif


