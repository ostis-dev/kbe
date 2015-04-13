/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "gwffileloader.h"

#include "scgdefaultobjectbuilder.h"
#include "gwfobjectinforeader.h"
#include "scgobject.h"
#include "scgscene.h"

#include <QMessageBox>
#include <QApplication>
#include <QDomDocument>
#include <QFile>

GWFFileLoader::GWFFileLoader()
{

}
GWFFileLoader::~GWFFileLoader()
{

}
        
void GWFFileLoader::showLastError()
{
    QMessageBox::information(0, qAppName(), QObject::tr("Error while opening file %1\n").arg(mFileName) + mLastError);
}

void GWFFileLoader::showGeneralError()
{
    errorParse();
    showLastError();
}

bool GWFFileLoader::load(QString file_name, QObject *output)
{
    SCgScene *scene = qobject_cast<SCgScene*>(output);

    // read data from file
    QString errorStr;
    int errorLine;
    int errorColumn;

    QFile file(file_name);
    QDomDocument document;

    mFileName = file_name;

    if (!document.setContent(&file, &errorStr, &errorLine, &errorColumn))
    {
        QMessageBox::information(0, qAppName(),
                                 QObject::tr("Error while opening file %1.\nParse error at line %2, column %3:\n%4")
                                 .arg(file_name)
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }


    /////////////////////////////////////////////
    // Read document
    GwfObjectInfoReader reader;
    if (! reader.read(document))
    {
        mLastError = reader.lastError();
        showLastError();
        return false;
    }
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    //Place objects to scene
    DefaultSCgObjectBuilder objectBuilder(scene);
    objectBuilder.buildObjects(reader.objectsInfo());
    if (objectBuilder.hasErrors())
    {
        mLastError = QObject::tr("Building process has finished with following errors:\n").arg(mFileName);
        foreach(const QString& str, objectBuilder.errorList())
            mLastError += str + '\n';

        showLastError();
    }
    /////////////////////////////////////////////

    return true;
}

void GWFFileLoader::errorParse()
{
    mLastError = QObject::tr("error to parse file '%1'").arg(mFileName);
}
