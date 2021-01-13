#include "scgfileloader.h"
#include "scgobjectinforeader.h"
#include "scgdefaultobjectbuilder.h"
#include "scgobject.h"
#include "scgscene.h"

#include <QMessageBox>
#include <QApplication>
#include <QDomDocument>
#include <QFile>

#include <QtDebug>

#include "sc-memory/scs/scs_parser.hpp"


SCgFileLoader::SCgFileLoader()
{

}

SCgFileLoader::~SCgFileLoader()
{

}

bool SCgFileLoader::load(QString file_name, QObject *output)
{
    SCgScene *scene = qobject_cast<SCgScene*>(output);

    // read data from file
    QString errorStr;

    mFileName = file_name;
    QString layoutFileName = file_name.replace(file_name.size() - 3, 3, "layout.scs");
    QFile file(mFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QFile layoutFile(layoutFileName);
    layoutFile.open(QIODevice::ReadOnly | QIODevice::Text);

    /////////////////////////////////////////////
    // Read document
    SCgObjectInfoReader reader;
    reader.read(&file, &layoutFile);
    file.close();
    layoutFile.close();

    /////////////////////////////////////////////
    /////////////////////////////////////////////
    //Place objects to scene
    DefaultSCgObjectBuilder objectBuilder(scene);
    objectBuilder.buildObjects(reader.objectsInfo());

    /////////////////////////////////////////////

    return true;
}
