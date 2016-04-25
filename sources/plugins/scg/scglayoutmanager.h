/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


