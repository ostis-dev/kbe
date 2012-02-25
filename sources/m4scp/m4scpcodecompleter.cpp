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
#include "config.h"
#include <QStringListModel>
#include <QStandardItemModel>

M4SCpCodeCompleter::M4SCpCodeCompleter(QObject *parent) :
    QCompleter(parent)
{
    QStandardItemModel *_mItemModel = new QStandardItemModel(parent);
    setModel(_mItemModel);
    popup()->setIconSize(QSize(16, 16));
}

M4SCpCodeCompleter::~M4SCpCodeCompleter()
{
}

void M4SCpCodeCompleter::initDictionary()
{
    QStandardItemModel *mod = static_cast<QStandardItemModel*>(model());
    QStringList words;
    words << M4SCpSyntax::attributes();

    foreach(QString str, words) {
        QStandardItem *item = new QStandardItem(
                    QIcon(Config::pathMedia.absolutePath() + "/m4scp/icons/attribute.png"),
                    str);
        mod->appendRow(item);
    }
    words.clear();
    words << M4SCpSyntax::ordinals();
    foreach(QString str, words) {
        QStandardItem *item = new QStandardItem(
                    QIcon(Config::pathMedia.absolutePath() + "/m4scp/icons/ordinal.png"),
                    str);
        mod->appendRow(item);
    }

    QMap<QString, QString> mTemplatesMap;
    words.clear();
    words << M4SCpSyntax::operators();
    foreach(QString str, words)
        mTemplatesMap.insert(str, str);

    // create templates
    mTemplatesMap["program"] = "program(,\n[[\n\t// constants\n]],\n[{\n\t// variables\n}])\n\n\nreturn()\nend()";
    mTemplatesMap["procedure"] = "procedure(,\n[[\n\t// constants\n]],\n[{\n\t// variables\n}],\n{[\n\t//parameters\n]})\n\nreturn()\nend()";
    mTemplatesMap["return"] = "return()\n";
    mTemplatesMap["end"] = "end()\n";

    mTemplatesMap["sys_set_event_handler"] = "sys_set_event_handler([\n\t1_: fixed_: , // event\n\t2_: fixed_: , //procedure\n\t3_: fixed_: //pattern\n])\n";
    mTemplatesMap["sys_get_location"] = "sys_get_location([\n\t1_: fixed_: ,// sc-element\n\t2_: assign_: //segment\n])\n";
    mTemplatesMap["sys_open_segment"] = "sys_open_segment([1_: fixed_: ])\n";
    mTemplatesMap["sys_open_segment_uri"] = "sys_open_segment_uri([\n\t1_: fixed_: ,\n\t2_: assign_: \n])\n";
    mTemplatesMap["sys_set_default_segment"] = "sys_set_default_segment([1_: fixed_: ])\n";
    mTemplatesMap["sys_get_default_segment"] = "sys_get_default_segment([1_: assign_: ])\n";
    mTemplatesMap["sys_spin_segment"] = "sys_spin_segment([\n\t1_: fixed_: ,\n\t2_: assign_: \n\t])\n";
    mTemplatesMap["sys_close_segment"] = "sys_close_segment([1_: fixed_: ])\n";
    mTemplatesMap["sys_search"] = "sys_search([\n\t1_: fixed_: ,\t// search pattern\n\t2_: fixed_: {\t// set of search result pairs\n\t\t{1_: , 2_: }\n\t},\n\t3_: fixed_: {\t// set of pairs that consisted of input parameters\n\t\t{1_: , 2_: }\n\t},\n\t4_: \t// result set\n])\n";
    mTemplatesMap["sys_gen"] = "sys_gen([\n\t1_: fixed_: ,\t// pattern generation\n\t2_: fixed_: {\t// set of search result pairs\n\t\t{1_: , 2_: }\n\t},\n\t3_: fixed_: {\t// set of pairs that consisted of input parameters\n\t\t{1_: , 2_: }\n\t},\n\t4_: \t// result set\n])\n";

    mTemplatesMap["print"]   = "print([1_: fixed_: ])\n";
    mTemplatesMap["printEl"] = "printEl([1_: fixed_: ])\n";
    mTemplatesMap["printNl"] = "printNl([1_: fixed_: ])\n";

    mTemplatesMap["searchElStr3"] = "searchElStr3([\n\t1_: ,\n\t2_: ,\n\t3_: \n], ,)\n";
    mTemplatesMap["searchElStr5"] = "searchElStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: \n], ,)\n";
    mTemplatesMap["searchSetStr3"] = "searchSetStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    mTemplatesMap["searchSetStr5"] = "searchSetStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";

    mTemplatesMap["genEl"] = "genEl([1_: assign_: ])\n";
    mTemplatesMap["genElStr3"] = "genElStr3([\n\t1_: ,\n\t2_: ,\n\t3_: \n])\n";
    mTemplatesMap["genElStr5"] = "genElStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: \n])\n";

    mTemplatesMap["eraseEl"] = "eraseEl([1_: fixed_: ])\n";
    mTemplatesMap["eraseElStr3"] = "eraseElStr3([\n\t1_: fixed_: ,\n\t2_: assign_: f_: ,\n\t3_: fixed_: \n])\n";
    mTemplatesMap["eraseElStr5"] = "eraseElStr5([\n\t1_: fixed_: ,\n\t2_: assign_: ,\n\t3_: fixed_: ,\n\t4_: assign_: f_: ,\n\t5_: fixed_: \n])\n";

    mTemplatesMap["selectYStr3"] = "selectYStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    mTemplatesMap["selectNStr3"] = "selectNStr3([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: \n], ,)\n";
    mTemplatesMap["selectYStr5"] = "selectYStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";
    mTemplatesMap["selectNStr5"] = "selectNStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: ,\n\tset1_: ,\n\tset2_: ,\n\tset3_: ,\n\tset4_: ,\n\tset5_: \n], ,)\n";

    mTemplatesMap["ifType"] = "ifType([\n\t1_: \n], ,)\n";
    mTemplatesMap["ifEq"] = "ifEq([\n\t1_: fixed_: ,\n\t2_: fixed_: \n], ,)\n";
    mTemplatesMap["ifCoin"] = "ifCoin([\n\t1_: ,\n\t2_: \n], ,)\n";
    mTemplatesMap["ifGr"] = "ifGr([\n\t1_: fixed_: \n\t2_: fixed_: \n], , )\n";
    mTemplatesMap["ifFormCount"] = "ifFormCount([\n\t1_: fixed_: ,\n\t2_: fixed_: \n], ,)\n";
    mTemplatesMap["ifVarAssign"] = "ifVarAssign([\n\t1_: fixed_: \n], ,)\n";

    mTemplatesMap["add"] = "add([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    mTemplatesMap["sub"] = "sub([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    mTemplatesMap["mult"] = "mult([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    mTemplatesMap["div"] = "div([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";
    mTemplatesMap["pow"] = "pow([\n\t1_: assign_: ,\t// result\n\t2_: fixed_: ,\n\t3_: fixed_: \n])\n";

    mTemplatesMap["callReturn"] = "callReturn([\n\t1_: fixed_: ,\n\t2_: fixed_: {[\n\t\t1_: fixed_: \n\t\t]}\n])";

    mTemplatesMap["label"] = "label()\n";

    QMap<QString, QString>::iterator it = mTemplatesMap.begin();
    for (; it != mTemplatesMap.end(); ++it) {
        QStandardItem *item = new QStandardItem(
                    QIcon(Config::pathMedia.absolutePath() + "/m4scp/icons/procedure.png"),
                    it.key());
        mod->appendRow(item);
        QModelIndex index = mod->indexFromItem(item);
        mod->setData(index, QVariant(it.value()), Qt::UserRole);
        mod->setData(index, QVariant(it.value()), Qt::ToolTipRole);
    }
}

//QString M4SCpCodeCompleter::resolveTemplate(const QString &keyword)
//{
//    QMap<QString, QString>::iterator it = mTemplatesMap.find(keyword);

//    if (it != mTemplatesMap.end())
//        return it.value();

//    return keyword;
//}
