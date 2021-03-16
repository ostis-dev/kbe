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
    //! Loads scs format.
    bool load(QString file_name, QObject *output);


private:
    QString mFileName;
};

