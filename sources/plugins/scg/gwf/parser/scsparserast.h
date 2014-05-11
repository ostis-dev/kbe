#ifndef SCSPARSERAST_H
#define SCSPARSERAST_H

#include <QString>
#include <antlr3defs.h>

class ScsParserAST
{
public:
    ScsParserAST();

    /*! Set fileName.
     * @param fileName file name.
     */
    void setFileName(QString fileName);
    /*! Builds AST from scs file.
     * @param fileName file name.
     */
    void buildTree(QString fileName);
    /*! Parse scs file.
     * @param stringFirstLevelInfo list of parsed sentences.
     * @return If parsed successfully returns true.
     */
    bool parse(QList<QStringList> *stringFirstLevelInfo);
    /*! Parse  first level of scs file.
     * @return If parsed successfully returns true.
     */
    bool parseFirstLevel();

private:
    //! file name
    QString fileName;
    //! AST
    pANTLR3_BASE_TREE tree;
    //! list of parsed sentences
    QList<QStringList> *stringFirstLevelInfo;

};

#endif // SCSPARSERAST_H
