#include "scgstreamwriter.h"

#include "scgobject.h"
#include "scgnode.h"
#include "scgbus.h"
#include "scgcontour.h"
#include "scgpair.h"

#include "scgtextitem.h"

#include <QStack>
#include <QSet>

#include "scgconsts.h"

const QString SCgStreamWriter::END_LINE = "\n";
const QString SCgStreamWriter::END_PART_SENT = ";\n";
const QString SCgStreamWriter::END_SENT = ";;\n";
const QString SCgStreamWriter::TAB = "\t";

SCgStreamWriter::SCgStreamWriter() {}

void SCgStreamWriter::setOutputFiles(QIODevice *device, QIODevice *layoutDevice)
{
    scs.setDevice(device);
    scg.setDevice(layoutDevice);
}

void SCgStreamWriter::preprocess(QVector<SCgObject *> const & vec)
{
    for (auto obj : vec)
    {
        int parId = obj->parentId();
        if (parId != 0)
            children[parId].push_back(obj);
    }

    for (auto obj : vec)
    {
        if (obj->type() == SCgPair::Type)
        {
            SCgPair *pair = static_cast<SCgPair *>(obj);
            auto tmp = {pair->beginObject(), pair->endObject()};
            for (auto obj : tmp)
            {
                if (obj->type() == SCgPair::Type || obj->type() == SCgContour::Type)
                    deps[pair].push_back(obj);
            }
        }
    }
}


void SCgStreamWriter::writeOrdered(QVector<SCgObject *> const & vec)
{
    for (auto obj : vec)
        writeObjectWithDeps(obj);
}

void SCgStreamWriter::writeObjectWithDeps(SCgObject *obj)
{
    enum {STATUS_NOT_QUEUED, STATUS_QUEUED, STATUS_PROCESSED, STATUS_WRITTEN};

    if (dfsStatus[obj] == STATUS_WRITTEN) return;

    //! DFS
    QStack<SCgObject *> stack;
    stack.push_front(obj);
    dfsStatus[obj] = STATUS_QUEUED;
    while (!stack.isEmpty())
    {
        SCgObject *cur = stack.front();
        if (dfsStatus[cur] == STATUS_PROCESSED)
        {
            writeObject(cur);
            dfsStatus[cur] = STATUS_WRITTEN;
            stack.pop_front();
        }
        else
        {
            dfsStatus[cur] = STATUS_PROCESSED;
            if (deps.find(cur) == deps.end()) continue;
            for (auto dep : deps[cur])
            {
                if (dfsStatus[dep] == STATUS_NOT_QUEUED)
                {
                    stack.push_front(dep);
                    dfsStatus[dep] = STATUS_QUEUED;
                }
            }
        }
    }
}

void SCgStreamWriter::writeObject(SCgObject *obj)
{
    switch (obj->type())
    {
    case SCgNode::Type:
        writeNode(obj);
        break;
    case SCgPair::Type:
        writePair(obj);
        break;
    case SCgBus::Type:
        writeBus(obj);
        break;
    case SCgContour::Type:
        writeContour(obj);
        break;
    default:
        break;
    }
    scs.write(getIdtf(obj) + " => nrel_system_identifier: " + linkWrap(obj->idtfValue()) + END_SENT);
}

void SCgStreamWriter::writeNode(SCgObject *obj)
{
    SCgNode *node = static_cast<SCgNode*>(obj);

    QString idtf = getIdtf(obj);
    QString scgIdtf = getSCgIdtf(obj);

    //! scs
    if (node->contentType() != 0)
    {
        QString content;
        if (node->contentType() == 4)
            content = node->contentData().toByteArray().toBase64();
        else
            content = node->contentData().toString();
        scs.write(idtf + " = " + linkWrap(content) + END_SENT);
    }

    //! scg
    RelationValueVector values;
    values.push_back({ SCgConsts::NREL_SCG_REPRESENTATION, scgIdtf });
    writeSCgProperties(idtf, values);

    values.clear();
    values.push_back({ SCgConsts::NREL_X, linkWrap(node->scenePos().x()) });
    values.push_back({ SCgConsts::NREL_Y, linkWrap(node->scenePos().y()) });
    if (idtf != "")
        values.push_back({ SCgConsts::NREL_IDTF_POS, linkWrap(node->idtfPos()) });
    if (node->contentType() != 0)
    {
        values.push_back({ SCgConsts::NREL_CONTENT_TYPE, linkWrap(node->contentType()) });
        values.push_back({ SCgConsts::NREL_CONTENT_MIME_TYPE, linkWrap(node->contentMimeType()) });
        values.push_back({ SCgConsts::NREL_CONTENT_VISIBLE, node->isContentVisible() ? "1" : "0" });
        values.push_back({ SCgConsts::NREL_CONTENT_FILENAME, linkWrap(node->contentFileName()) });
    }
    writeSCgProperties(scgIdtf, values);
    scg.write(idtf + " <- " + convertType(obj->typeAlias()) + END_SENT);
}

