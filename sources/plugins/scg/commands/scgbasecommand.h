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

#ifndef SCGBASECOMMAND_H
#define SCGBASECOMMAND_H


#include <QtWidgets/QUndoCommand>
#include "../scgscene.h"

class SCgObject;

/*! Base scg command for
  */
class SCgBaseCommand : public QUndoCommand
{
public:
    explicit SCgBaseCommand(SCgScene *scene,
                            SCgObject *object,
                            QUndoCommand *parent = 0);
    virtual ~SCgBaseCommand();

    /*! Get pointer to scene we worked with.
      @return pointer to scene.
      */
    QGraphicsScene *getScene() const;

protected:
    //! Pointer to scene that used for command working
    SCgScene *mScene;
    //! Pointer to object that command affects to
    SCgObject *mObject;
};

#endif // SCGBASECOMMAND_H
