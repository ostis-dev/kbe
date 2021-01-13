#pragma once

#include <QString>
#include <QObject>

class FileWriter
{
public:
    /*! Saves scg format to file.
      @param file_name Name of file.
      @param input scg-editor scene.

      @return If file saved, then return true, else - false.
      */
    virtual bool save(QString file_name, QObject *input) = 0;
};


