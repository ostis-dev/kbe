#ifndef SCGLAYER_H
#define SCGLAYER_H

#include <QObject>

#include <QList>

class SCgObject;

typedef QList<SCgObject*> SCgLayerObjects;

class SCgLayer : public QObject
{
    Q_OBJECT
public:
    //! Type of layer
    enum Type{
        Node,
        Pair,
        Bus,
        Contour,
        User
    } type;

    explicit SCgLayer(QString const& name, QObject *parent = 0);
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

    QString name() const;
    void setName(QString& name);

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
    SCgLayerObjects mObjects;

    //! layer's name
    QString mName;

    //! layer's state
    mutable bool mState;

    //! is layer dead
    bool mIsDead;

};

#endif // SCGLAYER_H
