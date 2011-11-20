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

#include "scgnode.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>

// ------------------------------
SCgContentNumericDialog::SCgContentNumericDialog(SCgNode *node, QWidget *parent) :
        SCgContentDialog(node, parent),
        mNumericLineEdit(0)
{
	mNumericLineEdit = new QLineEdit(this);

	mNumericLineEdit->setEnabled(true);
	mNumericLineEdit->setMinimumWidth(150);
	mNumericLineEdit->setFixedHeight(22);
	mNumericLineEdit->setValidator(new QDoubleValidator(mNumericLineEdit));
	mNumericLineEdit->setFocus();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mNumericLineEdit);
    mainLayout->addStretch();
    setLayout(mainLayout);

    if (mNode->isContentData() && mNode->contentFormat() == "numeric")
    	mNumericLineEdit->setText(mNode->contentData().toString());
    else mNumericLineEdit->setText("");
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

// ------------------------------
SCgContentViewer* SCgContentNumericFactory::createViewerInstance()
{
    return new SCgContentStringViewer();
}

SCgContentDialog* SCgContentNumericFactory::createDialogInstance(SCgNode *node)
{
    return new SCgContentNumericDialog(node);
}
