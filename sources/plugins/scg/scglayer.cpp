#include "scglayer.h"
#include "scgobject.h"

SCgLayer::SCgLayer(QString name)
{
    this->name = name;
    this->visible = true;
}
SCgLayer::~SCgLayer()
{

}

void SCgLayer::addObject(SCgObject* object)
{
    objects.append(object);
}

void SCgLayer::deleteObject(SCgObject* object)
{
    objects.removeOne(object);
}

void SCgLayer::setVisible(bool visible)
{
    this->visible = visible;
    if(visible)
    {
        for (int i = 0; i < objects.size(); ++i)
        {
            objects[i]->show();
        }
    } else {
        for (int i = 0; i < objects.size(); ++i)
        {
            objects[i]->hide();
        }
    }
}

bool SCgLayer::isVisible()
{
    return visible;
}

QString SCgLayer::getName()
{
    return name;
}

QList<SCgObject *> SCgLayer::getObjects()
{
    return objects;
}
