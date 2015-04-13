/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QGraphicsProxyWidget>
#include <QWidget>
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


