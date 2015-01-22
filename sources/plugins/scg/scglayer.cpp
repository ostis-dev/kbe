#include "scglayer.h"

#include "scgobject.h"

SCgLayer::SCgLayer(QString const& name, QObject *parent) : QObject(parent),
    mObjects(),
    mName(name),
    mState(true),
    mIsDead(false)
{

}

SCgLayer::~SCgLayer()
{

}

void SCgLayer::addObject(SCgObject *object)
{
    mObjects.append(object);
    object->setParentLayer(this);

}

void SCgLayer::removeObject(SCgObject *object)
{
    mObjects.removeOne(object);
}

void SCgLayer::clear()
{
    emit clear(mObjects);
    mObjects.clear();
}

void SCgLayer::show() const
{
    if (mState)
        return;
    Q_FOREACH(SCgObject* object, mObjects)
    {
        object->show();
    }
    mState = true;
}

void SCgLayer::hide() const
{
    if (!mState)
        return;
    Q_FOREACH(QGraphicsItem* object, mObjects)
    {
        object->hide();
    }
    mState = false;
}

QString SCgLayer::name() const
{
    return mName;
}

void SCgLayer::setName(QString &name)
{
    mName = name;
}

void SCgLayer::setDead(bool isDead)
{
    mIsDead = isDead;
    Q_FOREACH(SCgObject* object, mObjects)
    {
        if (isDead)
        {
            object->hide();
            Q_FOREACH(QGraphicsItem* item, object->childItems())
            {
                item->hide();
            }
        }
        else
        {
            object->show();
            Q_FOREACH(QGraphicsItem* item, object->childItems())
            {
                item->show();
            }
        }
        object->setDead(mIsDead);
    }
}

bool SCgLayer::isDead()
{
    return mIsDead;
}

void SCgLayer::selectObjects()
{
    Q_FOREACH(SCgObject* object, mObjects)
        object->setSelected(true);
}
