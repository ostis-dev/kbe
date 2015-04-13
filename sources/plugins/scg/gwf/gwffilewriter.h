/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "gwfstreamwriter.h"

//! TODO: add error messages

class SCgObject;
class SCgNode;

class GWFFileWriter
{
public:
    GWFFileWriter();
    virtual ~GWFFileWriter();

    /*! Saves gwf format to file.
      @param file_name Name of file.
      @param input scg-editor scene.

      @return If file saved, then return true, else - false.
      */
    bool save(QString file_name, QObject *input);

private:

    GwfStreamWriter stream;
};


