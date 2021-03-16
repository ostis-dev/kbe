#include "scgfilewriter.h"
#include "scgscene.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"

#include <QMessageBox>
#include <QTextCodec>
#include <QApplication>
#include <QFileInfo>

SCgFileWriter::SCgFileWriter()
{
}

SCgFileWriter::~SCgFileWriter()
{
}

bool SCgFileWriter::save(QString file_name, QObject *input)
{
    SCgScene *scene = qobject_cast<SCgScene*>(input);

    QFile fileOut(file_name);
    QFile layoutFileOut(getLayoutFileName(file_name));
    if (!openFile(fileOut) || !openFile(layoutFileOut))
        return false;

    stream.setOutputFiles(&fileOut, &layoutFileOut);

    auto items = scene->items();
    QGraphicsItem *item;

    QVector<SCgObject *> objs;
    QVector<SCgObject *> surfaceObjs;
    foreach (item, items)
    {
        if (SCgObject::isSCgObjectType(item->type()))
        {
            SCgObject *obj = static_cast<SCgObject*>(item);
            objs.push_back(obj);
            if (obj->parentId() == 0)
                surfaceObjs.push_back(obj);
        }
    }
    stream.preprocess(objs);
    stream.writeOrdered(surfaceObjs);

    fileOut.close();
    layoutFileOut.close();
    return true;
}

QString SCgFileWriter::getLayoutFileName(QString name)
{
    const QString SCS_EXTENSION = ".scs";
    const QString LAYOUT_EXTENSION = ".layout.scs";
    if (name.endsWith(SCS_EXTENSION)) name.remove(name.size() - SCS_EXTENSION.size(), SCS_EXTENSION.size());
    return name.append(LAYOUT_EXTENSION);
}

bool SCgFileWriter::openFile(QFile &file)
{
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(0, qAppName(),
                              QObject::tr("File saving error.\nCannot write file %1:\n%2.")
                              .arg(file.fileName())
                              .arg(file.errorString()));
        return false;
    }
    return true;
}
