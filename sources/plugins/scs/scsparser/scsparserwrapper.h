#ifndef SCSPARSERWRAPPER_H
#define SCSPARSERWRAPPER_H

#include <QObject>
#include <QVector>
#include <QSet>

#include "scsparserexception.h"


#include <antlr3defs.h>



class SCsParser : public QObject
{
    Q_OBJECT
public:
    explicit SCsParser(QObject *parent = 0);
    ~SCsParser();
	QSet<int> getErrorLines(const QString &text);
	QVector<SCsParserToken> getTokens(const QString &text);
	QSet<QString> getIdentifier(const QString &text);
	QVector<SCsParserException> getExceptions(const QString &text);

protected:
    //pANTLR3_INPUT_STREAM createInputStream(const QString &text);
    pANTLR3_INPUT_STREAM createInputStream(const std::string &text);

private:
  
    QString mParseData;

signals:
    
public slots:
    
};

#endif // SCSPARSERWRAPPER_H
