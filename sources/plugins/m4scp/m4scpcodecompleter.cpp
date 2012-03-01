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

#include "m4scpcodecompleter.h"
#include "m4scpsyntax.h"
#include "m4scpplugin.h"
#include "m4scpwindow.h"

#include <QStringListModel>
#include <QStandardItemModel>
#include <QPlainTextEdit>

M4SCpCodeCompleter::M4SCpCodeCompleter(QObject *parent) :
    QCompleter(parent)
{
    globalModel=new QStandardItemModel(parent);
    variablesModel=new QStandardItemModel(parent);
    atributesModel=new QStandardItemModel(parent);
    ordinalsModel=new QStandardItemModel(parent);
    setModel(globalModel);
    popup()->setIconSize(QSize(16, 16));
    this->parent=parent;
}

M4SCpCodeCompleter::~M4SCpCodeCompleter()
{
}

void M4SCpCodeCompleter::initDictionary()
{
    QStringList words;
    words << M4SCpSyntax::attributes();

    foreach(QString str, words) {
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("attribute.png"),
                    str);
        atributesModel->appendRow(item);
    }
    words.clear();

    words << M4SCpSyntax::ordinals();
    foreach(QString str, words) {
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("ordinal.png"),
                    str);
        ordinalsModel->appendRow(item);
    }

    QMap<QString, QString> templatesMap;
    words.clear();
    words << M4SCpSyntax::operators();
    foreach(QString str, words)
        templatesMap.insert(str, str);

    // create templates
    templatesMap["program"] = "program(,\n[[\n\t// constants\n]],\n[{\n\t// variables\n}])\n\n\nreturn()\nend()";
    templatesMap["procedure"] = "procedure(,\n[[\n\t// constants\n]],\n[{\n\t// variables\n}],\n{[\n\t//parameters\n]})\n\nreturn()\nend()";
    templatesMap["return"] = "return()\n";
    templatesMap["end"] = "end()\n";

    templatesMap["sys_set_event_handler"] = "sys_set_event_handler([\n\t1_: fixed_: , // event\n\t2_: fixed_: , //procedure\n\t3_: fixed_: //pattern\n])\n";
    templatesMap["sys_get_location"] = "sys_get_location([\n\t1_: fixed_: ,// sc-element\n\t2_: assign_: //segment\n])\n";
    templatesMap["sys_open_segment"] = "sys_open_segment([1_: fixed_: ])\n";
    templatesMap["sys_open_segment_uri"] = "sys_open_segment_uri([\n\t1_: fixed_: ,\n\t2_: assign_: \n])\n";
    templatesMap["sys_set_default_segment"] = "sys_set_default_segment([1_: fixed_: ])\n";
    templatesMap["sys_get_default_segment"] = "sys_get_default_segment([1_: assign_: ])\n";
    templatesMap["sys_spin_segment"] = "sys_spin_segment([\n\t1_: fixed_: ,\n\t2_: assign_: \n\t])\n";
    templatesMap["sys_close_segment"] = "sys_close_segment([1_: fixed_: ])\n";
    templatesMap["sys_search"] = "sys_search([\n\t1_: fixed_: ,\t// search pattern\n\t2_: fixed_: {\t// set of search result pairs\n\t\t{1_: , 2_: }\n\t},\n\t3_: fixed_: {\t// set of pairs that consisted of input parameters\n\t\t{1_: , 2_: }\n\t},\n\t4_: \t// result set\n])\n";
    templatesMap["sys_gen"] = "sys_gen([\n\t1_: fixed_: ,\t// pattern generation\n\t2_: fixed_: {\t// set of search result pairs\n\t\t{1_: , 2_: }\n\t},\n\t3_: fixed_: {\t// set of pairs that consisted of input parameters\n\t\t{1_: , 2_: }\n\t},\n\t4_: \t// result set\n])\n";

    templatesMap["print"]   = "print([1_: fixed_: ])\n";
    templatesMap["printEl"] = "printEl([1_: fixed_: ])\n";
    templatesMap["printNl"] = "printNl([1_: fixed_: ])\n";

    templatesMap["searchElStr3"] = "searchElStr3([\n\t1_: ,\n\t2_: ,\n\t3_: \n], ,)\n";
    templatesMap["searchElStr5"] = "searchElStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: \n], ,)\n";
    templatesMap["searchSetStr3"] = "searchSetStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    templatesMap["searchSetStr5"] = "searchSetStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";

    templatesMap["genEl"] = "genEl([1_: assign_: ])\n";
    templatesMap["genElStr3"] = "genElStr3([\n\t1_: ,\n\t2_: ,\n\t3_: \n])\n";
    templatesMap["genElStr5"] = "genElStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: \n])\n";

    templatesMap["eraseEl"] = "eraseEl([1_: fixed_: ])\n";
    templatesMap["eraseElStr3"] = "eraseElStr3([\n\t1_: fixed_: ,\n\t2_: assign_: f_: ,\n\t3_: fixed_: \n])\n";
    templatesMap["eraseElStr5"] = "eraseElStr5([\n\t1_: fixed_: ,\n\t2_: assign_: ,\n\t3_: fixed_: ,\n\t4_: assign_: f_: ,\n\t5_: fixed_: \n])\n";

    templatesMap["selectYStr3"] = "selectYStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    templatesMap["selectNStr3"] = "selectNStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    templatesMap["selectYStr5"] = "selectYStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";
    templatesMap["selectNStr5"] = "selectNStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";

    templatesMap["ifType"] = "ifType([\n\t1_: \n], ,)\n";
    templatesMap["ifEq"] = "ifEq([\n\t1_: fixed_: ,\n\t2_: fixed_: \n], ,)\n";
    templatesMap["ifCoin"] = "ifCoin([\n\t1_: ,\n\t2_: \n], ,)\n";
    templatesMap["ifGr"] = "ifGr([\n\t1_: fixed_: \n\t2_: fixed_: \n], , )\n";
    templatesMap["ifFormCount"] = "ifFormCount([\n\t1_: fixed_: ,\n\t2_: fixed_: \n], ,)\n";
    templatesMap["ifVarAssign"] = "ifVarAssign([\n\t1_: fixed_: \n], ,)\n";

    templatesMap["add"] = "add([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    templatesMap["sub"] = "sub([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    templatesMap["mult"] = "mult([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    templatesMap["div"] = "div([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    templatesMap["pow"] = "pow([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";

    templatesMap["callReturn"] = "callReturn([\n\t1_: fixed_: ,\n\t2_: fixed_: {[\n\t\t1_: fixed_: \n\t\t]}\n])";

    templatesMap["label"] = "label()\n";

    QMap<QString, QString>::iterator it = templatesMap.begin();
    for (; it != templatesMap.end(); ++it) {
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("procedure.png"),
                    it.key());
        globalModel->appendRow(item);
        QModelIndex index = globalModel->indexFromItem(item);
        globalModel->setData(index, QVariant(it.value()), Qt::UserRole);
        globalModel->setData(index, QVariant(it.value()), Qt::ToolTipRole);
    }
    setModel(globalModel);
}

QList<QStandardItem *> M4SCpCodeCompleter::updateVariables(const QString text,QTextCursor cursor)
{
    QList<QStandardItem *> variables;
    int cursorPosition=cursor.position();
    int current=text.lastIndexOf(QRegExp("\\bprocedure\\b|\\bprogram\\b"),cursorPosition+1);
        if (current==-1)
            return variables;
    //constants
    int from=text.indexOf("[[",current)+2;
    int length=text.indexOf("]]",current)-from;
    if(length<1)
        return variables;
    QString constantsLine=text.mid(from,length);
    constantsLine.remove(QRegExp("\\n|\\t|//[^\n]*|\\s|/\\*(.|\\s)*\\*/"));
    QStringList list;
    list<<constantsLine.split(',');
    foreach(QString str, list) {
        if(str.isEmpty()) continue;
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("constant.png"),
                    str);
        variables.append(item);
    }
    //variables
    from= text.indexOf("[{",current)+2;
    length=text.indexOf("}]",current)-from;
    if(length<1)
            return variables;
    constantsLine=text.mid(from,length);
    constantsLine.remove(QRegExp("\\n|\\t|//[^\n]*|\\s|/\\*(.|\\s)*\\*/"));
    list.clear();
    list<<constantsLine.split(',');
    foreach(QString str, list) {
        if(str.isEmpty()) continue;
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("variable.png"),
                    str);
        variables.append(item);
    }
    list.clear();
    list << M4SCpSyntax::attributes();

    foreach(QString str, list) {
        QStandardItem *item = new QStandardItem(
                    M4SCpWindow::findIcon("attribute.png"),
                    str);
        variables.append(item);
    }
    return variables;
 }

