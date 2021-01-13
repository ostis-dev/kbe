#pragma once

#include <QDomElement>
#include <QMap>
#include <QPair>
#include <QVector>
#include <QPointF>
#include <QObject>

#include "fileloader.h"

class SCgScene;
class SCgObject;

class SCgFileLoader : public FileLoader
{
public:
    SCgFileLoader();
    virtual ~SCgFileLoader();
    /*! Loads gwf format.
      @param file_name Name of file.
      @param output scg-editor scene.

      @return If file loaded, then return true, else - false.
      */
    bool load(QString file_name, QObject *output);


private:
    //! File name
    QString mFileName;
};

