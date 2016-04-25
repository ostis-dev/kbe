/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scglayoutmanager.h"


SCgLayoutManager* SCgLayoutManager::mInstance = 0;

SCgLayoutManager::SCgLayoutManager(QObject *parent) :
    QObject(parent)
{
}

SCgLayoutManager::~SCgLayoutManager()
{
    deleteArrangers();
}

SCgLayoutManager& SCgLayoutManager::instance()
{
    if (mInstance == 0)
        mInstance = new SCgLayoutManager();

    return *mInstance;
}

void SCgLayoutManager::destroy()
{
    delete mInstance;
    mInstance = 0;
}

void SCgLayoutManager::arrange(SCgView* view, int type) const
{
    if(mArrangers.contains(type))
        mArrangers.value(type)->arrange(view);
}

void SCgLayoutManager::deleteArrangers()
{
    QMap<int, SCgArranger*>::iterator it = mArrangers.begin();
    for (; it != mArrangers.end(); ++it)
        delete it.value();
    mArrangers.clear();
}

void SCgLayoutManager::addArranger(SCgArranger* arranger)
{
    Q_ASSERT_X(arranger, "LayoutManager::addArranger", "arranger is null");
    if(!mArrangers.contains(arranger->type()))
    {
        arranger->setParent(this);
        mArrangers.insert(arranger->type(), arranger);
    }
    else
        delete arranger;
}
