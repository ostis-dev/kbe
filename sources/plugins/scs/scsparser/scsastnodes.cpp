#include "scsastnodes.h"

using namespace SCsAST;

//***********************************************************************

SyntaxAST::SyntaxAST()
{

}

SyntaxAST::~SyntaxAST()
{
    qDeleteAll(mSentenceLst.begin(), mSentenceLst.end());
    mSentenceLst.clear();
}

//SyntaxAST::SyntaxAST(SentenceAST *sentence)
//{
//    Q_CHECK_PTR(sentence);

//    if(sentence)
//        mSentenceLst.append(sentence);
//}


void SyntaxAST::addSentence(SentenceWithSeparator *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSentenceLst.append(sentence);
}


//***********************************************************************

SentenceAST::SentenceAST():
    mSentenceLvl1(NULL), mSentenceLvl23456(NULL)
{

}

void SentenceAST::addSentenceLv234561(SentenceLv234561AST *sentence)
{
    Q_CHECK_PTR(sentence);
    Q_ASSERT_X(!mSentenceLvl23456,"","mSentenceLvl23456 already defined");

    Q_ASSERT_X(!mSentenceLvl23456 && !mSentenceLvl1,"","variable already defined");

    if(!mSentenceLvl23456 && !mSentenceLvl1)
        mSentenceLvl23456 = sentence;
}

void SentenceAST::addSentenceLvl1(SentenceLvl1AST *sentence)
{
    Q_CHECK_PTR(sentence);
    Q_ASSERT_X(!mSentenceLvl1,"","mSentenceLvl1 already defined");

    Q_ASSERT_X(!mSentenceLvl23456 && !mSentenceLvl1,"","variable already defined");

    if(!mSentenceLvl23456 && !mSentenceLvl1)
        mSentenceLvl1 = sentence;
}

SentenceAST::~SentenceAST()
{
    if(mSentenceLvl1)
        delete mSentenceLvl1;

    if(mSentenceLvl23456)
        delete mSentenceLvl23456;
}

//***********************************************************************

SentenceWithSeparator::SentenceWithSeparator():
    mSentence(NULL)
{

}

SentenceWithSeparator::~SentenceWithSeparator()
{
    if(mSentence)
        delete mSentence;
}

void SentenceWithSeparator::setSentence(SentenceAST *sentence)
{
    Q_ASSERT_X(!mSentence,"","mSentence already defined");
    Q_CHECK_PTR(sentence);

	msetSentenceError = false;

    if(sentence && !mSentence)
        mSentence = sentence;
}

void SentenceWithSeparator::setSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mSeparator.isEmpty(),"","mSeparator already defined");

	msetSeparatorError = false;

    if(!separator.isEmpty() && mSeparator.isEmpty())
        mSeparator = separator;
}


//***********************************************************************

SentenceLvl1AST::SentenceLvl1AST():
    mFirstIdtf(NULL), mSecondIdtf(NULL), mThirdIdtf(NULL)
{

}

SentenceLvl1AST::~SentenceLvl1AST()
{
    if(mFirstIdtf)
        delete mFirstIdtf;
    if(mSecondIdtf)
        delete mSecondIdtf;
    if(mThirdIdtf)
        delete mThirdIdtf;
}

void SentenceLvl1AST::setFirstIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(!mFirstIdtf,"","mFirstIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mFirstIdtf)
        mFirstIdtf = idtf;
}

void SentenceLvl1AST::setSecondIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(!mSecondIdtf,"","mSecondIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mSecondIdtf)
        mSecondIdtf = idtf;
}



void SentenceLvl1AST::setThirdIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(!mThirdIdtf,"","mThirdIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mThirdIdtf)
        mThirdIdtf = idtf;
}

SentenceLvl1AST::SentenceLvl1AST(SimpleIdentifierAST *firstIdtf, SimpleIdentifierAST *secondIdetf, SimpleIdentifierAST *thirdIdtf):
    mFirstIdtf(NULL), mSecondIdtf(NULL), mThirdIdtf(NULL)
{
    Q_CHECK_PTR(firstIdtf);
    Q_CHECK_PTR(secondIdetf);
    Q_CHECK_PTR(thirdIdtf);

    mFirstIdtf = firstIdtf;
    mSecondIdtf = secondIdetf;
    mThirdIdtf = thirdIdtf;
}


