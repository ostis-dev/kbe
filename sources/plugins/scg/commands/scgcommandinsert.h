/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
                              QString layerName,
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
    QString layerName;
private slots:

    void objectFromListDestroyed(QObject* obj);
};


