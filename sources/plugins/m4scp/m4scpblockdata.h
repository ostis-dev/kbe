/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <QTextBlockUserData>

class BlockData : public QTextBlockUserData
{
public:
    inline BlockData():
        foldingLevel(0),
        folded(false),
        breackPoint(false)
        {}

    ~BlockData(){}

    static BlockData* data(QTextBlock block)
    {
        BlockData *data=static_cast<BlockData *>(block.userData());
        if(!data && block.isValid()){
            data= new BlockData();
            block.setUserData(data);
        }
        return data;
    }

    inline void setFoldingLevel(int le) {foldingLevel = le;}
    inline int getFoldingLevel() const {return foldingLevel;}

    inline void setFolded (bool f) {folded=f;}
    inline bool isFolded() const {return folded;}

private:
    int foldingLevel;
    bool folded;

    bool breackPoint;
};

#endif // BLOCKDATA_H
