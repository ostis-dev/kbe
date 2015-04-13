/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scsasynchparser.h"
#include "scsparserwrapper.h"

#include <QtCore>
#include <QtConcurrentRun>

QSharedPointer<SCsParserExceptionArray> parseExceptionsFn(const QString &text)
{
	SCsParser psr;
    QSharedPointer<SCsParserExceptionArray> array = psr.getExceptions(text);
	return array;
}

QSharedPointer<SCsParserIdtfArray> parseIdentifiersFn(const QString &text)
{
	SCsParser psr;
	QSharedPointer<SCsParserIdtfArray> array = psr.getIdentifier(text);
	return array;
}

QSharedPointer<SCsParserTokenArray> parseTokensFn(const QString &text)
{
    SCsParser psr;
    QSharedPointer<SCsParserTokenArray> array = psr.getTokens(text);
    return array;
}

QSharedPointer<SCsParserErrorLinesArray> parseErrorLinesFn(const QString &text)
{
    SCsParser psr;
    QSharedPointer<SCsParserErrorLinesArray> array = psr.getErrorLines(text);
    return array;
}

//////////////////////////////////////////////////////////////////////////

SCsAsynchParser::SCsAsynchParser(QObject *parent)
    : QObject(parent)
    , mIsProcessed(false)
    , mCurrentOperation(NONE)
{
    connect(&mExceptionWatcher,SIGNAL(finished()),this,SLOT(processParseExceptionsFinished()));
    connect(&mIdentifiersWatcher,SIGNAL(finished()),this,SLOT(processParseIdentifiersFinished()));
}

SCsAsynchParser::~SCsAsynchParser()
{

}

bool SCsAsynchParser::parseExceptions(const QString &data)
{
    if (mIsProcessed)
        return false;

    mCurrentOperation = PARSE_EXCEPTIONS;

    mIsProcessed = true;

    mData = data;

    mExceptionWatcher.setFuture(QtConcurrent::run(parseExceptionsFn, mData));

    return true;
}

bool SCsAsynchParser::isParseExceptionsResultPresent() const
{
    return (mCurrentOperation == PARSE_EXCEPTIONS && mExceptionWatcher.isFinished());
}

void SCsAsynchParser::processParseExceptionsFinished()
{
    emit parseExceptionsFinished();
}

QSharedPointer<SCsParserExceptionArray> SCsAsynchParser::parseExceptionsResult()
{
    Q_ASSERT(isParseExceptionsResultPresent());

    if (!isParseExceptionsResultPresent())
    {
        return QSharedPointer<SCsParserExceptionArray>();
    }

    mIsProcessed = false;
    mCurrentOperation = NONE;
    return mExceptionWatcher.result();
}


bool SCsAsynchParser::parseIdentifiers(const QString &data)
{
    if (mIsProcessed)
        return false;

    mCurrentOperation = PARSE_IDENTIFIERS;

    mIsProcessed = true;

    mData = data;

    mIdentifiersWatcher.setFuture(QtConcurrent::run(parseIdentifiersFn, mData));

    return true;
}

bool SCsAsynchParser::isParseIdentifiersResultPresent() const
{
    return (mCurrentOperation == PARSE_IDENTIFIERS && mIdentifiersWatcher.isFinished());
}

void SCsAsynchParser::processParseIdentifiersFinished()
{
    emit parseIdentifiersFinished();
}

QSharedPointer<SCsParserIdtfArray> SCsAsynchParser::parseIdentifiersResult()
{
    Q_ASSERT(isParseIdentifiersResultPresent());

    if (!isParseIdentifiersResultPresent())
    {
        return QSharedPointer<SCsParserIdtfArray>();
    }

    mIsProcessed = false;
    mCurrentOperation = NONE;
    return mIdentifiersWatcher.result();
}


bool SCsAsynchParser::parseTokens(const QString &data)
{
    if (mIsProcessed)
        return false;

    mCurrentOperation = PARSE_TOKENS;

    mIsProcessed = true;

    mData = data;

    mTokensWatcher.setFuture(QtConcurrent::run(parseTokensFn, mData));

    return true;
}

bool SCsAsynchParser::isParseTokensResultPresent() const
{
    return (mCurrentOperation == PARSE_TOKENS && mTokensWatcher.isFinished());
}

void SCsAsynchParser::processParseTokensFinished()
{
    emit parseTokensFinished();
}

QSharedPointer<SCsParserTokenArray> SCsAsynchParser::parseTokensResult()
{
    Q_ASSERT(isParseTokensResultPresent());

    if (!isParseTokensResultPresent())
    {
        return QSharedPointer<SCsParserTokenArray>();
    }

    mIsProcessed = false;
    mCurrentOperation = NONE;
    return mTokensWatcher.result();
}


bool SCsAsynchParser::parseErrorLines(const QString &data)
{
    if (mIsProcessed)
        return false;

    mCurrentOperation = PARSE_ERROR_LINES;

    mIsProcessed = true;

    mData = data;

    mErrorLinesWatcher.setFuture(QtConcurrent::run(parseErrorLinesFn, mData));

    return true;
}

bool SCsAsynchParser::isParseErrorLinesResultPresent() const
{
    return (mCurrentOperation == PARSE_ERROR_LINES && mErrorLinesWatcher.isFinished());
}

void SCsAsynchParser::processParseErrorLinesFinished()
{
    emit parseErrorLinesFinished();
}

QSharedPointer<SCsParserErrorLinesArray> SCsAsynchParser::parseErrorLinesResult()
{
    Q_ASSERT(isParseErrorLinesResultPresent());

    if (!isParseErrorLinesResultPresent())
    {
        return QSharedPointer<SCsParserErrorLinesArray>();
    }

    mIsProcessed = false;
    mCurrentOperation = NONE;
    return mErrorLinesWatcher.result();
}

//////////////////////////////////////////////////////////////////////////


SCsParseExceptionsAsynchTask::SCsParseExceptionsAsynchTask(const QString &text, QObject *parent)
	: QObject(parent)
	, mText(text)
{
	connect(&mWatcher,SIGNAL(finished()),this,SIGNAL(taskFinished()));
}

SCsParseExceptionsAsynchTask::~SCsParseExceptionsAsynchTask()
{

}

void SCsParseExceptionsAsynchTask::execute()
{
	if (!isRunning())
		mWatcher.setFuture(QtConcurrent::run(parseExceptionsFn,mText));
}

QSharedPointer<SCsParserExceptionArray> SCsParseExceptionsAsynchTask::result()
{
	return QSharedPointer<SCsParserExceptionArray>(mWatcher.result());
}


void SCsParseExceptionsAsynchTask::finished()
{
	emit taskFinished();
}


//////////////////////////////////////////////////////////////////////////

SCsParseExtractIdftAsynchTask::SCsParseExtractIdftAsynchTask(const QString &text, QObject *parent)
	: QObject(parent)
	, mText(text)
{
	connect(&mWatcher,SIGNAL(finished()),this,SIGNAL(taskFinished()));
}

SCsParseExtractIdftAsynchTask::~SCsParseExtractIdftAsynchTask()
{
}

void SCsParseExtractIdftAsynchTask::execute()
{
    if (!isRunning())
        mWatcher.setFuture(QtConcurrent::run(parseIdentifiersFn,mText));
}

QSharedPointer<SCsParserIdtfArray> SCsParseExtractIdftAsynchTask::result()
{
	return QSharedPointer<SCsParserIdtfArray>(mWatcher.result());
}


void SCsParseExtractIdftAsynchTask::finished()
{
	emit taskFinished();
}
