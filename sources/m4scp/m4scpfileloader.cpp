/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "m4scpfileloader.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

M4SCpFileLoader::M4SCpFileLoader()
{

}

M4SCpFileLoader::~M4SCpFileLoader()
{

}

bool M4SCpFileLoader::load(QString file_name, QObject *output)
{
    QTextDocument *document = qobject_cast<QTextDocument*>(output);

    // read data from file

    QFile file(file_name);

    mFileName = file_name;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

    QTextStream in(&file);
    document->setPlainText(in.readAll());   
    file.close();
    return true;
}


M4SCpFileLoaderFactory::M4SCpFileLoaderFactory() :
        FileLoaderFactory()
{

}

M4SCpFileLoaderFactory::~M4SCpFileLoaderFactory()
{

}

AbstractFileLoader* M4SCpFileLoaderFactory::createInstance()
{
    return new M4SCpFileLoader();
}

QList<QString> M4SCpFileLoaderFactory::extensions()
{
    QList<QString> res;
    res.push_back("m4scp");
    return res;
}

QString M4SCpFileLoaderFactory::formatDescription(const QString &ext)
{
    return tr("Simple format");
}

FileLoaderFactory* M4SCpFileLoaderFactory::clone()
{
    return new M4SCpFileLoaderFactory();
}

AbstractFileLoader::Type M4SCpFileLoaderFactory::type()
{
    return AbstractFileLoader::LT_Open;
}