void SCgStreamWriter::writePair(SCgObject *obj)
{
    QString idtf = getIdtf(obj);
    SCgPair *pair = static_cast<SCgPair*>(obj);

    QString scgIdtf = getSCgIdtf(obj);

    // scs
    SCgObject *begin = pair->beginObject(),
            *end = pair->endObject();
    if (begin->type() == SCgBus::Type) begin = static_cast<SCgBus*>(begin)->owner();
    if (end->type() == SCgBus::Type) end = static_cast<SCgBus*>(end)->owner();

    QString buf;
    QTextStream s(&buf);
    s << idtf << " = (" << getIdtf(begin) << " " <<
         convertType(obj->typeAlias()) << " " << getIdtf(end) << ")" << END_SENT;
    scs.write(s.readAll());

    //! scg
    begin = pair->beginObject();
    end = pair->endObject();
    buf = QString();
    s.setString(&buf);
    s << scgIdtf << " = (" << getSCgIdtf(begin) << " " <<
         convertType(obj->typeAlias()) << " " << getSCgIdtf(end) << ")" << END_SENT;
    scg.write(s.readAll());

    RelationValueVector values;
    values.push_back({ SCgConsts::NREL_SCG_REPRESENTATION, scgIdtf });
    writeSCgProperties(idtf, values);

    values.clear();
    values.push_back({ SCgConsts::NREL_START_RATIO, linkWrap(pair->beginDot()) });
    values.push_back({ SCgConsts::NREL_END_RATIO, linkWrap(pair->endDot()) });
    writeSCgProperties(scgIdtf, values);

    QVector<QPointF> points = pair->scenePoints();
    points.pop_back();
    points.pop_front();
    writePoints(scgIdtf, points, false);

    if (convertExtendedType(obj->typeAlias()) != "")
        scg.write(idtf + " <- " + convertExtendedType(obj->typeAlias()) + END_SENT);
}

void SCgStreamWriter::writeBus(SCgObject *obj)
{
    QString idtf = getIdtf(obj);
    SCgBus *bus = static_cast<SCgBus *>(obj);

    QString buf;
    QTextStream s(&buf);

    //! scg
    s << idtf + END_LINE;
    s << TAB + "<- " + SCgConsts::CONCEPT_SCG_BUS + END_PART_SENT;
    s << TAB + "=> " + SCgConsts::NREL_OWNER + ": " + getSCgIdtf(bus->owner()) + END_SENT;
    scg.write(s.readAll());

    QVector<QPointF> points = bus->scenePoints();
    points.pop_front();
    writePoints(idtf, points, false);
}

void SCgStreamWriter::writeContour(SCgObject *obj)
{
    QString idtf = getIdtf(obj);
    SCgContour *contour = static_cast<SCgContour *>(obj);

    QString buf;
    QTextStream s(&buf);

    QVector<QPointF> points = contour->scenePoints();
    writePoints(idtf, points, true);

    scs.write(idtf + " = [*" + END_LINE);
    scs.indent.append(TAB);
    writeOrdered(children[obj->id()]);
    scs.indent.chop(1);
    scs.write("*]" + END_SENT);

    auto vec = children[obj->id()];
    s << idtf + " <- " + SCgConsts::CONCEPT_SCG_CONTOUR + END_SENT;
    if (vec.size() > 0)
    {
        s << idtf << " => " + SCgConsts::NREL_INCLUDING + ": {" << END_LINE;
        for (int i = 0; i < vec.size() - 1; i++)
            s << TAB << getSCgIdtf(vec[i]) << END_PART_SENT;
        s << TAB << getSCgIdtf(vec[vec.size() - 1]) << END_LINE;
        s << "}" << END_SENT;
    }
    scg.write(s.readAll());
}

