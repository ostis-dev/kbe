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

#include "m4scpcodeanalyzer.h"

M4SCpCodeAnalyzer::M4SCpCodeAnalyzer(QObject *parent) :
    QThread(parent),
    textCursorPos(0),
    previousCompleteModel(VoidModel)
{
    moveToThread(this);
    qRegisterMetaType<CompleteModel>("CompleteModel");
    connect(&timer, SIGNAL(timeout()),this, SLOT(analyze()));

}

M4SCpCodeAnalyzer::~M4SCpCodeAnalyzer()
{
}

void M4SCpCodeAnalyzer::run()
{
    timer.start(1000);
    exec();
}

void M4SCpCodeAnalyzer::analyze()
{
    if(updateVariables())
        emit variablesModelUpdated(variables);
    detectCompleteModel();
}

void M4SCpCodeAnalyzer::updateTextAndCursor(QString text, unsigned int cursorPos)
{
    //QMutexLocker locker(&mutex);
    this->text=text;
    this->textCursorPos=cursorPos;
}

bool M4SCpCodeAnalyzer::updateVariables()
{
    variables.clear();
    int startOfProcedureTag=text.lastIndexOf(QRegExp("\\bprocedure\\b|\\bprogram\\b"),textCursorPos+1);
    int endOfProcedureTag=text.indexOf(')',startOfProcedureTag);

    if (startOfProcedureTag==-1 || endOfProcedureTag==-1)
        return false;

    QString currentProgramHeader=text.mid(startOfProcedureTag,
                                          endOfProcedureTag-startOfProcedureTag);

    if(programHeader==currentProgramHeader)
        return false;
    else programHeader=currentProgramHeader;

    //! detecting constants
    int from=text.indexOf("[[",startOfProcedureTag)+2;
    int length=text.indexOf("]]",startOfProcedureTag)-from;

    if(length<1) return false;

    QString constantsLine=text.mid(from,length);
    constantsLine.remove(QRegExp("\\n|\\t|//[^\n]*|\\s|/\\*(.|\\s)*\\*/"));
    variables.clear();
    variables<<constantsLine.split(',');

    //! detecting constants
    from= text.indexOf("[{",startOfProcedureTag)+2;
    length=text.indexOf("}]",startOfProcedureTag)-from;

    constantsLine=text.mid(from,length);
    constantsLine.remove(QRegExp("\\n|\\t|//[^\n]*|\\s|/\\*(.|\\s)*\\*/"));
    variables<<constantsLine.split(',');
    return true;
}

bool M4SCpCodeAnalyzer::isGlobal(QString text, int cursorPos) const
{
    int closePos = text.lastIndexOf("]",cursorPos);
    int openPos = text.lastIndexOf("([",cursorPos);
    if(closePos!=-1 && openPos!=-1){
        if(closePos>openPos)
            return true;
        else return false;
    }
    if(closePos==-1 && openPos!=-1)
        return false;
    if(closePos!=-1 && openPos==-1)
        return true;
    if(closePos==-1 && openPos==-1)
        return true;
}

bool M4SCpCodeAnalyzer::isAtributeOrVariable(QString text, int cursorPos) const
{
    int colonPos = text.lastIndexOf(":",cursorPos-1);
    int comaPos = text.lastIndexOf(",",cursorPos-1);
    if(comaPos!=-1 && colonPos!=-1){
        if(comaPos<colonPos)
            return true;
        else return false;
    }
    if(comaPos==-1 && colonPos!=-1)
        return true;
    if(comaPos!=-1 && colonPos==-1)
        return false;
    if(comaPos==-1 && colonPos==-1)
        return false;
}

bool M4SCpCodeAnalyzer::isCommentOrProcedure(QString text, int cursorPos) const
{
    bool comment=false, procedure=false, multiline=false;

    //! detecting procedure
    int proceduePos = text.lastIndexOf(QRegExp("\\bprocedure\\b|\\bprogram\\b"),cursorPos-1);
    int endOfProcedure=text.indexOf(")",proceduePos);
    if (proceduePos==-1 && endOfProcedure!=-1) procedure=false;
    if (proceduePos!=-1 && endOfProcedure==-1) procedure=true;
    if (proceduePos!=-1 && endOfProcedure!=-1){
        if (cursorPos<=endOfProcedure && cursorPos>=proceduePos)
            procedure=true;
    }
    if (proceduePos==-1 && endOfProcedure==-1) procedure=false;

    //! detecting single line comment
    int doubleSlash = text.lastIndexOf("//",cursorPos-1);
    int returnChar=text.lastIndexOf("\n",cursorPos-1);
    if(doubleSlash!=-1 && returnChar!=-1){
        if(doubleSlash>returnChar)
            comment=true;
    }
    if((doubleSlash==-1 && returnChar!=-1)||(doubleSlash==-1 && returnChar==-1))
        comment=false;
    if(doubleSlash!=-1 && returnChar==-1)
        comment=true;

    //! detecting multiline comment
    int startComment = text.lastIndexOf("/*",cursorPos-1);
    int endComment=text.indexOf("*/", startComment);
    if (startComment==-1 && endComment!=-1) multiline=false;
    if (startComment!=-1 && endComment==-1) multiline=true;
    if (startComment!=-1 && endComment!=-1){
        if (startComment<=cursorPos && cursorPos<=endComment)
            multiline=true;
    }
    if (startComment==-1 && endComment==-1) multiline=false;
    return procedure || comment || multiline ? true : false;
}

void M4SCpCodeAnalyzer::detectCompleteModel()
{

     if (text.isEmpty()) return;
     if (isCommentOrProcedure(text,textCursorPos)){
         emit completeModelChanged(M4SCpCodeAnalyzer::VoidModel);
         previousCompleteModel=VoidModel;
         return;
     }

     if(isGlobal(text, textCursorPos) ){
        emit completeModelChanged(M4SCpCodeAnalyzer::GlobalModel);
        previousCompleteModel=GlobalModel;
        return;
     }
     else{
         if(isAtributeOrVariable(text, textCursorPos)){
            emit completeModelChanged(M4SCpCodeAnalyzer::AtributesAndVariablesModel);
            previousCompleteModel=AtributesAndVariablesModel;
            return;
         }
     }
}

