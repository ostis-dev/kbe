/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>

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


