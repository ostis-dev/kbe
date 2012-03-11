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
