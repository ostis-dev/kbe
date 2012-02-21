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

#include <QStringListModel>

M4SCpCodeCompleter::M4SCpCodeCompleter(QObject *parent) :
    QCompleter(parent)
{
}

M4SCpCodeCompleter::~M4SCpCodeCompleter()
{
}

void M4SCpCodeCompleter::initDictionary()
{
    QStringListModel *model = new QStringListModel(this);

    QStringList keywords = M4SCpSyntax::operators();
    keywords << M4SCpSyntax::attributes() << M4SCpSyntax::ordinals();

    model->setStringList(keywords);
    setModel(model);


    // create templates
    mTemplatesMap["program"] = "program(,\n[[\n\t// constants\n]],\n[{\n}])\n\n\nreturn()\nend()";
    mTemplatesMap["return"] = "return()\n";
    mTemplatesMap["end"] = "end()\n";
    mTemplatesMap["sys_set_event_handler"] = "sys_set_event_handler([\n\t1_: fixed_: , // event\n\t2_: fixed_: , //procedure\n\t3_: fixed_: //pattern\n])";
}

QString M4SCpCodeCompleter::resolveTemplate(const QString &keyword)
{
    QMap<QString, QString>::iterator it = mTemplatesMap.find(keyword);

    if (it != mTemplatesMap.end())
        return it.value();

    return keyword;
}
