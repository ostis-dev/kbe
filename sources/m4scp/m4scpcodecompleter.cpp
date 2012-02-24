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
#include <QDebug>

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

    // create templates
    mTemplatesMap["program"] = "program(,\n[[\n\t// constants\n]],\n[{\n}])\n\n\nreturn()\nend()";
    mTemplatesMap["return"] = "return()\n";
    mTemplatesMap["end"] = "end()\n";
    mTemplatesMap["sys_set_event_handler"] = "sys_set_event_handler([\n\t1_: fixed_: , // event\n\t2_: fixed_: , //procedure\n\t3_: fixed_: //pattern\n])";
    mTemplatesMap["sys_get_location"] = "sys_get_location([\n\t1_: fixed_: ,// sc-element\n\t2_: assign_: //segment\n])";
    mTemplatesMap["sys_open_segment"] = "sys_open_segment([1_: fixed_: ])";
    mTemplatesMap["sys_set_default_segment"] = "sys_set_default_segment([1_: fixed_: ])";

    mTemplatesMap["printEl"] = "printEl([1_: fixed_: ])";

    mTemplatesMap["searchElStr3"] = "searchElStr3([\n\t1_: ,\n\t2_: ,\n\t3_: \n\t], ,)";
    mTemplatesMap["searchElStr5"] = "searchElStr5([\n\t1_: ,\n\t2_: ,\n\t3_: ,\n\t4_: ,\n\t5_: \n\t], ,)";

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
