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

#ifndef SCNFIELDITEM_H
#define SCNFIELDITEM_H

#include <QObject>
#include <QGraphicsItem>

class SCnEditorScene;

class SCnFieldItem : public QObject,
                     public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    friend class SCnEditorScene;

protected:
    explicit SCnFieldItem();
    virtual ~SCnFieldItem();

public:
    enum FieldType
    {
        Empty = 0,
        GlobalIdtf, // global identifier
        Synonym,    // synonym field
        RelIn,      // Input binary relation
        RelOut,     // Ouput binary relation
        ArcIn,      // Included into set with global identifier
        ArcOut,     // Include described object as element into this set
        Subitem     // Item of binary relation sheaf
    };

    enum ChangeType
    {
        LevelChanged,
        TypeChanged,
        ValueChanged
    };

    enum FieldState
    {
        StateNormal = 0,
        StateHighlight,
        StateEdit,
        StateSelected
    };

public:
    //! Return true, if field is empty; otherwise - return flase
    bool isEmpty() const { return mType == Empty; }
    //! Return true, if specified field is possible to has subitems
    bool isSubitemsPossible() const;

    /*! Setup new level of item
      * @param level New level value
      */
    void setLevel(quint32 level);
    //! Return item level
    quint32 level() const;

protected:
    /*! Sets field type
      * @param type New field type
      */
    void setType(FieldType type);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    // hover events
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QSizeF mSize;
    FieldType mType;
    FieldState mState;

    //! Pointer to scene, that controls field
    SCnEditorScene *mEditorScene;
    //! Field level in hierarchy
    quint32 mLevel;

    //! Attribute value
    QString mAttribute;
    //! Field value
    QString mValue;

signals:
    /*! Signal that emits on item change @see ChangeType
      * @param field Pointer to changed scn-field
      * @param changeType Changes type
      */
    void changed(SCnFieldItem *field, ChangeType changeType);

public slots:
    //! Starts edit attribute
    void startEditAttr();
    //! Starts edit field value
    void startEditValue();
    //! Applies entered text for field attribute / value
    void applyEdit();
    //! Cancel edit without any changes
    void cancelEdit();
};

#endif // SCNFIELDITEM_H
