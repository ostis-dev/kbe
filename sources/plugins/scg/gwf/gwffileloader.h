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

#ifndef SCGFILELOADERGWF_H
#define SCGFILELOADERGWF_H

#include <QDomElement>
#include <QMap>
#include <QPair>
#include <QVector>
#include <QPointF>
#include <QObject>

class SCgScene;
class SCgObject;

class GWFFileLoader

{
public:
    GWFFileLoader();
    virtual ~GWFFileLoader();
    /*! Loads gwf format.
      @param file_name Name of file.
      @param output scg-editor scene.

      @return If file loaded, then return true, else - false.
      */
    bool load(QString file_name, QObject *output);

    /*! Show last error
      */
    void showLastError();

    /*! Show general error
      */
    void showGeneralError();


private:

    /*! Generates last error as general parsing error.
      */
    void errorParse();

    //! File name
    QString mFileName;
    //! Last error
    QString mLastError;
};

#endif // SCGFILELOADERGWF_H