void SentenceLvl1AST::setFirstTripleSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mFirstTripleSep.isEmpty(),"","mFirstTripleSep already defined");

    if(!separator.isEmpty() && mFirstTripleSep.isEmpty())
        mFirstTripleSep = separator;
}


void SentenceLvl1AST::setSecondTripleSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mSecondTripleSep.isEmpty(),"","mSecondTripleSep already defined");

    if(!separator.isEmpty() && mSecondTripleSep.isEmpty())
        mSecondTripleSep = separator;
}


//***********************************************************************

SentenceLv234561AST::SentenceLv234561AST():
    mIdentifier(NULL), mAttributeList(NULL), mObjectList(NULL)
{

}

SentenceLv234561AST::SentenceLv234561AST(IdentifierAST *idtf, QString connector, AttributesListAST *attrLst, ObjectListAST *objLst):
    mIdentifier(NULL), mAttributeList(NULL), mObjectList(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_CHECK_PTR(attrLst);
    Q_CHECK_PTR(objLst);

    mIdentifier = idtf;
    mAttributeList = attrLst;
    mObjectList = objLst;
}


SentenceLv234561AST::~SentenceLv234561AST()
{
    if(mIdentifier)
        delete mIdentifier;
    if(mAttributeList)
        delete mAttributeList;
    if(mObjectList)
        delete mObjectList;
}

void SentenceLv234561AST::setIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(!mIdentifier , "", "mIdentifier already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mIdentifier)
        mIdentifier = idtf;
}

void SentenceLv234561AST::setConnector(QString connector)
{
    Q_ASSERT_X(mConntector.isEmpty(), "", "mConntector already defined");
    Q_ASSERT(!connector.isEmpty());

    if(!connector.isEmpty() && mConntector.isEmpty())
        mConntector = connector;
}


void SentenceLv234561AST::setAttributeList(AttributesListAST *attrLst)
{
    Q_ASSERT_X(!mAttributeList , "", "mAttributeList already defined");
    Q_CHECK_PTR(attrLst);

    if(attrLst && !mAttributeList)
        mAttributeList = attrLst;
}


void SentenceLv234561AST::setObjectList(ObjectListAST *objLst)
{
    Q_ASSERT_X(!mObjectList , "", "mObjectList already defined");
    Q_CHECK_PTR(objLst);

    if(objLst && !mObjectList)
        mObjectList = objLst;
}


//***********************************************************************


SimpleIdentifierAST::SimpleIdentifierAST()
{

}

SimpleIdentifierAST::~SimpleIdentifierAST()
{

}

void SimpleIdentifierAST::setName(QString name)
{
    Q_ASSERT_X(mName.isEmpty(),"","mName already defined");
    Q_ASSERT(!name.isEmpty());

    if(!name.isEmpty() && mName.isEmpty())
    {
        mName = name;
        mUrl.clear();
    }
}

void SimpleIdentifierAST::setUrl(QString url)
{
    Q_ASSERT_X(mUrl.isEmpty(),"","mUrl already defined");
    Q_ASSERT(!url.isEmpty());

    if(!url.isEmpty() && !mUrl.isEmpty())
    {
        mUrl = url;
        mName.clear();
    }
}


//***********************************************************************


IdentifierAST::IdentifierAST():
    mIdentidier(NULL)
{

}

void IdentifierAST::setIdentifier(AnyIdentifierAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdentidier ,"","mIdentidier already defined");

    if(idtf && !mIdentidier)
        mIdentidier = idtf;
}

IdentifierAST::~IdentifierAST()
{
    if(mIdentidier)
        delete mIdentidier;
}

//***********************************************************************


TripleAST::TripleAST():
    mFirstIdtf(NULL), mSecondIdtf(NULL)
{

}



TripleAST::~TripleAST()
{
    if(mFirstIdtf)
        delete mFirstIdtf;
    if(mSecondIdtf)
        delete mSecondIdtf;
}

