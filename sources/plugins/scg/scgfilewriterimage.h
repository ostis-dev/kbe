/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QString>


class SCgFileWriterImage
{
public:
    SCgFileWriterImage();
    virtual ~SCgFileWriterImage(){}

    bool save(QString file_name, QObject *input);

};
