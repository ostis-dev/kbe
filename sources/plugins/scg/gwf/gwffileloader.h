/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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

