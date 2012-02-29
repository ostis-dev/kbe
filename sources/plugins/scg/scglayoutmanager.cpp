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

#include "layoutmanager.h"


LayoutManager* LayoutManager::mInstance = 0;

LayoutManager::LayoutManager(QObject *parent) :
    QObject(parent)
{
}

LayoutManager::~LayoutManager()
{
    deleteArrangers();
}

LayoutManager& LayoutManager::instance()
{
    if (mInstance == 0)
        mInstance = new LayoutManager();

    return *mInstance;
}

void LayoutManager::destroy()
{
    delete mInstance;
    mInstance = 0;
}

void LayoutManager::arrange(SCgView* view, int type) const
{
    if(mArrangers.contains(type))
        mArrangers.value(type)->arrange(view);
}

void LayoutManager::deleteArrangers()
{
    QMap<int, SCgArranger*>::iterator it = mArrangers.begin();
    for (; it != mArrangers.end(); ++it)
        delete it.value();
    mArrangers.clear();
}

void LayoutManager::addArranger(SCgArranger* arranger)
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
