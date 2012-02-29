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
#ifndef SCGFILEWRITERGWF_H
#define SCGFILEWRITERGWF_H

#include "abstractfilewriter.h"

#include "gwfstreamwriter.h"

//! TODO: add error messages

class SCgObject;
class SCgNode;

class SCgFileWriterGWF : public AbstractFileWriter
{
public:
    SCgFileWriterGWF();
    virtual ~SCgFileWriterGWF();

    /*! Saves gwf format to file.
      @param file_name Name of file.
      @param input scg-editor scene.

      @return If file saved, then return true, else - false.
      */
    bool save(QString file_name, QObject *input);

    AbstractFileWriter::Type type() const {return AbstractFileWriter::WT_Save;}

private:

    GwfStreamWriter stream;
};

class SCgFileWriterGWFFactory : public FileWriterFactory
{
public:
    SCgFileWriterGWFFactory();
    virtual ~SCgFileWriterGWFFactory();

    //! @see FileWriterFactory::createInstance
    AbstractFileWriter* createInstance();
    //! @see FileWriterFactory::extensions
    QList<QString> extensions();
    //! @see FileWriterFactory::formatDescription
    QString formatDescription(const QString &ext);
    //! @see FileWriterFactory::clone
    FileWriterFactory* clone();
    //! @see FileWriterFactory::type
    AbstractFileWriter::Type type();
};

#endif // SCGFILEWRITERGWF_H