void TripleAST::setFirstIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(!mFirstIdtf ,"","mFirstIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mFirstIdtf)
        mFirstIdtf = idtf;
}

void TripleAST::setSecondIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(!mSecondIdtf ,"","mSecondIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mSecondIdtf)
        mSecondIdtf = idtf;
}

void TripleAST::setLeftPar(QString par)
{
    Q_ASSERT_X(mLeftPar.isEmpty(),"","mLeftPar already defined");
    Q_ASSERT(!par.isEmpty());

    if(!par.isEmpty() && mLeftPar.isEmpty())
        mLeftPar = par;
}

void TripleAST::setRighPar(QString par)
{
    Q_ASSERT_X(mRightPar.isEmpty(),"","mRightPar already defined");
    Q_ASSERT(!par.isEmpty());

    if(!par.isEmpty() && mRightPar.isEmpty())
        mRightPar = par;
}


void TripleAST::setContent(QString content)
{
    Q_ASSERT_X(mContent.isEmpty(),"","mContent already defined");
    Q_ASSERT(!content.isEmpty());

    if(!content.isEmpty() && mContent.isEmpty())
        mContent = content;
}

//***********************************************************************


AnyIdentifierAST::AnyIdentifierAST():
    mIsDefine(false), mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{

}

void AnyIdentifierAST::setAlias(AliasAST *alias)
{
    Q_CHECK_PTR(alias);
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(alias && !mAlias)
    {
        mAlias = alias;
        mIsDefine = true;
    }
}

void AnyIdentifierAST::setOSetIdentifier(OSetIdentifierAST *osetIdtf)
{
    Q_CHECK_PTR(osetIdtf);
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(osetIdtf && !mOSetIdtf)
    {
        mOSetIdtf = osetIdtf;
        mIsDefine = true;
    }
}

void AnyIdentifierAST::setContent(QString content)
{
    Q_ASSERT(!content.isEmpty());
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(!content.isEmpty() && mContent.isEmpty())
    {
        mIsDefine = true;
        mContent = content;
    }
}

void AnyIdentifierAST::setSetIdentifier(SetIdentifierAST *setIdtf)
{
    Q_CHECK_PTR(setIdtf);
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(setIdtf && !mSetIdtf)
    {
        mSetIdtf = setIdtf;
        mIsDefine = true;
    }
}

void AnyIdentifierAST::setSimpleIdentifier(SimpleIdentifierAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(idtf && !mSimplyIdtf)
    {
        mSimplyIdtf = idtf;
        mIsDefine = true;
    }
}

void AnyIdentifierAST::setTriple(TripleAST *triple)
{
    Q_CHECK_PTR(triple);
    Q_ASSERT_X(!mIsDefine,"","variable already defined");

    if(triple && !mTriple)
    {
        mTriple = triple;
        mIsDefine = true;
    }
}

AnyIdentifierAST::~AnyIdentifierAST()
{
    if(mSimplyIdtf)
        delete mSimplyIdtf;
    if(mTriple)
        delete mTriple;
    if(mSetIdtf)
        delete mSetIdtf;
    if(mOSetIdtf)
        delete mOSetIdtf;
    if(mAlias)
        delete mAlias;
}


//***********************************************************************


SetIdentifierAST::SetIdentifierAST():
    mAttrLst(NULL), mIdtf(NULL)
{

}

SetIdentifierAST::~SetIdentifierAST()
{
    qDeleteAll(mSetSentenceLst.begin(), mSetSentenceLst.end());
    mSetSentenceLst.clear();

    if(mAttrLst)
        delete mAttrLst;
    if(mIdtf)
        delete mIdtf;
}


void SetIdentifierAST::setAttributeList(AttributesListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(!mAttrLst ,"","mAttrLst already defined");

    if(lst && !mAttrLst)
        mAttrLst = lst;
}



void SetIdentifierAST::setIdentifier(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdtf ,"","mIdtf already defined");

    if(idtf && !mIdtf)
        mIdtf = idtf;
}


void SetIdentifierAST::setLeftSeparator(QString sep)
{
   Q_ASSERT(!sep.isEmpty());
   Q_ASSERT_X(mLeftSep.isEmpty(),"","mLeftSep already defined");

    if(!sep.isEmpty() && mLeftSep.isEmpty())
        mLeftSep = sep;
}


