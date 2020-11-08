/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontentviewer.h"

SCgContentViewer::SCgContentViewer(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
}

SCgContentViewer::~SCgContentViewer()
{

}

void SCgContentViewer::setWidget(QWidget* w)
{
    QGraphicsProxyWidget::setWidget(w);
    if(w)
        setPos( -w->width()/2, -w->height()/2);
    QFont font("Times New Roman", 10, 10, false);
    w->setFont(font);
    hide();
}

void SCgContentViewer::setData(const QVariant &data)
{
    mData = data;
}

const QVariant& SCgContentViewer::getData() const
{
    return mData;
}
