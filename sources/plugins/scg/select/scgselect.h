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

#ifndef SCGSELECT_H
#define SCGSELECT_H

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
    virtual void undoSelection(SCgScene *scene) =0;

};

#endif // SCGSELECT_H
