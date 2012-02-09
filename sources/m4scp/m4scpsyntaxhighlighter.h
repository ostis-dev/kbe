#ifndef M4SCPSYNTAXHIGHLIGHTER_H
#define M4SCPSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class M4SCpSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    M4SCpSyntaxHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text);
private:
    void createSCpOperatorFormat();
    void createSCpAttributesFormat();
    void createSCpOriginsFormat();
    void createOthersFormat();
    void createBracketsFormat();

    void saveFormat(QTextCharFormat format, QStringList patterns);
private:

    struct M4SCpHighlightingRule
    {
         QRegExp pattern;
         QTextCharFormat format;
    };
    QVector<M4SCpHighlightingRule> highlightingRules;

};

#endif // M4SCPSYNTAXHIGHLIGHTER_H
