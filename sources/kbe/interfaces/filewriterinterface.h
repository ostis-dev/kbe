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
#ifndef ABSTRACTFILEWRITER_H
#define ABSTRACTFILEWRITER_H

#include <QObject>
#include <QList>
#include <QString>

/*! Base abstract class for file savers
  */
class FileWriterInterface
{
public:

    //! Type of writer
    typedef enum
    {
        WT_Save = 0,
        WT_Export,
        WT_Count
    } Type;

    explicit FileWriterInterface() {}
    virtual ~FileWriterInterface() {}
    /*! Saves data from window into file.
      @param file_name Name of file.
      @param input Input object to create saved data out.

      @return If file saved, then return true, else - false.
      */
    virtual bool save(QString file_name, QObject *input) = 0;
    //! Return type of writer
    virtual FileWriterInterface::Type type() const = 0;

signals:

public slots:
};

//! Base class for factories that create file loaders
class FileWriterFactoryInterface
{

public:
    FileWriterFactoryInterface() {};
    virtual ~FileWriterFactoryInterface() {};

    //! Return instance of file writer
    virtual FileWriterInterface* createInstance() = 0;
    //! Return list of supported file extensions
    virtual QList<QString> extensions() = 0;
    //! Return format description
    virtual QString formatDescription(const QString &ext) = 0;
    //! Clone factory
    virtual FileWriterFactoryInterface* clone() = 0;
    //! Return type of writer
    virtual FileWriterInterface::Type type() = 0;
};

Q_DECLARE_INTERFACE(FileWriterInterface,
                    "com.OSTIS.kbe.FileWriterInterface/1.0")

Q_DECLARE_INTERFACE(FileWriterFactoryInterface,
                    "com.OSTIS.kbe.FileWriterFactoryInterface/1.0")


#endif // ABSTRACTFILEWRITER_H
