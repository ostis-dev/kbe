/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

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

#ifndef SCGEXPORTIMAGE_H
#define SCGEXPORTIMAGE_H

#include <QObject>

class SCgScene;

class SCgExportImage : public QObject
{
    Q_OBJECT
public:
    explicit SCgExportImage(QObject *parent = 0);
    virtual ~SCgExportImage();

    //! Return list of all supported image formats
    QStringList supportedFormats() const;

    /*! Export specified \p scene into file with \p fileName
      * @param scene Pointer to scene that need to be exported
      * @param fileName Output file name
      */
    bool doExport(SCgScene *scene, const QString &fileName);

};

#endif // SCGEXPORTIMAGE_H
