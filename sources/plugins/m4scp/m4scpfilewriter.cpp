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

#include "m4scpfilewriter.h"
#include <QTextDocument>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>

M4SCpFileWriter::M4SCpFileWriter()
{
}

M4SCpFileWriter::~M4SCpFileWriter()
{

}

bool M4SCpFileWriter::save(QString file_name, QObject *input)
{
    QTextDocument *document = qobject_cast<QTextDocument*>(input);

    QFile fileOut(file_name);
    if (!fileOut.open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, qAppName(),
                                  QObject::tr("File saving error.\nCannot write file %1:\n%2.")
                                  .arg(file_name)
                                  .arg(fileOut.errorString()));
             return false;
         }
    QTextStream out(&fileOut);
    out<<document->toPlainText();
    fileOut.close();
    return true;
}