void SetIdentifierAST::setRightSeparator(QString sep)
{
    Q_ASSERT(!sep.isEmpty());
    Q_ASSERT_X(mRightSep.isEmpty(),"","mRightSep already defined");

     if(!sep.isEmpty() && mRightSep.isEmpty())
         mRightSep = sep;
}


void SetIdentifierAST::addSentence(ObjSepWAttrListWIdtfWithInt *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSetSentenceLst.append(sentence);
}


//***********************************************************************


OSetIdentifierAST::OSetIdentifierAST():
    mAttrLst(NULL), mIdtf(NULL)
{

}

OSetIdentifierAST::~OSetIdentifierAST()
{
    qDeleteAll(mSetSentenceLst.begin(), mSetSentenceLst.end());
    mSetSentenceLst.clear();

    if(mAttrLst)
        delete mAttrLst;
    if(mIdtf)
        delete mIdtf;
}


void OSetIdentifierAST::setAttributeList(AttributesListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(!mAttrLst ,"","mAttrLst already defined");

    if(lst && !mAttrLst)
        mAttrLst = lst;
}



void OSetIdentifierAST::setIdentifier(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdtf ,"","mIdtf already defined");

    if(idtf && !mIdtf)
        mIdtf = idtf;
}


void OSetIdentifierAST::setLeftSeparator(QString sep)
{
   Q_ASSERT(!sep.isEmpty());
   Q_ASSERT_X(mLeftSep.isEmpty(),"","mLeftSep already defined");

    if(!sep.isEmpty() && mLeftSep.isEmpty())
        mLeftSep = sep;
}


void OSetIdentifierAST::setRightSeparator(QString sep)
{
    Q_ASSERT(!sep.isEmpty());
    Q_ASSERT_X(mRightSep.isEmpty(),"","mRightSep already defined");

     if(!sep.isEmpty() && mRightSep.isEmpty())
         mRightSep = sep;
}


void OSetIdentifierAST::addSentence(ObjSepWAttrListWIdtfWithInt *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSetSentenceLst.append(sentence);
}

//***********************************************************************


AliasAST::AliasAST()
{

}

AliasAST::~AliasAST()
{

}

void AliasAST::setAlias(QString alias)
{
    Q_ASSERT(!alias.isEmpty());
    Q_ASSERT_X(mAlias.isEmpty(),"","mAlias already defined");

    mAlias = alias;
}


//***********************************************************************

AttributesListAST::AttributesListAST()
{

}

AttributesListAST::AttributesListAST(SimpleIdtfrWAttrSepAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mAttrListSentenceLst.append(idtf);
}

AttributesListAST::~AttributesListAST()
{
    qDeleteAll(mAttrListSentenceLst.begin(),mAttrListSentenceLst.end());
    mAttrListSentenceLst.clear();
}


void AttributesListAST::addIdentifier(SimpleIdtfrWAttrSepAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mAttrListSentenceLst.append(idtf);
}

//***********************************************************************

IdentifierWithInternalAST::IdentifierWithInternalAST():
    mIdtf(NULL), mInternal(NULL)
{

}

IdentifierWithInternalAST::IdentifierWithInternalAST(IdentifierAST *idtf, InternalAST *internal):
    mIdtf(NULL), mInternal(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_CHECK_PTR(internal);

    mIdtf = idtf;
    mInternal = internal;
}


IdentifierWithInternalAST::~IdentifierWithInternalAST()
{
    if(mIdtf)
        delete mIdtf;
    if(mInternal)
        delete mInternal;
}

void IdentifierWithInternalAST::setIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(!mIdtf ,"","mIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mIdtf)
        mIdtf = idtf;
}

void IdentifierWithInternalAST::setInternal(InternalAST *internal)
{
    Q_ASSERT_X(internal ,"","mInternal already defined");
    Q_CHECK_PTR(internal);

    if(internal && !mInternal)
        mInternal = internal;
}


//***********************************************************************

InternalAST::InternalAST():
    mInternalLst(NULL)
{

}