void SCgStreamWriter::writeSCgProperties(QString const & idtf, RelationValueVector const & relations)
{
    int size = relations.size();
    //assert(size != 0);
    QString buf;
    QTextStream s(&buf);
    s << idtf << END_LINE;
    for (int i = 0; i < size; i++)
    {
        auto relPair = relations[i];
        s << TAB << "=> " << relPair.first << ": " << relPair.second << (i == size - 1 ? END_SENT : END_PART_SENT);
    }
    scg.write(s.readAll());
}

void SCgStreamWriter::writePoints(QString const & idtf, QVector<QPointF> const & points, bool cyclic)
{
    if (points.size() == 0) return;
    QString buf;
    QTextStream s(&buf);

    int size = points.size();
    QVector<QString> names(size);
    for (int i = 0; i < size; i++)
        names[i] = getTemp("point");

    s << idtf + " => " + SCgConsts::NREL_DECOMPOSITION + ": {" + END_LINE;
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            s << TAB + names[i] + END_PART_SENT;
        else
            s << TAB + names[size - 1] + END_LINE;
    }
    s << "}" + END_SENT;
    scg.write(s.readAll());
    for (int i = 0; i < size; i++)
    {
        RelationValueVector values;
        values.push_back({ SCgConsts::NREL_X, linkWrap(points.at(i).x()) });
        values.push_back({ SCgConsts::NREL_Y, linkWrap(points.at(i).y()) });
        if (i > 0)
            values.push_back({ SCgConsts::NREL_BASIC_SEQUENCE, names[i - 1] });
        else if (cyclic)
            values.push_back({ SCgConsts::NREL_BASIC_SEQUENCE, names[size - 1] });

        writeSCgProperties(names[i], values);
    }
}

QString SCgStreamWriter::linkWrap(QString const & idtf)
{
    return "[" + idtf + "]";
}

QString SCgStreamWriter::linkWrap(int number)
{
    return "[" + QString::number(number) + "]";
}

QString SCgStreamWriter::linkWrap(double number)
{
    return "[" + QString::number(number) + "]";
}

