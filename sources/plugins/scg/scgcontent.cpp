/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontent.h"
#include <QObject>

SCgContent::SCgContent()
{
    mFileName = mFormat = mMimeType = "";
    mType = Empty;
}

SCgContent::SCgContent(const QString& mimeType, const QVariant& data,
                        const QString& fileName, SCgContent::ContType cType)
{
    setContent(mimeType, data, fileName, cType);
}

SCgContent::~SCgContent()
{

}

void SCgContent::setContent(const QString& mimeType, const QVariant& data,
                            const QString& fileName, SCgContent::ContType cType)
{
    mMimeType = mimeType;
    mData = data;
    mType = cType;

    int slashPos = fileName.lastIndexOf('/');
    if(slashPos < 0)
        mFileName = fileName;
    else
        mFileName = fileName.mid(slashPos+1);

    switch (cType)
    {
    case Empty:
        break;

    case Int:
    case Real:
        mFormat = "numeric";
        break;
    case String:
        mFormat = "string";
        break;
    case Data:
        mFormat = mMimeType.mid(0, mMimeType.indexOf("/"));
        break;

    case Lazy:
        break;
    }
}

SCgContent::ContType SCgContent::contentType() const
{
    return mType;
}

const QString& SCgContent::contentFormat() const
{
    return mFormat;
}

const QVariant& SCgContent::contentData() const
{
    return mData;
}

const QString& SCgContent::contentFileName() const
{
    return mFileName;
}

const QString& SCgContent::contentMimeType() const
{
    return mMimeType;
}

void SCgContent::contentInfo(SCgContent::ContInfo &info)
{
    info.data = mData;
    info.mimeType = mMimeType;
    info.fileName = mFileName;
    info.type = mType;
}