InternalAST::~InternalAST()
{
    if(mInternalLst)
        delete mInternalLst;
}

void InternalAST::setInternalSentenceList(InternalSentenceListAST *lst)
{
    Q_CHECK_PTR(lst);

    if(lst && !mInternalLst)
        mInternalLst = lst;
}


//***********************************************************************

InternalSentenceListAST::InternalSentenceListAST()
{

}


InternalSentenceListAST::~InternalSentenceListAST()
{
    qDeleteAll(mInternalLst.begin(),mInternalLst.end());
    mInternalLst.clear();
}

void InternalSentenceListAST::addSentence(IntSentenceWSentSep *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mInternalLst.append(sentence);
}


void InternalSentenceListAST::setLeftInternalSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mLeftIntSep.isEmpty(),"","mLeftIntSep already defined");

    if(!separator.isEmpty() && mLeftIntSep.isEmpty())
        mLeftIntSep = separator;
}

void InternalSentenceListAST::setRigthInternalSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mRightIntSep.isEmpty(),"","mRightIntSep already defined");

    if(!separator.isEmpty() && mRightIntSep.isEmpty())
        mRightIntSep = separator;
}

//***********************************************************************

InternalSentenceAST::InternalSentenceAST():
    mAttributeList(NULL), mObjectList(NULL)
{

}

InternalSentenceAST::InternalSentenceAST(QString connector, AttributesListAST *attrLst, ObjectListAST *objLst):
    mAttributeList(NULL), mObjectList(NULL)
{
    Q_CHECK_PTR(objLst);
    Q_CHECK_PTR(attrLst);
    Q_ASSERT(!connector.isEmpty());

    mConnector = connector;
    mAttributeList = attrLst;
    mObjectList = objLst;
}


InternalSentenceAST::~InternalSentenceAST()
{
    if(mAttributeList)
        delete mAttributeList;
    if(mObjectList)
        delete mObjectList;
}

void InternalSentenceAST::setAttributeList(AttributesListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(!mAttributeList ,"","mAttributeList already defined");

    if(lst)
        mAttributeList = lst;
}

void InternalSentenceAST::setConnector(QString connector)
{
    Q_ASSERT(!connector.isEmpty());
    Q_ASSERT_X(mConnector.isEmpty(),"","mConnector already defined");

    if(!connector.isEmpty() && mConnector.isEmpty())
        mConnector = connector;
}


void InternalSentenceAST::setObjectList(ObjectListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(!mObjectList ,"","mObjectList already defined");

    if(lst && !mObjectList)
        mObjectList = lst;
}

//***********************************************************************


ObjectListAST::ObjectListAST():
    mIdtfWithInt(NULL)
{

}

ObjectListAST::~ObjectListAST()
{
    if(mIdtfWithInt)
        delete mIdtfWithInt;

    qDeleteAll(mIdtfWithIntLst.begin(),mIdtfWithIntLst.end());
    mIdtfWithIntLst.clear();
}


void ObjectListAST::addIdentifier(ObjSepWIdtfWithInt *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mIdtfWithIntLst.append(idtf);
}


void ObjectListAST::setIdentifierWithInt(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdtfWithInt ,"","mIdtfWithInt already defined");

    if(idtf && !mIdtfWithInt)
        mIdtfWithInt = idtf;
}

//***********************************************************************

SimpleIdtfrWAttrSepAST::SimpleIdtfrWAttrSepAST():
    mIdentifier(NULL)
{

}


SimpleIdtfrWAttrSepAST::SimpleIdtfrWAttrSepAST(SimpleIdentifierAST *idtf, QString attrSep):
    mIdentifier(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT(!attrSep.isEmpty());

    mIdentifier = idtf;
    mAttrSep = attrSep;
}


SimpleIdtfrWAttrSepAST::~SimpleIdtfrWAttrSepAST()
{
    if(mIdentifier)
        delete mIdentifier;
}

void SimpleIdtfrWAttrSepAST::setIdentifier(SimpleIdentifierAST *idtf)
{
   Q_CHECK_PTR(idtf);

   Q_ASSERT_X(!mIdentifier ,"","mIdentifier already defined");

    if(idtf && !mIdentifier)
        mIdentifier = idtf;
}



