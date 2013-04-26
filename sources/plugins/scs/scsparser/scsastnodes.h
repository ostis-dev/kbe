#ifndef ASTNODES_H
#define ASTNODES_H


struct _bool{
	_bool():value(true){}
	bool value;
	_bool operator=(const bool &val)
	{
		this->value = val;
		return *this;
	}
};


#define NodeType(NodeType)  \
	public:					\
		ASTNodeType type() { return NodeType; }

#define SET_ERROR_RULE(ruleName) \
	public:							\
		void ruleName##Error(){m##ruleName##Error.value = true;}     \
		bool ruleName##Check##Error() {return m##ruleName##Error.value; } \
	private:						\
		_bool m##ruleName##Error;		\

#include <QList>
#include <QString>

namespace SCsAST{




class AST;
class SyntaxAST;
class SentenceAST;
class SentenceLvl1AST;
class SentenceLv234561AST;
class SimpleIdentifierAST;
class IdentifierAST;
class AnyIdentifierAST;
class TripleAST;
class SetIdentifierAST;
class OSetIdentifierAST;
class AliasAST;
class AttributesListAST;
class IdentifierWithInternalAST;
class InternalAST;
class InternalSentenceListAST;
class InternalSentenceAST;
class ObjectListAST;
class SimpleIdtfrWAttrSepAST;
class ObjSepWAttrListWIdtfWithInt;
class IntSentenceWSentSep;
class ObjSepWIdtfWithInt;
class SentenceWithSeparator;

enum _ASTNodeType{
     SYNTAX                    = 1
    ,SENTENCE
    ,SENTENCE_LVL1
    ,SENTENCE_LVL23456
    ,SIMPLE_IDENTIFIER
    ,IDENTIFIER
    ,ANY_IDENTIFIER
    ,TRIPLE
    ,SET_IDENTIFIER
    ,OSET_IDENTIFIER
    ,ALIAS
    ,ATRIBUTES_LIST
    ,IDTF_WITH_INT
    ,INTERNAL
    ,INTERNAL_SENTENCE_LIST
    ,INTERNAL_SENTENCE
    ,OBJECT_LIST
    ,SIMPLE_IDENTIFIER_W_ATTRIBUTE_SEPARATOR
    ,OBJSEP_W_ATTR_LIST_W_IDTF_WITH_INT
    ,INT_SENTENCE_W_SENT_SEP
    ,OBJ_SEP_W_IDTF_WITH_INT
    ,SENTANCE_WITH_SEPARATOR
};

typedef _ASTNodeType ASTNodeType;

class AST
{
public:
	AST(){mIsHaveException = false;}
    virtual ASTNodeType type() = 0;
	void setException() { mIsHaveException = true; }
private:
protected:
	bool mIsHaveException;
};



class SyntaxAST: public AST
{
public:
    SyntaxAST();
    virtual ~SyntaxAST();
//    explicit SyntaxAST(SentenceAST *sentence);

    ASTNodeType type() { return SYNTAX; }

    void addSentence(SentenceWithSeparator *sentence);

private:
    QList<SentenceWithSeparator*> mSentenceLst;
};

class SentenceWithSeparator: public AST
{
public:
    SentenceWithSeparator();
    virtual ~SentenceWithSeparator();

    void setSentence(SentenceAST *sentence);
    void setSeparator(QString separator);

    NodeType(SENTANCE_WITH_SEPARATOR)
	SET_ERROR_RULE(setSentence)
	SET_ERROR_RULE(setSeparator)
private:
    SentenceAST* mSentence;
    QString mSeparator;
};


class SentenceAST: public AST
{
public:
    SentenceAST();
    void addSentenceLvl1(SentenceLvl1AST *sentence);
    void addSentenceLv234561(SentenceLv234561AST *sentence);
    virtual ~SentenceAST();

    NodeType(SENTENCE)
	SET_ERROR_RULE(addSentenceLvl1)
	SET_ERROR_RULE(addSentenceLv234561)
private:
    SentenceLvl1AST* mSentenceLvl1;
    SentenceLv234561AST* mSentenceLvl23456;

};

class SentenceLvl1AST: public AST
{
public:
    SentenceLvl1AST();
    SentenceLvl1AST(SimpleIdentifierAST *firstIdtf, SimpleIdentifierAST *secondIdetf, SimpleIdentifierAST *thirdIdtf);
    ~SentenceLvl1AST();

