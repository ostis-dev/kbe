#pragma once

#include "scgstreamwriter.h"
#include "filewriter.h"
#include <QFile>

//! TODO: add error messages

class SCgObject;
class SCgNode;

class SCgFileWriter : public FileWriter
{
public:
    SCgFileWriter();
    virtual ~SCgFileWriter();

    /*! Saves scg format to file.
      @param file_name Name of file.
      @param input scg-editor scene.

      @return If file saved, then return true, else - false.
      */
    bool save(QString file_name, QObject *input);
private:
    SCgStreamWriter stream;

    QString getLayoutFileName(QString name);
    bool openFile(QFile &file);
};


