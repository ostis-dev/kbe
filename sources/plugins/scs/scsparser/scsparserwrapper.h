/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QVector>
#include <QSet>
#include <QSharedPointer>

#include "scsparserexception.h"


#include <antlr3defs.h>

class SCsParser : public QObject
{
    Q_OBJECT
public:
    explicit SCsParser(QObject *parent = 0);
    ~SCsParser();
	QSharedPointer<SCsParserErrorLinesArray> getErrorLines(const QString &text) const;
	QSharedPointer<SCsParserTokenArray> getTokens(const QString &text) const;
	QSharedPointer<SCsParserIdtfArray> getIdentifier(const QString &text) const;
	QSharedPointer<SCsParserExceptionArray> getExceptions(const QString &text) const;

protected:
    pANTLR3_INPUT_STREAM createInputStream(const std::string &text) const;

private:
  
    QString mParseData;

signals:
    
public slots:
    
};


