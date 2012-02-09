#ifndef M4SCPFILELOADER_H
#define M4SCPFILELOADER_H

#include "abstractfileloader.h"

class M4SCpFileLoader : public AbstractFileLoader
{

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


class M4SCpFileLoaderFactory : public FileLoaderFactory
{
public:
    M4SCpFileLoaderFactory();
    virtual ~M4SCpFileLoaderFactory();

    //! @see FileLoaderFactory::createInstance
    AbstractFileLoader* createInstance();
    //! @see FileLoaderFactory::extensions
    QList<QString> extensions();
    //! @see FileLoaderFactory::formatDescription
    QString formatDescription(const QString &ext);
    //! @see FileLoaderFactory::clone
    FileLoaderFactory* clone();
    //! @see FileLoaderFactory::type
    AbstractFileLoader::Type type();
};

#endif // M4SCPFILELOADER_H
