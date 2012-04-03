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

#ifndef SCGCOMMANDINSERT_H
#define SCGCOMMANDINSERT_H

#include <QObject>
#include "scgbasecommand.h"

/*! Object insertion command
  */
class SCgCommandInsert : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param scene          Pointer to SCgScene that will be used for command working
      @param objList        List of inserted objects
      @param parentContour  Pointer to parent contour (if 0 then parent is scene).
      @param parent         Pointer to parent command
      */
    explicit SCgCommandInsert(SCgScene *scene,
                              QList<SCgObject*> objList,
                              SCgContour* parentContour,
                              QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandInsert();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();
    //! List of inserted objects
    QList<SCgObject*> mList;
    //! Parent contour
    SCgContour* mParent;
private slots:

    void objectFromListDestroyed(QObject* obj);
};

#endif // SCGCOMMANDINSERT_H
