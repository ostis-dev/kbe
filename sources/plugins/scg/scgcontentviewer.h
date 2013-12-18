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

#ifndef SCGCONTENTVIEWER_H
#define SCGCONTENTVIEWER_H

#include <QWidgets/QGraphicsProxyWidget>
#include <QWidgets/QWidget>
#include <QVariant>

class SCgContentViewer : public QGraphicsProxyWidget
{
Q_OBJECT
public:

    explicit SCgContentViewer(QGraphicsItem* parent = 0);
    virtual ~SCgContentViewer();
    /*! Set content data
      */
    virtual void setData(const QVariant &data);

    /*! Get content data
      */
    const QVariant& getData() const;

    //! @see QGraphicsProxyWidget::hide()
    virtual void hide(){QGraphicsProxyWidget::hide();}

    //! @see QGraphicsProxyWidget::show()
    virtual void show(){QGraphicsProxyWidget::show();}

protected:
    /*! Content data
      */
    QVariant mData;

    //! overloads parent method (@see QGraphicsProxyWidget::setWidget)
    //! Now it's no more visible for non-subclasses.
    void setWidget(QWidget* w);

signals:

public slots:

};

#endif // SCGCONTENTVIEWER_H
