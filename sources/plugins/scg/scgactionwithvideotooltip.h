/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QEvent>
#include <QToolTip>
#include <QAction>
#include <QString>
#include <QMovie>
#include <QLabel>

class ActionWithVideoTooTip : public QWidget
{
    Q_OBJECT
public:
    ActionWithVideoTooTip(const QString text, const QString& gifPath, QWidget *parent= nullptr);

protected:
    virtual bool event(QEvent *event) override;
private:
    QMovie *movie;
    QLabel *label;
    QWidget * wid;

};
