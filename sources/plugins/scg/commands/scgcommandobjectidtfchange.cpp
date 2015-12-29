/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcommandobjectidtfchange.h"

#include "scgnode.h"
#include "scgpair.h"

SCgCommandObjectIdtfChange::SCgCommandObjectIdtfChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newIdtf,
                                                       QUndoCommand *parent)
        : SCgBaseCommand(scene, object, parent)
        , mNewIdtf(newIdtf)
{
    setText(QObject::tr("Change object's identifier"));
    mOldIdtf = mObject->idtfValue();
}

SCgCommandObjectIdtfChange::~SCgCommandObjectIdtfChange()
{

}

void SCgCommandObjectIdtfChange::redo()
{
    mObject->setIdtfValue(mNewIdtf);
    tryUpdateType(mNewIdtf);

    SCgBaseCommand::redo();
}

void SCgCommandObjectIdtfChange::undo()
{
    mObject->setIdtfValue(mOldIdtf);
    tryUpdateType(mOldIdtf);

    SCgBaseCommand::undo();
}

void SCgCommandObjectIdtfChange::tryUpdateType(QString const & idtf)
{
    // check if need to change object type
    if (!idtf.isEmpty())
    {
        SCgAlphabet const & alphabet = SCgAlphabet::getInstance();
        bool typeChanged = false;
        QStringList splittedAlias = mObject->typeAlias().split("/");
        if (mObject->type() == SCgNode::Type || mObject->type() == SCgPair::Type)
        {
            if (idtf.startsWith('_') && splittedAlias.at(1) != alphabet.aliasFromConstCode(SCgAlphabet::Var))
            {
                splittedAlias[1] = alphabet.aliasFromConstCode(SCgAlphabet::Var);
                typeChanged = true;
            }
        }

        // check possible node types
        if (mObject->type() == SCgNode::Type)
        {
            // role relation
            if (idtf.endsWith('\''))
            {
                splittedAlias[2] = alphabet.aliasFromStructCode(SCgAlphabet::StructType_Role);
                typeChanged = true;
            }

            // binary relation
            if (idtf.endsWith('*'))
            {
                splittedAlias[2] = alphabet.aliasFromStructCode(SCgAlphabet::StructType_Relation);
                typeChanged = true;
            }
        }

        // if type changed, then make new type alias and setup it to object
        if (typeChanged)
        {
            QString newType;
            for (int i = 0; i < splittedAlias.size(); ++i)
                newType.append(splittedAlias.at(i) + "/");

            mObject->setTypeAlias(newType.mid(0, newType.size() - 1));
        }
    }
}
