#ifndef SCSFILELOADER_H
#define SCSFILELOADER_H

#include <QObject>
#include <QString>
#include "scsobjectinforeader.h"

class SCgScene;
class SCgObject;

class ScsFileLoader
{
public:
    ScsFileLoader();
    virtual ~ScsFileLoader();

    /*! Loads scs2 format.
      @param file_name Name of file.
      @param output scg-editor scene.

      @return If file loaded, then return true, else - false.
    */
    bool load(QString file_name, QObject*output);
private:
    //! File name
    QString mFileName;
};

#endif // SCSFILELOADER_H
