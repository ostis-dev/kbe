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
