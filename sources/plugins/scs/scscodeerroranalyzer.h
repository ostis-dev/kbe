#ifndef SCSCODEERRORANALYZER_H
#define SCSCODEERRORANALYZER_H

#include <QObject>
#include <QSet>

class SCsErrorTableWidget;
class SCsParserException;

class SCsCodeErrorAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit SCsCodeErrorAnalyzer(SCsErrorTableWidget *errorTable, QObject *parent = 0);
    void parse(QString &text);

private:
	void showError(QVector<SCsParserException> &exceptions);
	QString getErrorDescription(SCsParserException &ex);

	SCsErrorTableWidget *mErrorTable;
signals:
    void errorLines(QSet<int> lines);
public slots:
    
};

#endif // SCSCODEERRORANALYZER_H
