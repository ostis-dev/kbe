/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "gwffilewriter.h"
#include "scgscene.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"

#include <QMessageBox>
#include <QFile>
#include <QTextCodec>
#include <QApplication>


GWFFileWriter::GWFFileWriter()
{

}

GWFFileWriter::~GWFFileWriter()
{

}

bool GWFFileWriter::save(QString file_name, QObject *input)
{
    SCgScene *scene = qobject_cast<SCgScene*>(input);

        QFile fileOut(file_name);
        if (!fileOut.open(QFile::WriteOnly | QFile::Text))
        {
                 QMessageBox::warning(0, qAppName(),
                                      QObject::tr("File saving error.\nCannot write file %1:\n%2.")
                                      .arg(file_name)
                                      .arg(fileOut.errorString()));
                 return false;
        }
        stream.setDevice(&fileOut);
        stream.startWriting("UTF-8");

        QList<QGraphicsItem *>	items = scene->items ();
        QGraphicsItem * item;
        foreach (item, items)
        {
            if(SCgObject::isSCgObjectType(item->type()) )
            {
                SCgObject *obj = static_cast<SCgObject*>(item);
                stream.writeObject(obj);
            }
        }

        stream.finishWriting();

        fileOut.close();
        return true;
}
