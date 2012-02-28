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


#ifndef M4SCPFILEWRITER_H
#define M4SCPFILEWRITER_H

#include "interfaces/filewriterinterface.h"

class M4SCpFileWriter : public FileWriterInterface
{
    Q_INTERFACES(FileWriterInterface)
public:
    M4SCpFileWriter();
    virtual ~M4SCpFileWriter();

    /*! Saves m4scp format to file.
      @param file_name Name of file.
      @param input QTextDocument document.

      @return If file saved, then return true, else - false.
      */
    bool save(QString file_name, QObject *input);

    FileWriterInterface::Type type() const {return FileWriterInterface::WT_Save;}

};

class M4SCpFileWriterFactory : public QObject,
                               public FileWriterFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(FileWriterFactoryInterface)
public:
    explicit M4SCpFileWriterFactory(QObject *parent);
    virtual ~M4SCpFileWriterFactory();

    //! @see FileWriterFactory::createInstance
    FileWriterInterface* createInstance();
    //! @see FileWriterFactory::extensions
    QList<QString> extensions();
    //! @see FileWriterFactory::formatDescription
    QString formatDescription(const QString &ext);
    //! @see FileWriterFactory::clone
    FileWriterFactoryInterface* clone();
    //! @see FileWriterFactory::type
    FileWriterInterface::Type type();
};

#endif // M4SCPFILEWRITER_H