void SimpleIdtfrWAttrSepAST::setAttributeSeparator(QString attrSep)
{
    Q_ASSERT(!attrSep.isEmpty());
    Q_ASSERT_X(mAttrSep.isEmpty(),"","mAttrSep already defined");

    if(!attrSep.isEmpty() && mAttrSep.isEmpty())
        mAttrSep = attrSep;

}

//***********************************************************************


ObjSepWAttrListWIdtfWithInt::ObjSepWAttrListWIdtfWithInt():
    mAttrLst(NULL), mIdtfWithInt(NULL)
{

}

ObjSepWAttrListWIdtfWithInt::ObjSepWAttrListWIdtfWithInt(QString separator, AttributesListAST *lst, IdentifierWithInternalAST *idtf):
    mAttrLst(NULL), mIdtfWithInt(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_CHECK_PTR(lst);
    Q_ASSERT(!separator.isEmpty());

    mAttrLst = lst;
    mIdtfWithInt = idtf;
    mObjSep = separator;
}


ObjSepWAttrListWIdtfWithInt::~ObjSepWAttrListWIdtfWithInt()
{
    if(mIdtfWithInt)
        delete mIdtfWithInt;
    if(mAttrLst)
        delete mAttrLst;
}


void ObjSepWAttrListWIdtfWithInt::setAttributeList(AttributesListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(!mAttrLst ,"","mAttrLst already defined");

    if(lst && !mAttrLst)
        mAttrLst = lst;
}


void ObjSepWAttrListWIdtfWithInt::setIdentifier(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdtfWithInt ,"","mIdtfWithInt already defined");

    if(idtf && !mIdtfWithInt)
        mIdtfWithInt = idtf;
}


void ObjSepWAttrListWIdtfWithInt::setSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mObjSep.isEmpty(),"","mObjSep already defined");


    if(!separator.isEmpty() && mObjSep.isEmpty())
        mObjSep = separator;
}

//***********************************************************************

IntSentenceWSentSep::IntSentenceWSentSep():
    mIntSentence(NULL)
{

}

IntSentenceWSentSep::IntSentenceWSentSep(InternalSentenceAST *sentence, QString septSep):
    mIntSentence(NULL)
{
    Q_CHECK_PTR(sentence);
    Q_ASSERT(!septSep.isEmpty());

    mSentSep = septSep;
    mIntSentence = sentence;
}

IntSentenceWSentSep::~IntSentenceWSentSep()
{
    if(mIntSentence)
        delete mIntSentence;
}


void IntSentenceWSentSep::setInternalSentence(InternalSentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);
    Q_ASSERT_X(!mIntSentence ,"","mIntSentence already defined");

    if(sentence && !mIntSentence)
        mIntSentence = sentence;
}

void IntSentenceWSentSep::setSentenceSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mSentSep.isEmpty(),"","mSentSep already defined");

    if(!separator.isEmpty() && mSentSep.isEmpty())
        mSentSep = separator;
}


//***********************************************************************

ObjSepWIdtfWithInt::ObjSepWIdtfWithInt():
    mIdtwWithInt(NULL)
{

}

ObjSepWIdtfWithInt::ObjSepWIdtfWithInt(IdentifierWithInternalAST *idtf, QString objSep):
    mIdtwWithInt(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT(!objSep.isEmpty());

    mIdtwWithInt = idtf;
    mObjSep = objSep;
}


ObjSepWIdtfWithInt::~ObjSepWIdtfWithInt()
{
    if(mIdtwWithInt)
        delete mIdtwWithInt;
}


void ObjSepWIdtfWithInt::setIdentifierWithInternal(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT_X(!mIdtwWithInt ,"","mIdtwWithInt already defined");

    if(idtf && !mIdtwWithInt)
        mIdtwWithInt = idtf;
}


void ObjSepWIdtfWithInt::setObjectSeparator(QString separator)
{
    Q_ASSERT(!separator.isEmpty());
    Q_ASSERT_X(mObjSep.isEmpty(),"","mObjSep already defined");

    if(!separator.isEmpty() && mObjSep.isEmpty())
        mObjSep = separator;
}



//***********************************************************************

