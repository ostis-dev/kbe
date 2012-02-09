#ifndef M4SCPFILEWRITER_H
#define M4SCPFILEWRITER_H

#include "abstractfilewriter.h"

class M4SCpFileWriter : public AbstractFileWriter
{
public:
    M4SCpFileWriter();
    virtual ~M4SCpFileWriter();

    /*! Saves m4scp format to file.
      @param file_name Name of file.
      @param input QTextDocument document.

      @return If file saved, then return true, else - false.
      */
    bool save(QString file_name, QObject *input);

    AbstractFileWriter::Type type() const {return AbstractFileWriter::WT_Save;}

};

class M4SCpFileWriterFactory : public FileWriterFactory
{
public:
    M4SCpFileWriterFactory();
    virtual ~M4SCpFileWriterFactory();

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

#endif // M4SCPFILEWRITER_H
