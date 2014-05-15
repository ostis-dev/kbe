/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#include "m4scpsyntax.h"

QStringList M4SCpSyntax::mOperatorsList = QStringList();
QStringList M4SCpSyntax::mAttributesList = QStringList();
QStringList M4SCpSyntax::mOrdinalsList = QStringList();

QString M4SCpSyntax::mEndOfWord = "~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="; // end of word

void M4SCpSyntax::initialize()
{
    mOperatorsList.clear();
    mOperatorsList
      << "add"         << "add_to_queue" << "call"
      << "contAssign"  << "contErase"    << "div"
      << "eraseElStr3" << "eraseElStr5"  << "eraseSetStr3"
      << "genElStr3"   << "genElStr5"    << "gsub"
      << "idtfErase"   << "idtfMove"     << "ifCoin"
      << "ifFormCont"  << "ifFormIdtf"   << "ifGr"
      << "ifNumber"    << "ifString"     << "ifType"
      << "init"        << "mult"         << "nop"
      << "print"       << "printEl"      << "printNl"
      << "program"     << "programSCP"   << "return"
      << "searchElStr5"<< "searchSetStr3"<< "searchSetStr5"
      << "selectNStr5" << "selectYStr3"  << "selectYStr5"
      << "callReturn"  << "eraseEl"      << "genEl"
      << "idtfAssign"  << "ifEq"         << "ifGrEq"
      << "ifVarAssign" << "pow"          << "procedure"
      << "searchElStr3"<<"selectNStr3"   << "sub"

      << "sys_close_segment"       << "sys_create_segment"
      << "sys_get_default_segment" << "sys_get_location"
      << "sys_open_dir_uri"        << "sys_open_segment"
      << "sys_send_message"        << "sys_set_default_segment"
      << "sys_spin_segment"        << "sys_unlink"
      << "varAssign"               << "varErase"
      << "wait_erase_element"      << "wait_gen_input_arc"
      << "wait_input_arc"          << "wait_output_arc"
      << "end"                     << "wait_recieve_message"
      << "sys_get_autosegment"     << "sys_open_dir"
      << "sys_open_segment_uri"    << "sys_set_event_handler"
      << "sys_wait"                << "waitReturn"
      << "wait_gen_output_arc"     << "label";


    mOrdinalsList.clear();
    mOrdinalsList
       << "1_"    << "2_" << "3_" << "4_"    << "5_"
       << "7_"    << "8_" << "9_" << "set1_" << "set2_"
       << "set4_" << "set5_" << "set6_" << "set7_" << "set8_"
       << "6_"    << "set3_" << "set9_" ;


    mAttributesList.clear();
    mAttributesList
        << "arc_"     << "const_"  << "else_"  << "segc_9_"
        << "fuz_"     << "goto_"   << "in_"    << "segc_4_"
        << "metavar_" << "neg_"    << "node_"  << "out_"
        << "prm_"     << "segc_1_" << "segc_2_"<< "segc_3_"
        << "segc_5_"  << "segc_6_" << "segc_7_"<< "segc_8_"
        << "then_"    << "undf_"   << "var_"   <<"elem_"
        << "f_"       << "init_"   << "pos_"   << "assign_"
        << "fixed_"  << "f_";
}

const QStringList& M4SCpSyntax::operators()
{
    return mOperatorsList;
}

const QStringList& M4SCpSyntax::attributes()
{
    return mAttributesList;
}

const QStringList& M4SCpSyntax::ordinals()
{
    return mOrdinalsList;
}


const QString& M4SCpSyntax::eow()
{
    return mEndOfWord;
}
