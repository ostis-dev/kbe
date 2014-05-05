#include "scsparserast.h"

#include "scsParser.h"
#include "scsLexer.h"

#include <QStringList>
#include <QList>
#include <QFile>
#include <QDebug>

ScsParserAST::ScsParserAST()
{

}

void ScsParserAST::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void ScsParserAST::buildTree(QString fileName)
{
    //set file name
    setFileName(fileName);

    //reading from file
    QFile file(this->fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    QString sourceScs = out.readAll();
    //std::string text = sourceScs.toStdString();
    std::string file1 = this->fileName.toStdString();

    //building AST
    pANTLR3_INPUT_STREAM input = antlr3AsciiFileStreamNew((pANTLR3_UINT8)file1.c_str());
    pscsLexer lexer = scsLexerNew(input);
    pANTLR3_COMMON_TOKEN_STREAM tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
    pscsParser parser = scsParserNew(tstream);
    scsParser_syntax_return syntax = parser->syntax(parser);
    pANTLR3_BASE_TREE tree = syntax.tree;
    this->tree = tree;
}

bool ScsParserAST::parse(QList<QStringList> *stringFirstLevelInfo)
{
    this->stringFirstLevelInfo = stringFirstLevelInfo;
    parseFirstLevel();
    return true;
}

bool ScsParserAST::parseFirstLevel()
{
   for (int i = 0; i < tree->getChildCount(tree); i++)
   {
       QStringList exp;
       pANTLR3_BASE_TREE sentence = (pANTLR3_BASE_TREE)tree->getChild(tree, i);
       if (sentence->getType(sentence) == SEP_SIMPLE)
       {
           pANTLR3_BASE_TREE idtf = (pANTLR3_BASE_TREE)sentence->getChild(sentence, 0);
           std::string name((const char *)idtf->getText(idtf)->chars);
           exp.append(name.c_str());
           pANTLR3_BASE_TREE idtf1 = (pANTLR3_BASE_TREE)sentence->getChild(sentence, 1);
           std::string name1((const char *)idtf1->getText(idtf1)->chars);
           exp.append(name1.c_str());
           pANTLR3_BASE_TREE idtf2 = (pANTLR3_BASE_TREE)sentence->getChild(sentence, 2);
           std::string name2((const char *)idtf2->getText(idtf2)->chars);
           exp.append(name2.c_str());

           stringFirstLevelInfo->append(exp);
       }
       else
       {
           //sentence2-7level
       }

   }   
}

