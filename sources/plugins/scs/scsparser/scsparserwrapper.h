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

#ifndef SCSPARSERWRAPPER_H
#define SCSPARSERWRAPPER_H

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

#endif // SCSPARSERWRAPPER_H
