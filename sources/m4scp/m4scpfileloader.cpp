#include "m4scpfileloader.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

M4SCpFileLoader::M4SCpFileLoader()
{

}

M4SCpFileLoader::~M4SCpFileLoader()
{

}

bool M4SCpFileLoader::load(QString file_name, QObject *output)
{
    QTextDocument *document = qobject_cast<QTextDocument*>(output);

    // read data from file

    QFile file(file_name);

    mFileName = file_name;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

    QTextStream in(&file);
    document->setPlainText(in.readAll());   
    file.close();
    return true;
}


M4SCpFileLoaderFactory::M4SCpFileLoaderFactory() :
        FileLoaderFactory()
{

}

M4SCpFileLoaderFactory::~M4SCpFileLoaderFactory()
{

}

AbstractFileLoader* M4SCpFileLoaderFactory::createInstance()
{
    return new M4SCpFileLoader();
}

QList<QString> M4SCpFileLoaderFactory::extensions()
{
    QList<QString> res;
    res.push_back("m4scp");
    return res;
}

QString M4SCpFileLoaderFactory::formatDescription(const QString &ext)
{
    return tr("Simple format");
}

FileLoaderFactory* M4SCpFileLoaderFactory::clone()
{
    return new M4SCpFileLoaderFactory();
}

AbstractFileLoader::Type M4SCpFileLoaderFactory::type()
{
    return AbstractFileLoader::LT_Open;
}
