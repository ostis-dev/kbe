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

#ifndef SCGCONTENTCHANGEDIALOG_H
#define SCGCONTENTCHANGEDIALOG_H

#include <QtWidgets/QDialog>

#include "scgcontent.h"
#include <QValidator>

class SCgContentDialog;
class SCgNode;
class QHBoxLayout;
class QPushButton;

class SCgContentChangeDialog : public QDialog
{
Q_OBJECT
public:
    static SCgContentChangeDialog* getInstance();
    static void Destroy()
    {
        if(mInstance)
            delete mInstance;
        mInstance = 0;
    }
private:
    static SCgContentChangeDialog *mInstance;

public:
    explicit SCgContentChangeDialog(SCgNode *node, QWidget *parent = 0);
    virtual ~SCgContentChangeDialog();

    /*! Get content info
      */
    void contentInfo(SCgContent::ContInfo &info);

private:
    //! sc.g-node that controls by dialog
    SCgNode *mNode;
    //! Current content dialog
    SCgContentDialog *mDialog;

    //! Central widget that contains content dialog
    QHBoxLayout *mCenterLayout;
    //! Apply button on dialog
    QPushButton *mButtonApply;

signals:

private slots:
    /*! Slot for a format changing
        \param format   Selected format.
      */
    void changeFromat(QString format);

    /*! Slot to apply content to node
      */
    void apply();

private slots:
    /*! Slot to change apply button state in dependence of content value
      */
    void slotEnableApplyButton(QValidator::State);

};

#endif // SCGCONTENTCHANGEDIALOG_H
