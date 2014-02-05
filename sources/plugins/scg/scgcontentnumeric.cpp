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

#include "scgcontentnumeric.h"
#include "scgcontentchangedialog.h"

#include "scgnode.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QDoubleValidator>
#include <QtWidgets/QLabel>

// ------------------------------
SCgContentNumericDialog::SCgContentNumericDialog(SCgNode *node, QWidget *parent)
        : SCgContentDialog(node, parent)
        , mNumericLineEdit(0)
{
	mNumericLineEdit = new QLineEdit(this);
    mLabel = new QLabel("Input value in borders (-1e308, 1e308):");

	mNumericLineEdit->setEnabled(true);
	mNumericLineEdit->setMinimumWidth(150);
    mNumericLineEdit->setMinimumHeight(32);
    //mNumericLineEdit->setFixedHeight(22);
    mNumericValidator = new QDoubleValidator(mNumericLineEdit);
    mNumericValidator->setBottom(-1e308);
    mNumericValidator->setTop(1e308);
    mNumericLineEdit->setValidator(mNumericValidator);
	mNumericLineEdit->setFocus();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mLabel);
    mainLayout->addWidget(mNumericLineEdit, 2);
    mainLayout->addSpacing(20);
    setLayout(mainLayout);

    if (mNode->isContentData() && mNode->contentFormat() == "numeric")
    {
    	mNumericLineEdit->setText(mNode->contentData().toString());
    }
    else
    {
        mNumericLineEdit->setText("");
    }

    connect(mNumericLineEdit, SIGNAL(textChanged(QString)), this,
            SLOT(slotEnableApplyButton(QString)));
    connect(this, SIGNAL(enableApplyButton(QValidator::State)),
            SCgContentChangeDialog::getInstance(),
            SLOT(slotEnableApplyButton(QValidator::State)));
}

void SCgContentNumericDialog::apply()
{
//    Q_ASSERT(mNode);
//    // gets value and sets it to the node
//    mNode->setContent("numeric", QVariant(mNumericLineEdit->text().toDouble()), "", SCgContent::Real);
}

void SCgContentNumericDialog::contentInfo(SCgContent::ContInfo &info)
{
    if (!mNumericLineEdit->text().isEmpty()) {
        info.data = QVariant(mNumericLineEdit->text().toDouble());
        info.mimeType = "content/term";
        info.fileName = "";
        info.type = SCgContent::Real;
    }
    else info.setEmpty();
}

void SCgContentNumericDialog::slotEnableApplyButton(QString changes)
{
    int i = 0;
    emit enableApplyButton(mNumericValidator->validate(changes, i));
    if (mNumericValidator->validate(changes, i) != 2)
    {
        mNumericLineEdit->setStyleSheet("QLineEdit{color:red}");
    }
    else
    {
        mNumericLineEdit->setStyleSheet("QLineEdit{color:black}");
    }
}

// ------------------------------
SCgContentViewer* SCgContentNumericFactory::createViewerInstance()
{
    return new SCgContentStringViewer();
}

SCgContentDialog* SCgContentNumericFactory::createDialogInstance(SCgNode *node)
{
    return new SCgContentNumericDialog(node);
}

QMap<QString, SCgContentFactory::MimeAndSCgTypes> SCgContentNumericFactory::supportedExtentions() {
    return QMap<QString, MimeAndSCgTypes>();
}
