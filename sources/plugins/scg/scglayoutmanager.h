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

#ifndef LAYOUTMANAGER_H_
#define LAYOUTMANAGER_H_

#include <QObject>
#include <QMap>
#include "arrangers/scgarranger.h"

class SCgView;
class LayoutAlgorithm;

class SCgLayoutManager : public QObject
{
Q_OBJECT
    explicit SCgLayoutManager(QObject *parent = 0);
    virtual ~SCgLayoutManager();
public:
    static SCgLayoutManager& instance();

    //! Destroys instance of the manager.
    static void destroy();

    /*! Arrange objects on the scene, connected with specified view.
     *
     * @param view specifies view, items on which will be arranged.
     * @param type specifies type of arranger (@see SCgArranger::ArrangerType).
     */
    void arrange(SCgView* view, int type) const;

    /*! Deletes all existing arrangers.
      */
    void deleteArrangers();

    /*! Registers new arranger.
     *
     * @param arranger arranger, to be registered.
     */
    void addArranger(SCgArranger* arranger);

private:
    //! Pointer to instance
    static SCgLayoutManager *mInstance;

protected:
    //! Holds registered arrangers
    QMap<int, SCgArranger*> mArrangers;

};

#endif /* LAYOUTMANAGER_H_ */
