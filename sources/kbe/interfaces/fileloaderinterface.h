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

#ifndef ABSTRACTFILELOADER_H
#define ABSTRACTFILELOADER_H

#include <QObject>

/*! Base absract class for file loaders
  */
class FileLoaderInterface
{
public:

    //! Type of loader
    typedef enum
    {
        LT_Open = 0,
        LT_Import,
        LT_Count
    } Type;

    explicit FileLoaderInterface() {}
    virtual ~FileLoaderInterface() {}

    /*! Loads data from file into window.
      @param file_name Name of file.
      @param output Output object to create loaded data in.

      @return If file loaded, then return true, else - false.
      */
    virtual bool load(QString file_name, QObject *output) = 0;

signals:

public slots:

};

//! Base class for factories that create file loaders
class FileLoaderFactoryInterface
{

public:
    explicit FileLoaderFactoryInterface() {}
    virtual ~FileLoaderFactoryInterface() {}

    //! Return instance of file loader
    virtual FileLoaderInterface* createInstance() = 0;
    //! Return list of supported file extensions
    virtual QList<QString> extensions() = 0;
    //! Return format description
    virtual QString formatDescription(const QString &ext) = 0;
    //! Clone factory
    virtual FileLoaderFactoryInterface* clone() = 0;
    //! Get loader type
    virtual FileLoaderInterface::Type type() = 0;
};

Q_DECLARE_INTERFACE(FileLoaderInterface,
                    "com.OSTIS.kbe.FileLoaderInterface/1.0")

Q_DECLARE_INTERFACE(FileLoaderFactoryInterface,
                    "com.OSTIS.kbe.FileLoaderFactoryInterface/1.0")

#endif // ABSTRACTFILELOADER_H
