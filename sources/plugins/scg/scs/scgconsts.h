#pragma once

#include <memory>
#include <QString>

class SCgConsts
{
public:
    static const QString CONCEPT_SCG_CONTOUR;
    static const QString NREL_SCG_REPRESENTATION;
    static const QString NREL_INCLUDING;
    static const QString CONCEPT_SCG_BUS;
    static const QString NREL_X;
    static const QString NREL_Y;
    static const QString NREL_IDTF_POS;
    static const QString NREL_CONTENT_TYPE;
    static const QString NREL_CONTENT_MIME_TYPE;
    static const QString NREL_CONTENT_VISIBLE;
    static const QString NREL_CONTENT_FILENAME;
    static const QString NREL_START_RATIO;
    static const QString NREL_END_RATIO;
    static const QString NREL_DECOMPOSITION;
    static const QString NREL_OWNER;
    static const QString NREL_BASIC_SEQUENCE;

    //extended types
    //nodes
    static const QString SC_NODE_NOT_DEFINE;
    static const QString SC_NODE_SUPER_GROUP;
    static const QString SC_NODE_SUPER_GROUP_VAR;
    static const QString SC_NODE_META;
    static const QString SC_NODE_ABSTRACT_META;
    static const QString SC_NODE_STRUCT_META;
    static const QString SC_NODE_TUPLE_META;
    static const QString SC_NODE_ROLE_RELATION_META;
    static const QString SC_NODE_NOROLE_RELATION_META;
    static const QString SC_NODE_CLASS_META;
    static const QString SC_NODE_SUPER_GROUP_META;
    static const QString SC_NODE_TEMP;
    static const QString SC_NODE_ABSTRACT_TEMP;
    static const QString SC_NODE_STRUCT_TEMP;
    static const QString SC_NODE_TUPLE_TEMP;
    static const QString SC_NODE_ROLE_RELATION_TEMP;
    static const QString SC_NODE_NOROLE_RELATION_TEMP;
    static const QString SC_NODE_CLASS_TEMP;
    static const QString SC_NODE_SUPER_GROUP_TEMP;
    static const QString SC_NODE_VAR_TEMP;
    static const QString SC_NODE_ABSTRACT_VAR_TEMP;
    static const QString SC_NODE_STRUCT_VAR_TEMP;
    static const QString SC_NODE_TUPLE_VAR_TEMP;
    static const QString SC_NODE_ROLE_RELATION_VAR_TEMP;
    static const QString SC_NODE_NOROLE_RELATION_VAR_TEMP;
    static const QString SC_NODE_CLASS_VAR_TEMP;
    static const QString SC_NODE_SUPER_GROUP_VAR_TEMP;
    static const QString SC_NODE_META_TEMP;
    static const QString SC_NODE_ABSTRACT_META_TEMP;
    static const QString SC_NODE_STRUCT_META_TEMP;
    static const QString SC_NODE_TUPLE_META_TEMP;
    static const QString SC_NODE_ROLE_RELATION_META_TEMP;
    static const QString SC_NODE_NOROLE_RELATION_META_TEMP;
    static const QString SC_NODE_CLASS_META_TEMP;
    static const QString SC_NODE_SUPER_GROUP_META_TEMP;

    //pairs
    static const QString SC_PAIR_CONST_TEMP_NOORIENT;
    static const QString SC_PAIR_CONST_TEMP_ORIENT;
    static const QString SC_PAIR_VAR_TEMP_NOORIENT;
    static const QString SC_PAIR_VAR_TEMP_ORIENT;
    static const QString SC_PAIR_META_PERM_NOORIENT;
    static const QString SC_PAIR_META_PERM_ORIENT;
    static const QString SC_PAIR_META_TEMP_NOORIENT;
    static const QString SC_PAIR_META_TEMP_ORIENT;
    static const QString SC_PAIR_META_POS_PERM_MEMBERSHIP;
    static const QString SC_PAIR_META_POS_TEMP_MEMBERSHIP;
    static const QString SC_PAIR_META_NEG_PERM_MEMBERSHIP;
    static const QString SC_PAIR_META_NEG_TEMP_MEMBERSHIP;
    static const QString SC_PAIR_META_FUZ_PERM_MEMBERSHIP;
    static const QString SC_PAIR_META_FUZ_TEMP_MEMBERSHIP;
};
