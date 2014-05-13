#include "scsfileloader.h"

#include "scgdefaultobjectbuilder.h"
#include "scgobject.h"
#include "scgscene.h"

#include <QDebug>

ScsFileLoader::ScsFileLoader()
{

}

ScsFileLoader::~ScsFileLoader()
{

}

bool ScsFileLoader::load(QString file_name ,QObject *output)
{    
    SCgScene *scene = qobject_cast<SCgScene*>(output);
    mFileName = file_name;

    // Read SCS document
    ScsObjectInfoReader reader;

    if (!reader.read(mFileName))
    {
        /*mLastError = reader.lastError();
        showLastError();*/
        return false;
    }

    //Place objects to scene
    DefaultSCgObjectBuilder objectBuilder(scene);
    objectBuilder.buildObjects(reader.objectsInfo());
    if (objectBuilder.hasErrors())
    {
        //mLastError = QObject::tr("Building process has finished with following errors:\n").arg(mFileName);
        //foreach(const QString& str, objectBuilder.errorList())
          //  mLastError += str + '\n';

       // showLastError();
    }



    return true;

}
