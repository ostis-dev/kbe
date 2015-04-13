/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


