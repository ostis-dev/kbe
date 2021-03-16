#pragma once

#include <QString>
#include <QObject>

class FileLoader
{
public:
    //! Loads file.
    virtual bool load(QString file_name, QObject *output) = 0;
};
