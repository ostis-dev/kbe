/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgarrangerhorizontal.h"

#include "scgview.h"
#include "scgpair.h"
#include "scgbus.h"

#include <QMessageBox>
#include <QApplication>

SCgHorizontalArranger::SCgHorizontalArranger(QObject *parent) :
    SCgArranger(parent)
{
}

SCgHorizontalArranger::~SCgHorizontalArranger()
{
}

bool SCgHorizontalArranger::configDialog()
{
    return true;
}

void SCgHorizontalArranger::startOperation()
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
    double averageY = 0;

    // Calculate average Y coordinate
    for (it = objects.begin(); it != objects.end(); ++it)
       averageY += (*it)->y();
    averageY = averageY/objects.size();

    // Set objects position
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it)->type() == SCgBus::Type)
        {
            SCgBus* b = static_cast<SCgBus*>(*it);
            QVector<QPointF> points = b->mapToParent(b->points());

            for(int i = 0; i < points.size(); ++i)
                points[i].setY(averageY);

            registerCommand(b,  b->mapFromParent(points));
        }else
        {
            QPointF p = (*it)->pos();
            p.setY(averageY);
            registerCommand(*it, p);
        }
    }
}

QString SCgHorizontalArranger::name() const
{
    return tr("Horizontal arrange");
}
