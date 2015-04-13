/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QUndoCommand>
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


