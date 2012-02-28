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

#ifndef M4SCPFILELOADER_H
#define M4SCPFILELOADER_H

#include "interfaces/fileloaderinterface.h"

class M4SCpFileLoader : public FileLoaderInterface
{
    Q_INTERFACES(FileLoaderInterface)
public:
    M4SCpFileLoader();
    virtual ~M4SCpFileLoader();
    /*! Loads m4scp format.
      @param file_name Name of file.
      @param output QTextDocument document.

      @return If file loaded, then return true, else - false.
      */
    bool load(QString file_name, QObject *output);

private:
    QString mFileName;
};


class M4SCpFileLoaderFactory : public QObject,
                               public FileLoaderFactoryInterface

{
    Q_OBJECT
    Q_INTERFACES(FileLoaderFactoryInterface)

public:
    explicit M4SCpFileLoaderFactory(QObject *parent);
    virtual ~M4SCpFileLoaderFactory();

    //! @see FileLoaderFactory::createInstance
    FileLoaderInterface* createInstance();
    //! @see FileLoaderFactory::extensions
    QList<QString> extensions();
    //! @see FileLoaderFactory::formatDescription
    QString formatDescription(const QString &ext);
    //! @see FileLoaderFactory::clone
    FileLoaderFactoryInterface* clone();
    //! @see FileLoaderFactory::type
    FileLoaderInterface::Type type();
};

#endif // M4SCPFILELOADER_H
