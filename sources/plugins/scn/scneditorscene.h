/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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
#include "scninputdialog.h"

#include <QGraphicsScene>
#include <QList>

class SCnEditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SCnEditorScene(QObject *parent = 0);
    virtual ~SCnEditorScene();

    /*! Append new scn-field after specified \p afterField
      * @param field Pointer to appended scn-field
      * @param afterField Pointer to item, to insert new field after this one.
      * If \p afterField pointer is null, then new field will be added to the end
      * @return Return pointer to appended new field
      */
    SCnFieldItem* appendField(SCnFieldItem *field, SCnFieldItem *afterField = 0);

    /*! Remove specified field from scene and destroy it.
      * @param field Pointer to field that need to be removed
      */
    void removeField(SCnFieldItem *field);

    /*! Get pointer to field, that located after specified \p field
      * @param field Pointer to scn-field for get next
      * @param withLevelChange true, if level changing allowed
      * @return Return pointer to scn-field, that located after \p field.
      * If \p field is a first field, then return 0
      */
    SCnFieldItem* nextField(SCnFieldItem *field, bool withLevelChange);

    /*! Get pointer to field, that located before specified \p field
      * @param field Pointer to scn-field for get previous
      * @param withLevelChange true, if level changing allowed
      * @return Return pointer to scn-field, that located before \p field
      * If \p field is a last field, then return 0
      */
    SCnFieldItem* prevField(SCnFieldItem *field, bool withLevelChange);

    /*!
      * @param field Pointer to scn-field for get parent
      * @return Return pointer to parent scn-field
      * If \p field is the root field, then return 0
      */
    SCnFieldItem* parentField(SCnFieldItem *field);

    /*!
      * @param field Pointer to scn-field for get child
      * @return Return pointer to the first child scn-field
      * If \p field is a leaf field, then return 0
      */
    SCnFieldItem* childField(SCnFieldItem *field);


    //! Select specified \p field
    void selectField(SCnFieldItem *field);
    //! Move up specified \p field
    void moveFieldUp(SCnFieldItem *field);
    //! Move down specified \p field
    void moveFieldDown(SCnFieldItem *field);
    //! Swap specified \p field_1 with specified \p field_2
    void swapFields(SCnFieldItem *field_1, SCnFieldItem *field_2);
    //! Add new field as child of \p field
    void insertField(SCnFieldItem *field);

private:
    //! Unselect all selected items
    void unselectItems();

    //! Recalculate all fields positions
    void updateFieldsPositions();

protected:
    void keyPressEvent(QKeyEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    //! Remove all fields from scene
    void removeAllFields();

public:
    //! Nofification about item change
    void itemChanged(SCnFieldItem *field, SCnFieldItem::ChangeType changeType);

protected:
    typedef QVector<SCnFieldItem*> FieldItems;
    FieldItems mFields;
    //! Level horizontal offset in pixels
    quint32 mLevelOffset;
    //! Vertical distance between fields
    quint32 mLevelDistance;

    //! Dialog for input SCn-text
    SCnInputDialog *inputDialog;

signals:

public slots:
    void setTextForSelectedField(const QString &text);
};

#endif // SCNEDITOR_H
