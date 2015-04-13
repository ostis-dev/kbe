/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