QString SCgStreamWriter::convertType(QString const & type)
{
    static const QHash<QString, QString> types =
    {
        //! not define
        { "node/-/-/not_define", SCgConsts::SC_NODE_NOT_DEFINE },

        //! const perm
        { "node/const/perm/general", "sc_node" },
        { "node/const/perm/terminal", "sc_node_abstract" },
        { "node/const/perm/struct", "sc_node_struct" },
        { "node/const/perm/tuple", "sc_node_tuple" },
        { "node/const/perm/role", "sc_node_role_relation" },
        { "node/const/perm/relation", "sc_node_norole_relation" },
        { "node/const/perm/group", "sc_node_class" },
        { "node/const/perm/super_group", SCgConsts::SC_NODE_SUPER_GROUP },

        //! var perm
        { "node/var/perm/general", "sc_node" },
        { "node/var/perm/terminal", "sc_node_abstract" },
        { "node/var/perm/struct", "sc_node_struct" },
        { "node/var/perm/tuple", "sc_node_tuple" },
        { "node/var/perm/role", "sc_node_role_relation" },
        { "node/var/perm/relation", "sc_node_norole_relation" },
        { "node/var/perm/group", "sc_node_class" },
        { "node/var/perm/super_group", SCgConsts::SC_NODE_SUPER_GROUP_VAR },

        //! meta perm
        { "node/meta/perm/general", SCgConsts::SC_NODE_META },
        { "node/meta/perm/terminal", SCgConsts::SC_NODE_ABSTRACT_META },
        { "node/meta/perm/struct", SCgConsts::SC_NODE_STRUCT_META },
        { "node/meta/perm/tuple", SCgConsts::SC_NODE_TUPLE_META },
        { "node/meta/perm/role", SCgConsts::SC_NODE_ROLE_RELATION_META },
        { "node/meta/perm/relation", SCgConsts::SC_NODE_NOROLE_RELATION_META },
        { "node/meta/perm/group", SCgConsts::SC_NODE_CLASS_META },
        { "node/meta/perm/super_group", SCgConsts::SC_NODE_SUPER_GROUP_META },

        //! const temp
        { "node/const/temp/general", SCgConsts::SC_NODE_TEMP },
        { "node/const/temp/terminal", SCgConsts::SC_NODE_ABSTRACT_TEMP },
        { "node/const/temp/struct", SCgConsts::SC_NODE_STRUCT_TEMP },
        { "node/const/temp/tuple", SCgConsts::SC_NODE_TUPLE_TEMP },
        { "node/const/temp/role", SCgConsts::SC_NODE_ROLE_RELATION_TEMP },
        { "node/const/temp/relation", SCgConsts::SC_NODE_NOROLE_RELATION_TEMP },
        { "node/const/temp/group", SCgConsts::SC_NODE_CLASS_TEMP },
        { "node/const/temp/super_group", SCgConsts::SC_NODE_SUPER_GROUP_TEMP },

        //! var temp
        { "node/var/temp/general", SCgConsts::SC_NODE_VAR_TEMP },
        { "node/var/temp/terminal", SCgConsts::SC_NODE_ABSTRACT_VAR_TEMP },
        { "node/var/temp/struct", SCgConsts::SC_NODE_STRUCT_VAR_TEMP },
        { "node/var/temp/tuple", SCgConsts::SC_NODE_TUPLE_VAR_TEMP },
        { "node/var/temp/role", SCgConsts::SC_NODE_ROLE_RELATION_VAR_TEMP },
        { "node/var/temp/relation", SCgConsts::SC_NODE_NOROLE_RELATION_VAR_TEMP },
        { "node/var/temp/group", SCgConsts::SC_NODE_CLASS_VAR_TEMP },
        { "node/var/temp/super_group", SCgConsts::SC_NODE_SUPER_GROUP_VAR_TEMP },

        //! meta temp
        { "node/meta/temp/general", SCgConsts::SC_NODE_META_TEMP },
        { "node/meta/temp/terminal", SCgConsts::SC_NODE_ABSTRACT_META_TEMP },
        { "node/meta/temp/struct", SCgConsts::SC_NODE_STRUCT_META_TEMP },
        { "node/meta/temp/tuple", SCgConsts::SC_NODE_TUPLE_META_TEMP },
        { "node/meta/temp/role", SCgConsts::SC_NODE_ROLE_RELATION_META_TEMP },
        { "node/meta/temp/relation", SCgConsts::SC_NODE_NOROLE_RELATION_META_TEMP },
        { "node/meta/temp/group", SCgConsts::SC_NODE_CLASS_META_TEMP },
        { "node/meta/temp/super_group", SCgConsts::SC_NODE_SUPER_GROUP_META_TEMP },


        { "pair/const/-/perm/noorient", "<=>" },
        { "pair/const/-/perm/orient", "=>" },
        { "pair/const/fuz/perm/orient/membership", "-/>" },
        { "pair/const/neg/perm/orient/membership", "-|>" },
        { "pair/const/pos/perm/orient/membership", "->" },
        { "pair/const/fuz/temp/orient/membership", "~/>" },
        { "pair/const/neg/temp/orient/membership", "~|>" },
        { "pair/const/pos/temp/orient/membership", "~>" },
        { "pair/const/-/temp/noorient", "<=>" }, //not supported
        { "pair/const/-/temp/orient", "=>" }, //not supported

        { "pair/var/-/perm/noorient", "_<=>" },
        { "pair/var/-/perm/orient", "_=>" },
        { "pair/var/fuz/perm/orient/membership", "_-/>" },
        { "pair/var/neg/perm/orient/membership", "_-|>" },
        { "pair/var/pos/perm/orient/membership", "_->" },
        { "pair/var/fuz/temp/orient/membership", "_~/>" },
        { "pair/var/neg/temp/orient/membership", "_~|>" },
        { "pair/var/pos/temp/orient/membership", "_~>" },
        { "pair/var/-/temp/noorient", ">" }, //not supported
        { "pair/var/-/temp/orient", ">" }, //not supported

        { "pair/meta/-/perm/noorient", ">" }, //not supported
        { "pair/meta/-/perm/orient", ">" }, //not supported
        { "pair/meta/-/temp/noorient", ">" }, //not supported
        { "pair/meta/-/temp/orient", ">" }, //not supported
        { "pair/meta/pos/perm/orient/membership", ">" }, //not supported
        { "pair/meta/pos/temp/orient/membership", ">" }, //not supported
        { "pair/meta/neg/perm/orient/membership", ">" }, //not supported
        { "pair/meta/neg/temp/orient/membership", ">" }, //not supported
        { "pair/meta/fuz/perm/orient/membership", ">" }, //not supported
        { "pair/meta/fuz/temp/orient/membership", ">" }, //not supported

        { "pair/-/-/-/orient", ">" },
        { "pair/-/-/-/noorient", "<>" },
    };

    return types[type];
}

