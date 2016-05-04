/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#include "scglayer.h"

#include "scgobject.h"

SCgLayer::SCgLayer(QString const& name, QObject *parent) : QObject(parent),
    mLayerObjects(),
    mLayerName(name),
    mState(true),
    mIsDead(false)
{

}

SCgLayer::~SCgLayer()
{

}

void SCgLayer::addObject(SCgObject *object)
{
    mLayerObjects.append(object);
    object->setLayer(this);

}

void SCgLayer::removeObject(SCgObject *object)
{
    mLayerObjects.removeOne(object);
}

void SCgLayer::clear()
{
    emit clear(mLayerObjects);
    mLayerObjects.clear();
}

void SCgLayer::show() const
{
    if (mState)
    {
        return;
    }

    Q_FOREACH(SCgObject* object, mLayerObjects)
    {
        object->show();
    }
    mState = true;
}

void SCgLayer::hide() const
{
    if (!mState)
    {
        return;
    }

    Q_FOREACH(QGraphicsItem* object, mLayerObjects)
    {
        object->hide();
    }
    mState = false;
}

QString SCgLayer::getName() const
{
    return mLayerName;
}

void SCgLayer::setName(QString &name)
{
    mLayerName = name;
}

void SCgLayer::setDead(bool isDead)
{
    mIsDead = isDead;
    Q_FOREACH(SCgObject* object, mLayerObjects)
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
    Q_FOREACH(SCgObject* object, mLayerObjects)
        object->setSelected(true);
}
