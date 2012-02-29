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


#ifndef SCGCONTENT_H_
#define SCGCONTENT_H_

#include <QObject>
#include <QVariant>

class SCgContent
{
public:

    //! Content types
    enum ContType
    {
        Empty = 0,
        String,
        Int,
        Real,
        Data,
        Lazy
    };

    //! Content data
    struct ContInfo
    {
        QVariant    data;
        QString     mimeType;
        QString     fileName;
        SCgContent::ContType    type;

        ContInfo() :
            type(Empty)
        {

        }

        ContInfo(QVariant _data, QString _mimeType, QString _fileName, SCgContent::ContType _type) :
            data(_data),
            mimeType(_mimeType),
            fileName(_fileName),
            type(_type)
        {

        }

        ContInfo(const ContInfo& info)
        {
            data = info.data;
            mimeType = info.mimeType;
            fileName = info.fileName;
            type = info.type;
        }

        void setEmpty()
        {
            data = 0;
            mimeType = "";
            fileName = "";
            type = Empty;
        }

    };

    SCgContent();
    SCgContent(const QString& mimeType, const QVariant& data, const QString& fileName, ContType cType);
    virtual ~SCgContent();

    /*! Set content information and data

        @param  format Content format
        @param  data Content data
        @param  fileName File name (if content has been loaded from file)
        @param  cType   Content type
     */
    virtual void setContent(const QString& mimeType, const QVariant& data,
                        const QString& fileName, ContType cType);

    /*! Get content format

        @return content format.
      */
    const QString& contentFormat() const;

    /*! Get contend data

        @return Content data.

        @see SCgContent::setAllData()
      */
    const QVariant& contentData() const;

    /*! Get content file name

        @return content file name.
      */
    const QString& contentFileName() const;

    /*! Get content type(1..4)

        @return content type.
      */
    ContType contentType() const;

    /*! Get content mime-type.

        \return content mime-type.
      */
    const QString& contentMimeType() const;

    /*! Get content info in one structure
      @param    info    Reference to structure that will be filled with content data
      */
    void contentInfo(ContInfo &info);

protected:
    /*! Content type
      */
    ContType mType;

    /*! Content data
      */
    QVariant mData;

    /*! Content format
      */
    QString mFormat;

    /*! Mime-type
     */
    QString mMimeType;

    /*! File name (if any)
     */
    QString mFileName;
};

#endif /* SCGCONTENT_H_ */
