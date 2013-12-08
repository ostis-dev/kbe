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

#ifndef SCSASYNCHPARSER_H
#define SCSASYNCHPARSER_H

#include "scsparserexception.h"

#include <QObject>
#include <QFutureWatcher>
#include <QSharedPointer>

class SCsAsynchParser: public QObject
{
    Q_OBJECT

    typedef enum{
          NONE = 0
        , PARSE_EXCEPTIONS
        , PARSE_ERROR_LINES
        , PARSE_IDENTIFIERS
        , PARSE_TOKENS
    } ParserOperation;

public:
    SCsAsynchParser(QObject *parent = 0);
    virtual ~SCsAsynchParser();

    bool parseExceptions(const QString &data);
    bool parseErrorLines(const QString &data);
    bool parseIdentifiers(const QString &data);
    bool parseTokens(const QString &data);

    QSharedPointer<SCsParserExceptionArray> parseExceptionsResult();
    QSharedPointer<SCsParserErrorLinesArray> parseErrorLinesResult();
    QSharedPointer<SCsParserIdtfArray> parseIdentifiersResult();
    QSharedPointer<SCsParserTokenArray> parseTokensResult();

    bool isParseExceptionsResultPresent() const;
    bool isParseErrorLinesResultPresent() const;
    bool isParseIdentifiersResultPresent() const;
    bool isParseTokensResultPresent() const;

    bool doWork() const { return mIsProcessed; }

signals:
    void parseExceptionsFinished();
    void parseErrorLinesFinished();
    void parseIdentifiersFinished();
    void parseTokensFinished();

private slots:
    void processParseExceptionsFinished();
    void processParseErrorLinesFinished();
    void processParseIdentifiersFinished();
    void processParseTokensFinished();

protected:
    bool mIsProcessed;
    QString mData;
    ParserOperation mCurrentOperation;

    QFutureWatcher< QSharedPointer<SCsParserExceptionArray> > mExceptionWatcher;
    QFutureWatcher< QSharedPointer<SCsParserErrorLinesArray> > mErrorLinesWatcher;
    QFutureWatcher< QSharedPointer<SCsParserIdtfArray> > mIdentifiersWatcher;
    QFutureWatcher< QSharedPointer<SCsParserTokenArray> > mTokensWatcher;

private:
    Q_DISABLE_COPY(SCsAsynchParser)
};


class SCsParseExceptionsAsynchTask: public QObject
{
	Q_OBJECT

public:

	SCsParseExceptionsAsynchTask(const QString &text, QObject *parent = 0);
	virtual ~SCsParseExceptionsAsynchTask();

	void execute();
	QSharedPointer<SCsParserExceptionArray> result();
	bool isRunning() const { return mWatcher.isRunning(); }
	bool isStarted() const { return mWatcher.isStarted(); }
	bool isFinished() const { return mWatcher.isFinished(); }

signals:
	void taskFinished();

private slots:
	void finished();

private:
    Q_DISABLE_COPY(SCsParseExceptionsAsynchTask)

    QFutureWatcher< QSharedPointer<SCsParserExceptionArray> > mWatcher;
	QString mText;
};


class SCsParseExtractIdftAsynchTask: public QObject
{
	Q_OBJECT

public:

	SCsParseExtractIdftAsynchTask(const QString &text, QObject *parent = 0);
	virtual ~SCsParseExtractIdftAsynchTask();

	void execute();
	QSharedPointer<SCsParserIdtfArray> result();
	bool isRunning() const { return mWatcher.isRunning(); }
	bool isStarted() const { return mWatcher.isStarted(); }
	bool isFinished() const { return mWatcher.isFinished(); }

signals:
	void taskFinished();

	private slots:
		void finished();

private:
    Q_DISABLE_COPY(SCsParseExtractIdftAsynchTask)

    QFutureWatcher< QSharedPointer<SCsParserIdtfArray> > mWatcher;
	QString mText;
};

#endif // SCSASYNCHPARSER_H
