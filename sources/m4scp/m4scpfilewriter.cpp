#include "m4scpfilewriter.h"
#include <QTextDocument>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>

M4SCpFileWriter::M4SCpFileWriter()
{
}

M4SCpFileWriter::~M4SCpFileWriter()
{

}

bool M4SCpFileWriter::save(QString file_name, QObject *input)
{
    QTextDocument *document = qobject_cast<QTextDocument*>(input);

    QFile fileOut(file_name);
    if (!fileOut.open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, qAppName(),
                                  tr("File saving error.\nCannot write file %1:\n%2.")
                                  .arg(file_name)
                                  .arg(fileOut.errorString()));
             return false;
         }
    QTextStream out(&fileOut);
    out<<document->toPlainText();
    fileOut.close();
    return true;
}

// -------------------------------------------------
M4SCpFileWriterFactory::M4SCpFileWriterFactory() :
        FileWriterFactory()
{

}

M4SCpFileWriterFactory::~M4SCpFileWriterFactory()
{

}

AbstractFileWriter* M4SCpFileWriterFactory::createInstance()
{
    return new M4SCpFileWriter();
}

QList<QString> M4SCpFileWriterFactory::extensions()
{
    QList<QString> res;
    res.push_back("m4scp");
    return res;
}

QString M4SCpFileWriterFactory::formatDescription(const QString &ext)
{
    return tr("Simple format");
}

FileWriterFactory* M4SCpFileWriterFactory::clone()
{
    return new M4SCpFileWriterFactory();
}

AbstractFileWriter::Type M4SCpFileWriterFactory::type()
{
    return AbstractFileWriter::WT_Save;
}
