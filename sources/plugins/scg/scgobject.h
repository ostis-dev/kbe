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

#ifndef SCGOBJECT_H
#define SCGOBJECT_H

#include <QObject>
#include <QGraphicsItem>

#include "scgalphabet.h"
#include "scgabstractobjectbuilder.h"

class SCgScene;

class SCgObject : public QObject, public QGraphicsItem
{
Q_OBJECT
Q_INTERFACES(QGraphicsItem)

public:
    enum { Type = UserType + 1 };
    virtual int type() const = 0;

    explicit SCgObject(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgObject();

    //! Check if type is an scg-object type
    static bool isSCgObjectType(int type);

    //! Check if type is an scg-pointObject type
    static bool isSCgPointObjectType(int type);

public:
    typedef QList<SCgObject*> SCgObjectList;

    //! Add connected object
    void addConnectedObject(SCgObject *object);
    //! Removes given connected object.
    void removeConnectedObject(SCgObject *object);
    //! @return If given object @p object is connected to this object returns true.
    bool haveConnectedObject(SCgObject *object) const;
    //! Update (repaint) connected objects
    virtual void updateConnected();

    /*! Method to update object position.
      It calls when object need to recalculate it position.
      */
    virtual void updatePosition() = 0;

    /*! Method to set text idtf for object.
      */
    virtual void setIdtfValue(const QString &idtf);
    QString idtfValue() const;

    /*! Get cross.
      @param  from Point we are building line intersection from. It should have scene coordimates.
      @param  dot Relative dot position.
      @return Returns intersaction point for a line from specified point to
      object center. This point is in scene coordinates.
      */
    virtual QPointF cross(const QPointF &from, float dot) const = 0;

    /*! Count dot position on object.
      Counts dot relative position by scene point.
      @param point  Point for calculate dot pos on object. Must be in
                    scene coordinates.
      */
    virtual float dotPos(const QPointF &point) const = 0;

    /*! Set color
      */
    void setColor(QColor color);

    /*! Get color
      */
    QColor color() const;

    /*! Show/hide boudngin box
        \param value    Visibility flag value.
      */
    void setBoundingBoxVisible(bool value);
    //! Check if bounding box is visible
    bool isBoundingBoxVisible() const;
//////////////////////////
/* Working with types */
public:
    // Working with types
    virtual void setTypeAlias(const QString &typeAlias);
    QString typeAlias() const;

    // Const type
    SCgAlphabet::SCgConstType getConstType() const
    {
        return mConstType;
    }

protected:
    QString mTypeAlias;
    SCgAlphabet::SCgConstType mConstType;
////////////////////////

protected:
    // hover events
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*! Connected object remove notification.
      That method calls in connected object to notify it,
      that this one is deleting. As parameter it takes object
      that is deleting.
      When you immplementing this method, you need to remove all pointers
      and references to deletion object.
      */
    virtual void objectDelete(SCgObject *object) = 0;


public:
    /*! Check if object is dead.
      Dead object means that it removed from scene, but still available in memory.
      */
    bool isDead() const;

    /*! Set object dead flag
      \param dead Dead flag value.
      */
    void setDead(bool dead);

    /*! Delete object.
      \param list List of deleted objects.
      @note Object removes from scene, but still alive in memory. It removes from memory by
            undo command objects.
      */
    virtual void del(QList<SCgObject*> &delList);

    /*! Restore object after deletion
      \param scene  Scene for item restore.
      @note Object added to scene.
      */
    virtual void undel(SCgScene *scene);

    /*!
     * @return unique identifier of this object in current environment.
     */
    long id() const
    {
        return reinterpret_cast<long>(this);
    }

    long parentId() const
    {
        return ((SCgObject*)this->parentItem())->id();
    }

    /**
      * @brief Get full copy of SCgObject. Returned result depends on type of SCgObject
      * @param objList Reference to the list of objects that have been cloned
      */
    virtual void clone(SCgObjectList& objMap) = 0;

protected:
    //! Main color
    QColor mColor;

    //! List of connected objects
    SCgObjectList mConnectedObjects;

    //! Bounding box drawing flag
    bool mIsBoundingBoxVisible;

    //! Text idtf value
    QString mIdtfValue;

    //! Text item
    QGraphicsTextItem *mTextItem;

    //! Dead flag
    bool mIsDead;

    //! true, if parent about to change.
    bool mParentChanging;

protected:
    friend class GwfStreamWriter;
    const QGraphicsTextItem* textItem() const{return mTextItem;}

};


#endif // SCGOBJECT_H
