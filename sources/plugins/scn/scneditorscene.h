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

#ifndef SCNEDITOR_H
#define SCNEDITOR_H

#include "scnfielditem.h"

#include <QGraphicsScene>
#include <QList>

class SCnEditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SCnEditorScene(QObject *parent = 0);
    virtual ~SCnEditorScene();

    /*! Append new scn-field after specified \p afterField
      * @param afterField Pointer to item, to insert new field after this one.
      * If \p afterField pointer is null, then new field will be added to the end
      * @return Return pointer to appended new field
      */
    SCnFieldItem* appendField(SCnFieldItem *afterField = 0);

    /*! Remove specified field from scene and destroy it.
      * @param field Pointer to field that need to be removed
      */
    void removeField(SCnFieldItem *field);

    /*! Move specified \p field to position after \p afterField
      * @param field Poiter to field that moves
      * @param aferField Pointer to field, that will be previsous for \p field
      */
    void moveField(SCnFieldItem *field, SCnFieldItem *afterField);

private:
    /*! Recalculate all fields positions
      */
    void updateFieldsPositions();

protected:
    //! Remove all fields from scene
    void removeAllFields();

protected:
    //! List of scn fields
    QList<SCnFieldItem*> mFields;
    //! Level horizontal offset in pixels
    quint32 mLevelOffset;
    //! Vertical distance between fields
    quint32 mLevelDistance;

signals:

public slots:
    //! Nofification about item change
    void itemChanged(SCnFieldItem *field, SCnFieldItem::ChangeType changeType);
};

#endif // SCNEDITOR_H