    void setFirstIdentifier(SimpleIdentifierAST *idtf);
    void setSecondIdentifier(SimpleIdentifierAST *idtf);
    void setThirdIdentifier(SimpleIdentifierAST *idtf);
    void setFirstTripleSeparator(QString separator);
    void setSecondTripleSeparator(QString separator);


    NodeType(SENTENCE_LVL1)
	SET_ERROR_RULE(setFirstIdentifier)
	SET_ERROR_RULE(setSecondIdentifier)
	SET_ERROR_RULE(setThirdIdentifier)
	SET_ERROR_RULE(setFirstTripleSeparator)
	SET_ERROR_RULE(setSecondTripleSeparator)
private:
    QString mFirstTripleSep;
    QString mSecondTripleSep;
    SimpleIdentifierAST *mFirstIdtf;
    SimpleIdentifierAST *mSecondIdtf;
    SimpleIdentifierAST *mThirdIdtf;
};

class SentenceLv234561AST: public AST
{
public:
    SentenceLv234561AST();
    SentenceLv234561AST(IdentifierAST *idtf, QString connector, AttributesListAST *attrLst, ObjectListAST* objLst);
    virtual ~SentenceLv234561AST();

    void setIdentifier(IdentifierAST* idtf);
    void setConnector(QString connector);
    void setAttributeList(AttributesListAST* attrLst);
    void setObjectList(ObjectListAST* objLst);

    NodeType(SENTENCE_LVL23456)
	SET_ERROR_RULE(setIdentifier)
	SET_ERROR_RULE(setConnector)
	SET_ERROR_RULE(setAttributeList)
	SET_ERROR_RULE(setObjectList)
private:
    IdentifierAST *mIdentifier;
    QString mConntector;
    AttributesListAST *mAttributeList;
    ObjectListAST *mObjectList;
};

class SimpleIdentifierAST: public AST
{
public:
    SimpleIdentifierAST();
    ~SimpleIdentifierAST();

    void setName(QString name);
    void setUrl(QString url);

    NodeType(SIMPLE_IDENTIFIER)
	SET_ERROR_RULE(setName)
	SET_ERROR_RULE(setUrl)
private:
    QString         mName;
    QString         mUrl;
};


class IdentifierAST: public AST
{
public:
    IdentifierAST();
    void setIdentifier(AnyIdentifierAST *idtf);
    virtual ~IdentifierAST();

    NodeType(IDENTIFIER)
	SET_ERROR_RULE(setIdentifier)
private:
    AnyIdentifierAST *mIdentidier;
};


class TripleAST: public AST
{
public:
    TripleAST();
    virtual ~TripleAST();

    void setFirstIdentifier(IdentifierAST *idtf);
    void setSecondIdentifier(IdentifierAST *idtf);
    void setLeftPar(QString par);
    void setRighPar(QString par);
    void setContent(QString content);

    NodeType(TRIPLE)
	SET_ERROR_RULE(setFirstIdentifier)
	SET_ERROR_RULE(setSecondIdentifier)
	SET_ERROR_RULE(setLeftPar)
	SET_ERROR_RULE(setRighPar)
	SET_ERROR_RULE(setContent)
private:
    QString mLeftPar;
    QString mRightPar;
    QString mContent;
    IdentifierAST   *mFirstIdtf;
    IdentifierAST   *mSecondIdtf;
};

class AnyIdentifierAST: public AST
{
public:
    AnyIdentifierAST();
    void setSimpleIdentifier(SimpleIdentifierAST* idtf);
    void setContent(QString content);
    void setTriple(TripleAST* triple);
    void setSetIdentifier(SetIdentifierAST* setIdtf);
    void setOSetIdentifier(OSetIdentifierAST* osetIdtf);
    void setAlias(AliasAST* alias);
    virtual ~AnyIdentifierAST();


