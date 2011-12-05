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


#ifndef SCGCONTENTNUMERIC_H_
#define SCGCONTENTNUMERIC_H_


//#include "scgcontentdialog.h"
//#include "scgcontentfactory.h"
//#include "scgcontentviewer.h"
#include "scgcontentstring.h"
#include <QValidator>

class SCgNode;
class QLabel;
class QLineEdit;
class QDoubleValidator;

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
};

// ---------------------------------------------------
class SCgContentNumericFactory : public SCgContentFactory
{
public:
    virtual ~SCgContentNumericFactory(){}
    SCgContentViewer* createViewerInstance();
    SCgContentDialog* createDialogInstance(SCgNode *node);
};

#endif /* SCGCONTENTNUMERIC_H_ */
