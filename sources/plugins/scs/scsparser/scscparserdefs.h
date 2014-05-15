/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef	_SCSPARSERDEFS_H
#define _SCSPARSERDEFS_H

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

#endif
