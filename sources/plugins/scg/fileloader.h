#pragma once

#include <QString>
#include <QObject>

class FileLoader
{
public:
    /*! Loads gwf format.
      @param file_name Name of file.
      @param output scg-editor scene.

      @return If file loaded, then return true, else - false.
      */
    virtual bool load(QString file_name, QObject *output) = 0;
};
