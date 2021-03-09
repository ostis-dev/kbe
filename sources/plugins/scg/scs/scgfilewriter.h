#pragma once

#include "scgstreamwriter.h"
#include "filewriter.h"
#include <QFile>

class SCgObject;
class SCgNode;

class SCgFileWriter : public FileWriter
{
public:
    SCgFileWriter();
    virtual ~SCgFileWriter();

    bool save(QString file_name, QObject *input);
private:
    SCgStreamWriter stream;

    QString getLayoutFileName(QString name);
    bool openFile(QFile &file);
};


