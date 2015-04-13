/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgcontentstring.h"
#include <QValidator>

class SCgNode;
class QLineEdit;
class QDoubleValidator;
class QLabel;

// ---------------------------------------------------
class SCgContentNumericDialog : public SCgContentDialog
{
Q_OBJECT

public:
    explicit SCgContentNumericDialog(SCgNode *node, QWidget *parent = 0);
    virtual ~SCgContentNumericDialog(){}

protected:
    void apply();

    //! @see    SCgContentDialog::contentInfo()
    void contentInfo(SCgContent::ContInfo &info);

signals:
    /*! Signal keeps line edit text validity
      */
    void enableApplyButton(QValidator::State);

private slots:
    /*! Slot keeps line edit text changes
      */
    void slotEnableApplyButton(QString);

private:
    //! Numeric edit area
    QLineEdit* mNumericLineEdit;
    //! Validator for edit area
    QDoubleValidator *mNumericValidator;
    //! Layout for borders of numeric dialog value
    QLabel *mLabel;
};

// ---------------------------------------------------
class SCgContentNumericFactory : public SCgContentFactory
{
public:
    virtual ~SCgContentNumericFactory(){}
    SCgContentViewer* createViewerInstance();
    SCgContentDialog* createDialogInstance(SCgNode *node);

    QMap<QString, MimeAndSCgTypes> supportedExtentions();
};


