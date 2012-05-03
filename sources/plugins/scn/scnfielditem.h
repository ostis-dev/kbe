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
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QCompleter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>

class SCnEditorScene;

class SCnFieldItem : public QObject,
                     public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    friend class SCnEditorScene;

protected:
    explicit SCnFieldItem(QObject *parent = 0);
    virtual ~SCnFieldItem();

public:
    enum ChangeType
    {
        ParentChanged,
        ValueChanged,
        StateChanged,
        BoundChanged
    };

    enum FieldState
    {
        StateNormal = 0,
        StateHighlight,
        StateEdit,
        StateSelected
    };

    enum { Type = UserType + 1 };

    int type() const { return Type; }

    //! Check if specified item type is an scn field item
    static bool isSCnFieldType(int type);

public:
    //! Return true, if field is empty; otherwise - return flase
    bool isEmpty() const { return mValue.isEmpty(); }
    //! Return true, if this field is possible to has subitems
    virtual bool isSubitemsPossible() const = 0;
    //! Return true, if this field can be a root
    virtual bool canBeRoot() const = 0;
    //! Return true, if this field can be at first level
    virtual bool canBeAtZeroLevel() const = 0;
    //! Return y offset for first child item
    virtual qreal childsOffset() const = 0;
    //! Update on childs changed. Called when any child changed, or added/removed
    virtual void updateOnChilds();
    virtual QRectF getChildrenBoundingRect() const;


    //! Return current state
    FieldState state() const { return mState; }

    /*! Set new value for field
      * @param value New value
      */
    void setValue(const QString &value);
    //! Return field value
    const QString& value() const { return mValue; }


protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void keyPressEvent(QKeyEvent *event);

    ////////
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//////////////



    // hover events
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    /*! Function to notify scene about item change
      * @param field Pointer to changed scn-field
      * @param changeType Changes type
      */
    void changed(SCnFieldItem *field, ChangeType changeType);
    void changeValue();
    void selfDeleting();

protected:
    FieldState mState;

    //! Pointer to scene, that controls field
    SCnEditorScene *mEditorScene;
    //! Attribute value
    QString mAttribute;
    //! Field value
    QString mValue;
    QMenu * mMenu;
    QAction * addNewItemAct;
    QAction * deleteItemAct;
    QAction * editItemAct;

signals:


public slots:
    //! Starts edit field value
    void startEdit();
    //! Applies entered text for field attribute / value
    void applyEdit();
    //! Cancel edit without any changes
    void cancelEdit();
    void AddNewSlot();
    void EditSlot();
    void DeleteSlot();
};

#endif // SCNFIELDITEM_H
