#pragma once

#include <QString>
#include <QObject>

class FileWriter
{
public:
    // Saves scg format to file.
    virtual bool save(QString file_name, QObject *input) = 0;
};


