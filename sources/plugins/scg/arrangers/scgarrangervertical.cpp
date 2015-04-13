/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgarrangervertical.h"

#include "scgview.h"
#include "scgpair.h"
#include "scgbus.h"

#include <QMessageBox>
#include <QApplication>

SCgVerticalArranger::SCgVerticalArranger(QObject *parent) :
    SCgArranger(parent)
{
}

SCgVerticalArranger::~SCgVerticalArranger()
{
}

bool SCgVerticalArranger::configDialog()
{
    return true;
}

void SCgVerticalArranger::startOperation()
{
    QList<SCgObject*> objects;
    foreach(QGraphicsItem* it, mView->scene()->selectedItems())
        if(SCgObject::isSCgObjectType(it->type()) && it->type() != SCgPair::Type)
            objects.append(static_cast<SCgObject*>(it));

    if(objects.isEmpty() || objects.size() == 1)
    {
        QMessageBox::information(0, qAppName(), tr("Nothing to align. Did you forget to select objects for alignment?"));
        return;
    }

    QList<SCgObject*>::const_iterator it;
    double averageX = 0;

    // Calculate average X coordinate
    for (it = objects.begin(); it != objects.end(); ++it)
        averageX += (*it)->x();
    averageX = averageX/objects.size();

    // Set objects position
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it)->type() == SCgBus::Type)
        {
            SCgBus* b = static_cast<SCgBus*>(*it);
            QVector<QPointF> points = b->mapToParent(b->points());

            for(int i = 0; i < points.size(); ++i)
                points[i].setX(averageX);

            registerCommand(b,  b->mapFromParent(points));
        }else
        {
            QPointF p = (*it)->pos();
            p.setX(averageX);
            registerCommand(*it, p);
        }
    }
}

QString SCgVerticalArranger::name() const
{
    return tr("Vertical arrange");
}
