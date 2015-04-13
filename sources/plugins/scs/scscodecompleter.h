/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QCompleter>

class SCsCodeCompleter : public QCompleter
{
    Q_OBJECT

public:
    explicit SCsCodeCompleter(QObject *parent = 0);
    virtual ~SCsCodeCompleter();

    static const int MinCompletetionLength = 3;

signals:

public slots:

};


