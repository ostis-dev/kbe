/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#ifndef SCGCONTENTDIALOG_H
#define SCGCONTENTDIALOG_H

#include <QDialog>

#include "scgcontent.h"

class SCgNode;


class SCgContentDialog : public QWidget
{
Q_OBJECT
public:
    explicit SCgContentDialog(SCgNode *node, QWidget *parent = 0);

    virtual ~SCgContentDialog(){}

    /*! Function calls to apply edited content to node
      */
    virtual void apply() = 0;

    //! Return content info
    virtual void contentInfo(SCgContent::ContInfo &info) = 0;

protected:
    /*! sc.g-node pointer
      */
    SCgNode *mNode;

signals:

private slots:

};

#endif // SCGCONTENTDIALOG_H
