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


#include "scgcommandobjecttypechage.h"

#include "../scgnode.h"
#include "../scgpair.h"
#include "../scgcontour.h"
#include "../scgbus.h"
#include "../scgscene.h"

SCgCommandObjectTypeChange::SCgCommandObjectTypeChange(SCgScene *scene,
                                                       SCgObject *object,
                                                       const QString &newType,
                                                       QUndoCommand *parent) :
        SCgBaseCommand(scene, object, parent),
        mNewType(newType)
{
    setText(QObject::tr("Change object's type"));
    mOldType = mObject->typeAlias();
}

SCgCommandObjectTypeChange::~SCgCommandObjectTypeChange()
{

}

void SCgCommandObjectTypeChange::redo()
{
    mObject->setTypeAlias(mNewType);
}

void SCgCommandObjectTypeChange::undo()
{
    mObject->setTypeAlias(mOldType);
}