    NodeType(ANY_IDENTIFIER)
	SET_ERROR_RULE(setSimpleIdentifier)
	SET_ERROR_RULE(setContent)
	SET_ERROR_RULE(setTriple)
	SET_ERROR_RULE(setSetIdentifier)
	SET_ERROR_RULE(setOSetIdentifier)
	SET_ERROR_RULE(setAlias)
private:
    bool                 mIsDefine;
    SimpleIdentifierAST *mSimplyIdtf;
    QString              mContent;
    TripleAST           *mTriple;
    SetIdentifierAST    *mSetIdtf;
    OSetIdentifierAST   *mOSetIdtf;
    AliasAST            *mAlias;
};


class ObjSepWAttrListWIdtfWithInt: public AST
{
public:
    ObjSepWAttrListWIdtfWithInt();
    ObjSepWAttrListWIdtfWithInt(QString separator, AttributesListAST *lst, IdentifierWithInternalAST *idtf);
    virtual ~ObjSepWAttrListWIdtfWithInt();

    void setSeparator(QString separator);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);

    NodeType(OBJSEP_W_ATTR_LIST_W_IDTF_WITH_INT)
	SET_ERROR_RULE(setSeparator)
	SET_ERROR_RULE(setAttributeList)
	SET_ERROR_RULE(setIdentifier)
private:
    QString mObjSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtfWithInt;
};


class SetIdentifierAST: public AST
{
public:
    SetIdentifierAST();
    virtual ~SetIdentifierAST();

    void setLeftSeparator(QString sep);
    void setRightSeparator(QString sep);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);
    void addSentence(ObjSepWAttrListWIdtfWithInt *sentence);

    NodeType(SET_IDENTIFIER)
	SET_ERROR_RULE(setLeftSeparator)
	SET_ERROR_RULE(setRightSeparator)
	SET_ERROR_RULE(setAttributeList)
	SET_ERROR_RULE(setIdentifier)
	SET_ERROR_RULE(addSentence)
private:
    QString mLeftSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtf;
    QList<ObjSepWAttrListWIdtfWithInt*> mSetSentenceLst;
    QString mRightSep;
};

class OSetIdentifierAST: public AST
{
public:
    OSetIdentifierAST();
    virtual ~OSetIdentifierAST();

    void setLeftSeparator(QString sep);
    void setRightSeparator(QString sep);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);
    void addSentence(ObjSepWAttrListWIdtfWithInt *sentence);

    NodeType(OSET_IDENTIFIER)
	SET_ERROR_RULE(setLeftSeparator)
	SET_ERROR_RULE(setRightSeparator)
	SET_ERROR_RULE(setAttributeList)
	SET_ERROR_RULE(setIdentifier)
	SET_ERROR_RULE(addSentence)
private:
    QString mLeftSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtf;
    QList<ObjSepWAttrListWIdtfWithInt*> mSetSentenceLst;
    QString mRightSep;
};

class AliasAST: public AST
{
public:
    AliasAST();
    virtual ~AliasAST();
    void setAlias(QString alias);

    NodeType(ALIAS)

	SET_ERROR_RULE(setAlias)
private:
    QString     mAlias;
};


class AttributesListAST: public AST
{
public:
    AttributesListAST();
    AttributesListAST(SimpleIdtfrWAttrSepAST *idtf);
    virtual ~AttributesListAST();

    void addIdentifier(SimpleIdtfrWAttrSepAST *idtf);

    NodeType(ATRIBUTES_LIST)

	SET_ERROR_RULE(addIdentifier)
private:
    QList<SimpleIdtfrWAttrSepAST*> mAttrListSentenceLst;
};

class SimpleIdtfrWAttrSepAST: public AST
{
public:
    SimpleIdtfrWAttrSepAST();
    SimpleIdtfrWAttrSepAST(SimpleIdentifierAST *idtf, QString attrSep);
    virtual ~SimpleIdtfrWAttrSepAST();

    void setIdentifier(SimpleIdentifierAST *idtf);
    void setAttributeSeparator(QString attrSep);

    NodeType(SIMPLE_IDENTIFIER_W_ATTRIBUTE_SEPARATOR)

	SET_ERROR_RULE(setIdentifier)
	SET_ERROR_RULE(setAttributeSeparator)
private:
    SimpleIdentifierAST *mIdentifier;
    QString mAttrSep;
};