QString SCgStreamWriter::convertExtendedType(QString const & type)
{
    static const QHash<QString, QString> types =
    {
        { "pair/const/-/temp/noorient", SCgConsts::SC_PAIR_CONST_TEMP_NOORIENT },
        { "pair/const/-/temp/orient", SCgConsts::SC_PAIR_CONST_TEMP_ORIENT},

        { "pair/var/-/temp/noorient", SCgConsts::SC_PAIR_VAR_TEMP_NOORIENT },
        { "pair/var/-/temp/orient", SCgConsts::SC_PAIR_VAR_TEMP_ORIENT },

        { "pair/meta/-/perm/noorient", SCgConsts::SC_PAIR_META_PERM_NOORIENT },
        { "pair/meta/-/perm/orient", SCgConsts::SC_PAIR_META_PERM_ORIENT },
        { "pair/meta/-/temp/noorient", SCgConsts::SC_PAIR_META_TEMP_NOORIENT },
        { "pair/meta/-/temp/orient", SCgConsts::SC_PAIR_META_TEMP_ORIENT },
        { "pair/meta/pos/perm/orient/membership", SCgConsts::SC_PAIR_META_POS_PERM_MEMBERSHIP },
        { "pair/meta/pos/temp/orient/membership", SCgConsts::SC_PAIR_META_POS_TEMP_MEMBERSHIP },
        { "pair/meta/neg/perm/orient/membership", SCgConsts::SC_PAIR_META_NEG_PERM_MEMBERSHIP },
        { "pair/meta/neg/temp/orient/membership", SCgConsts::SC_PAIR_META_NEG_TEMP_MEMBERSHIP },
        { "pair/meta/fuz/perm/orient/membership", SCgConsts::SC_PAIR_META_FUZ_PERM_MEMBERSHIP },
        { "pair/meta/fuz/temp/orient/membership", SCgConsts::SC_PAIR_META_FUZ_TEMP_MEMBERSHIP },
    };

    return types[type];
}

SCgStreamWriter::StreamWriter::StreamWriter()
{
}

SCgStreamWriter::StreamWriter::StreamWriter(QIODevice *device) : stream(device)
{
}

void SCgStreamWriter::StreamWriter::write(QString s)
{
    QTextStream temp(&s);
    while (!temp.atEnd())
        stream << indent << temp.readLine() << END_LINE;
}

void SCgStreamWriter::StreamWriter::setDevice(QIODevice *device)
{
    stream.setDevice(device);
}

QString SCgStreamWriter::getIdtf(QString const & base)
{
    return base + QString::number(count[base]++);
}

QString SCgStreamWriter::makeAlias(QString const & base)
{
    return "@" + base;
}

QString SCgStreamWriter::makeTemp(QString const & base)
{
    return ".." + base;
}

QString SCgStreamWriter::getIdtf(SCgObject *obj)
{
    //! Check if idtf is already defined.
    uint64_t id = obj->id();
    if (names.find(id) != names.end()) return names[id];

    //! Define idtf when it is not defined
    QString name;
    if (obj->type() == SCgNode::Type)
    {
        SCgNode *node = static_cast<SCgNode*>(obj);
        if (node->contentType() != 0)
        {
            name = getAlias("link");
            names[id] = name;
        }
        else {
            SCgAlphabet &alphabet = SCgAlphabet::getInstance();
            QStringList splittedAlias = obj->typeAlias().split("/");
            bool isVar = splittedAlias.at(1) == alphabet.aliasFromConstCode(SCgAlphabet::Var);
            if (isVar)
                names[id] = getTemp("_node");
            else
                names[id] = getTemp("node");
        }
    }
    else if (obj->type() == SCgPair::Type)
        names[id] = getAlias("pair");
    else if (obj->type() == SCgBus::Type)
        names[id] = getTemp("bus");
    else if (obj->type() == SCgContour::Type)
        names[id] = getAlias("contour");
    return names[id];
}

QString SCgStreamWriter::getSCgIdtf(SCgObject *obj)
{
    if (obj->type() != SCgNode::Type && obj->type() != SCgPair::Type)
        return getIdtf(obj);

    uint64_t id = obj->id();
    if (scgNames.find(id) == scgNames.end())
    {
        if (obj->type() == SCgNode::Type) scgNames[id] = getTemp("scgNode");
        if (obj->type() == SCgPair::Type) scgNames[id] = getAlias("scgPair");
    }

    return scgNames[id];
}

QString SCgStreamWriter::getAlias(QString const & base)
{
    return makeAlias(getIdtf(base));
}

QString SCgStreamWriter::getTemp(QString const & base)
{
    return makeTemp(getIdtf(base));
}
