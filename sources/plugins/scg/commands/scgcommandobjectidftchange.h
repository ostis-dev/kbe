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


#ifndef SCGCOMMANDOBJECTIDFTCHANGE_H
#define SCGCOMMANDOBJECTIDFTCHANGE_H

#include <QUndoCommand>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QPair>

#include "../scgcontent.h"
#include "../scgpointobject.h"
#include "../scgscene.h"


class SCgObject;
class SCgNode;
class SCgPair;
class SCgContour;
class SCgBus;

class QGraphicsScene;
class QGraphicsItem;

/*! Object identification change command
  */
class SCgCommandObjectIdtfChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to object for identifier changing
      @param    newIdtf New object identifier
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectIdtfChange(SCgScene *scene,
                                        SCgObject *object,
                                        const QString &newIdtf,
                                        QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectIdtfChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Old identifier
    QString mOldIdtf;
    //! New identifier
    QString mNewIdtf;
};

#endif // SCGCOMMANDOBJECTIDFTCHANGE_H