class IdentifierWithInternalAST: public AST
{
public:
    IdentifierWithInternalAST();
    explicit IdentifierWithInternalAST(IdentifierAST *idtf, InternalAST *internal = NULL);
    virtual ~IdentifierWithInternalAST();

    void setIdentifier(IdentifierAST *idtf);
    void setInternal(InternalAST *internal);

    NodeType(IDTF_WITH_INT)

	SET_ERROR_RULE(setIdentifier)
	SET_ERROR_RULE(setInternal)
private:
    IdentifierAST   *mIdtf;
    InternalAST     *mInternal;
};


class InternalAST: public AST
{
public:
    InternalAST();
    void setInternalSentenceList(InternalSentenceListAST *lst);
    virtual ~InternalAST();

    NodeType(INTERNAL)

	SET_ERROR_RULE(setInternalSentenceList)
private:
    InternalSentenceListAST *mInternalLst;
};


class InternalSentenceListAST: public AST
{
public:
    InternalSentenceListAST();
    virtual ~InternalSentenceListAST();

    void setLeftInternalSeparator(QString separator);
    void setRigthInternalSeparator(QString separator);
    void addSentence(IntSentenceWSentSep *sentence);

    NodeType(INTERNAL_SENTENCE_LIST)

	SET_ERROR_RULE(setLeftInternalSeparator)
	SET_ERROR_RULE(setRigthInternalSeparator)
	SET_ERROR_RULE(addSentence)
private:
    QString mRightIntSep;
    QString mLeftIntSep;
    QList<IntSentenceWSentSep*> mInternalLst;
};


class InternalSentenceAST: public AST
{
public:
    InternalSentenceAST();
    InternalSentenceAST(QString connector, AttributesListAST *attrLst, ObjectListAST *objLst);
    ~InternalSentenceAST();

    void setConnector(QString connector);
    void setAttributeList(AttributesListAST *lst);
    void setObjectList(ObjectListAST *lst);


    NodeType(INTERNAL_SENTENCE)

	SET_ERROR_RULE(setConnector)
	SET_ERROR_RULE(setAttributeList)
	SET_ERROR_RULE(setObjectList)
private:
    QString mConnector;
    AttributesListAST *mAttributeList;
    ObjectListAST *mObjectList;
};


class ObjectListAST: public AST
{
public:
    ObjectListAST();
    ~ObjectListAST();

    void setIdentifierWithInt(IdentifierWithInternalAST *idtf);
    void addIdentifier(ObjSepWIdtfWithInt *idtf);

    NodeType(OBJECT_LIST)

	SET_ERROR_RULE(setIdentifierWithInt)
	SET_ERROR_RULE(addIdentifier)
private:
    IdentifierWithInternalAST *mIdtfWithInt;
    QList<ObjSepWIdtfWithInt*> mIdtfWithIntLst;
};


class IntSentenceWSentSep: public AST
{
public:
    IntSentenceWSentSep();
    IntSentenceWSentSep(InternalSentenceAST *sentence, QString septSep);
    virtual ~IntSentenceWSentSep();

    void setInternalSentence(InternalSentenceAST *sentence);
    void setSentenceSeparator(QString separator);


    NodeType(INT_SENTENCE_W_SENT_SEP)

	SET_ERROR_RULE(setInternalSentence)
	SET_ERROR_RULE(setSentenceSeparator)
private:
    InternalSentenceAST *mIntSentence;
    QString mSentSep;
};


class ObjSepWIdtfWithInt: public AST
{
public:
    ObjSepWIdtfWithInt();
    ObjSepWIdtfWithInt(IdentifierWithInternalAST *idtf, QString objSep);
    virtual ~ObjSepWIdtfWithInt();

    void setIdentifierWithInternal(IdentifierWithInternalAST *idtf);
    void setObjectSeparator(QString separator);


    NodeType(OBJ_SEP_W_IDTF_WITH_INT)

	SET_ERROR_RULE(setIdentifierWithInternal)
	SET_ERROR_RULE(setObjectSeparator)
private:
    IdentifierWithInternalAST *mIdtwWithInt;
    QString mObjSep;
};



}

#endif // ASTNODES_H
