/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>

class SCgScene;
class SCgObject;

class SCgSelect : public QObject
{
public:
    explicit SCgSelect(QObject *parent = 0);
    virtual ~SCgSelect();

    /*! Do selection algorithm
      * @param scene Pointer to sc.g-scene for objects selection
      */
    virtual void doSelection(SCgScene *scene) = 0;
};