void M4SCpCodeCompleter::changeModel()
{
     QPlainTextEdit *editor=qobject_cast<QPlainTextEdit *>(parent);
     QString text = editor->toPlainText();
     int cursorPos = editor->textCursor().position();
     if (text.isEmpty()) return;
     if (isCommentOrProcedure(text,cursorPos)){
         setModel(new QStandardItemModel());
         return;
     }
     //курсор не в теге
     if(isGlobal(text, cursorPos))
         setModel(globalModel);
     //курсор в открытом теге
     else{
         //если нужно вставить атрибут или переменную
         if(isAtributeOrVariable(text, cursorPos)){
            QStandardItemModel *mod = new QStandardItemModel();
            QList<QStandardItem *> list=updateVariables(text,editor->textCursor());
            if(list.isEmpty())
                setModel(atributesModel);
            else{
                foreach(QStandardItem * it, list)
                    mod->appendRow(it);
                setModel(mod);
            }
         }
         //иначе вставляем только порядковые номера (ordinals)
         else
             setModel(ordinalsModel);
     }
}
bool M4SCpCodeCompleter::isGlobal(const QString text, int cursorPos)
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

bool M4SCpCodeCompleter::isAtributeOrVariable(const QString text, int cursorPos)
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

bool M4SCpCodeCompleter::isCommentOrProcedure(const QString text, int cursorPos)
{
    bool comment=false, procedure=false, multiline=false;
    //detecting procedure
    int proceduePos = text.lastIndexOf(QRegExp("\\bprocedure\\b|\\bprogram\\b"),cursorPos-1);
    int endOfProcedure=text.indexOf(")",proceduePos);
    if (proceduePos==-1 && endOfProcedure!=-1) procedure=false;
    if (proceduePos!=-1 && endOfProcedure==-1) procedure=true;
    if (proceduePos!=-1 && endOfProcedure!=-1){
        if (cursorPos<=endOfProcedure && cursorPos>=proceduePos)
            procedure=true;
    }
    if (proceduePos==-1 && endOfProcedure==-1) procedure=false;
    //detecting single line comment
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
    //detecting multiline comment
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
