/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>

#include <QList>

class SCgObject;

typedef QList<SCgObject*> SCgLayerObjects;

class SCgLayer : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Node,
        Pair,
        Bus,
        Contour,
        User
    } type;

    explicit SCgLayer(QString const& getName, QObject *parent = 0);

    //! Destructor
    ~SCgLayer();

    //! Selects objects on scene
    void selectObjects();

    /*! Adds object to layer
      * @param object object for adding
      */
    void addObject(SCgObject* object);

    /*! Removes object from layer
      * @param object object for removing
      */
    void removeObject(SCgObject* object);

    //! Clears layer
    void clear();

    void setDead(bool setDead);
    bool isDead();

    QString getName() const;
    void setName(QString& getName);

public slots:
    //! Shows layer's objects
    void show() const;

    //! Hides layer's objects
    void hide() const;

signals:
    /*! Signal that emitted on clearing
      * @param objects Layer's objects
      */

    void clear(SCgLayerObjects objects);

private:
    //! layer's objects
    SCgLayerObjects mLayerObjects;

    //! layer's name
    QString mLayerName;

    //! layer's state
    mutable bool mState;

    //! is layer dead
    bool mIsDead;

};
